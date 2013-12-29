/*========================================================
  HandWriting.c
  all routine is running with Platform non-related,
  all is hand writing related routine.


  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0517, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>
#include <HWUtility.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

//extern UInt32	allocCounts;
extern UInt32	mcounts;


#define	MAXINT		0xffff
#define	WORST_SCORE	MAXINT
#define	BUFSIZ		2048

#define NUM_RECS    3

/* Dynamic programming parameters */
#define	DP_BAND		3
#define	MIN_SIM		0
#define	MAX_DIST	MAXINT
#define	SIM_THLD	60	/* x 100 */
#define	DIST_THLD	3200	/* x 100 */

/* Low-pass filter parameters -- empirically derived */
#define	LP_FILTER_WIDTH	6
#define	LP_FILTER_ITERS	8
#define	LP_FILTER_THLD		250	/* x 100 */
#define	LP_FILTER_MIN		5
#define REC_DEFAULT_LOCALE  	"C"

#define CS_LETTERS		0
#define CS_DIGITS			1
#define CS_PUNC			2
#define LI_ISA_LI			0               /*Is this a li recognizer?.*/
#define LI_TRAIN			1		   /*Train recognizer*/
#define LI_CLEAR			2              /* ari's clear-state extension fn. */
#define LI_GET_CLASSES	3              /* ari's get-classes extension fn. */
#define LI_NUM_EX_FNS	4               /*Number of extension functions*/
/*Locale supported by recognizer.*/
#define LI_SUPPORTED_LOCALE  REC_DEFAULT_LOCALE

/* Pre-processing and canonicalization parameters */
#define	CANONICAL_X	108
#define	CANONICAL_Y	128
#define	DIST_SQ_THRESHOLD   (3*3)	/* copied from fv.h */
#define	NCANONICAL	50

/* Tap-handling parameters */
#define	TAP_CHARS	"."
#define	TAP_TIME_THLD	150	    /* msec */
#define	TAP_DIST_THLD	75	    /* dx * dx + dy * dy */
#define	TAP_PATHLEN	1000	    /* x 100 */

/* region types */
#define	RGN_CONVEX  0
#define	RGN_CONCAVE 1
#define	RGN_PLAIN   2
#define	RGN_PSEUDO  3

/* Pseudo-extrema parameters -- empirically derived */
#define	PE_AL_THLD	1500	/* x 100 */
#define	PE_ATCR_THLD	135	/* x 100 */

#define REC_DEFAULT_USER_DIR    "classifiers"
#define CLASSIFIER_DIR          "classifiers"
/*Classifier file extension.*/
#define LI_CLASSIFIER_EXTENSION ".cl"

/* XXX -- Intl Hack -- Jay & Ari */
#define	dgettext(domain, msg)	(msg)
#define	bindtextdomain(dirname,	domain)

/*LI Magic Number.*/
#define LI_MAGIC 0xACCBADDD

/*Check the recognizer for validity*/
#define RI_CHECK_MAGIC(rec) \
  ( (rec != NULL) && \
    (((recognizer)rec)->recognizer_magic == REC_MAGIC) && \
   (((recognizer)rec)->recognizer_end_magic == REC_END_MAGIC) &&\
   (((recognizer)rec)->recognizer_version == REC_VERSION) )
#define CHECK_LI_MAGIC(_a) \
  ((_a) != NULL && ((li_recognizer*)(_a))->li_magic == LI_MAGIC)

#define RECOGNIZER_INITIALIZE(_a) recognizer __recognizer_internal_initialize(rec_info* _a)
#define RECOGNIZER_FINALIZE(_a)	int __recognizer_internal_finalize(recognizer _a)
#define HEADER(a)	( ((struct array_header *) a) - 1 )
#define	NDIMS(a)	(int)(HEADER(a)->ndims)
#define NROWS(a)	(int)(HEADER(a)->nrows)
#define NCOLS(a)	(int)(HEADER(a)->ncols)

/* direction-code table; indexed by dx, dy */
static int lialg_dctbl[3][3] = {{1, 0, 7}, {2, 0x7FFFFFFF, 6}, {3, 4, 5}};

/* low-pass filter weights */
static int lialg_lpfwts[2 * LP_FILTER_WIDTH + 1];
static int lialg_lpfconst = -1;
static char* the_last_error = NULL;
/*Version number of API.*/
const char* REC_VERSION = "2.0";
char* li_err_msg = NULL;


static RecInterface recIFace = NULL;
point_list	*lpts=NULL;
pen_point	*currentPnt=NULL;


recognizer __recognizer_internal_initialize(rec_info* ri);
static char *recognize_stroke(rClassifier *rec, point_list *stroke) ;
static int filter_points(point_list *points) ;
static void get_bounding_box(point_list *points,
				    int *pminx, int *pminy,
				    int *pmaxx, int *pmaxy);
static int translate_points(point_list *points,
				   int minx, int miny,
				   int scalex, int scaley);
static void initialize(rClassifier *rec);
static point_list *compute_dominant_points(point_list *points) ;
static int compute_pathlen(point_list *points);
static void compute_chain_code(point_list *pts);
static void wdelete_examples(point_list* l);

/*************************************************************

  Core routines for the Li/Yeung recognition algorithm

 *************************************************************/
static void initialize(rClassifier *rec) 
{
   int i;

   /* Initialize the dompts arrays. */
   for (i = 0; i < MAXSCLASSES; i++) {
		rec->dompts[i] = NULL;
		rec->canonex[i] = NULL;
   }

}

/*
 Allocation functions
*/

Vector
NewVector(r)
int r;
{
	register struct array_header *a;
	register Vector v;

	a = (struct array_header *)
	    allocate(sizeof(struct array_header) + r * sizeof(double), char);
	a->ndims = 1;
	a->nrows = r;
	a->ncols = 1;
	v = (Vector) (a + 1);

#define CHECK
#ifdef CHECK
	if(HEADER(v) != (struct array_header *) a ||
	   NDIMS(v) != 1 || NROWS(v) != r || NCOLS(v) != 1) {
//	    	exit_error("NewVector error: v=%x H: %x,%x  D:%d,%d  R:%d,%d  C:%d,%d\n", v,  HEADER(v), a,  NDIMS(v), 1,  NROWS(v), r, NCOLS(v), 1);
	    }
#endif

	return v;
}

double	myMatrix[100][12];
UInt16	matrixCount=0;

Matrix
NewMatrix(r, c)
int r, c;
{
	register struct array_header *a = (struct array_header *)
	   allocate(sizeof(struct array_header) + r * sizeof(double *), char);
	register int i;
	register Matrix m;

	m = (Matrix) (a + 1);
	// Modify by Jerry, 11/15/2001 to resolve memory problem
	for(i = 0; i < r; i++)
		m[i] = &(myMatrix[matrixCount][i]);
//		m[i] = allocate(c, double);
	matrixCount++;
	a->ndims = 2;
	a->nrows = r;
	a->ncols = c;
	return m;
}

void
FreeVector(v)
Vector v;
{
	Vfree(HEADER(v));
}

void
FreeMatrix(m)
Matrix m;
{
//	register int i;

//	for(i = 0; i < NROWS(m); i++)
//		Vfree(m[i]);
	Vfree(HEADER(m));
}

void
sFreeClassifier(sc)
register sClassifier sc;
{
	register int i;
	register sClassDope scd;

	for(i = 0; i < sc->nclasses; i++) {
		scd = sc->classdope[i];
		if(scd->name) Vfree(scd->name);
		if(scd->sumcov) FreeMatrix(scd->sumcov);
		if(scd->average) FreeVector(scd->average);
		Vfree(scd);
		if(sc->w && sc->w[i]) FreeVector(sc->w[i]);
	}
	Vfree(sc->classdope);
	if(sc->w) Vfree(sc->w);
	if(sc->cnst) FreeVector(sc->cnst);
	if(sc->invavgcov) FreeMatrix(sc->invavgcov);
	Vfree(sc);
}

/*free_rClassifier-Free the rClassifier.*/
static void
free_rClassifier(rClassifier* rc)
{
   int i;

   if( rc->file_name != NULL) {
		Vfree(rc->file_name);
		rc->file_name = NULL;
   }

   for( i = 0; rc->ex[i] != NULL; i++) {
		wdelete_examples(rc->ex[i]);
/*
		if ( rc->ex[i]->pts ) {
			Vfree (rc->ex[i]->pts);
			rc->ex[i]->pts = NULL;
		}
*/
		Vfree (rc->ex[i]);
//		delete_examples(rc->ex[i]);
		Vfree(rc->cnames[i]);
		rc->ex[i] = NULL;
		rc->cnames[i] = NULL;
   }

   for( i = 0; rc->canonex[i] != NULL; i++) {
		delete_examples(rc->canonex[i]);
		rc->canonex[i] = NULL;
   }

   for( i = 0; rc->dompts[i] != NULL; i++) {
		delete_examples(rc->dompts[i]);
		rc->dompts[i] = NULL;
   }

   if(rc->sc != NULL ) {
		sFreeClassifier(rc->sc);
   }
}

/*
 * Point List Support
*/

static point_list*
add_example(point_list* l,int npts,pen_point* pts)
{
    pen_point* lpts = make_pen_point_array((UInt16)npts);
    /*    point_list* p = (point_list*)safe_malloc(sizeof(point_list));*/
    point_list *p = allocate(1, point_list);

    p->npts = npts;
    p->pts = lpts;
    p->next = l;       /*Order doesn't matter, so we stick on end.*/

    /*Copy points.*/
//    Vmemcpy(pts,lpts,npts * sizeof(pen_point));
    Vmemcpy(lpts, pts,npts * sizeof(pen_point));

    return(p);
}
    

static void
delete_examples(point_list* l)
{
   point_list* p;

   for( ; l != NULL; l = p ) {
		p = l->next;
		Vfree(l->pts);
		l->pts = NULL;
		Vfree(l);
		l = NULL;
   }
}

static void
wdelete_examples(point_list* l)
{
   point_list* p;

   for( ; l != NULL; l = p ) {
		p = l->next;
		Vfree(l->pts);
		l->pts = NULL;
   }
}

/*
 * recognize_internal-Form Vector, use Classifier to classify, return char.
 */

static char*
  recognize_internal(rClassifier* rec,pen_stroke* str,int* rconf)
{
   char *res = NULL;
   point_list *stroke = NULL;

   stroke = add_example(NULL, str->ps_npts, str->ps_pts);
   if (stroke == NULL) return(NULL);

	res = recognize_stroke(rec, stroke);

   delete_examples(stroke);
   return(res);
}

/*
 * file_path-Construct pathname, check for proper extension.
 */

static int
  file_path(char* dir,char* filename,char* pathname)
{
   char* dot;
    
    /*Check for proper extension on file name.*/
    
   dot = Vstrrchr(filename,'.');
    
   if( dot == NULL ) {
		return(-1);
   }

    /*Determine whether a gesture or character classifier.*/

   if( Vstrcmp(dot,LI_CLASSIFIER_EXTENSION) != 0 ) {
		return(-1);
   }

   /*Concatenate directory and filename into pathname.*/
    
   Vstrcpy(pathname,dir);
   Vstrcat(pathname,"/");
   Vstrcat(pathname,filename);
    
   return(0);
}

static int compute_equipoints(point_list *points) 
{
   pen_point *equipoints = make_pen_point_array(NCANONICAL);
   int nequipoints = 0;
   int pathlen = compute_pathlen(points);
   int equidist = (pathlen + (NCANONICAL - 1) / 2) / (NCANONICAL - 1);
   int i;
   int dist_since_last_eqpt;
   int remaining_seglen;
   int dist_to_next_eqpt;

   if (equipoints == NULL) {
//		error("can't allocate memory in lialg_compute_equipoints");
		return(-1);
	}

   /* First original point is an equipoint. */
   equipoints[0] = points->pts[0];
   nequipoints++;
   dist_since_last_eqpt = 0;

   for (i = 1; i < points->npts; i++) {
		int dx1 = points->pts[i].x - points->pts[i-1].x;
		int dy1 = points->pts[i].y - points->pts[i-1].y;
		int endx = 100 * points->pts[i-1].x;
		int endy = 100 * points->pts[i-1].y;
		remaining_seglen = isqrt(10000 * (dx1 * dx1 + dy1 * dy1));
		dist_to_next_eqpt = equidist - dist_since_last_eqpt;

		while (remaining_seglen >= dist_to_next_eqpt) {
			if (dx1 == 0) {
				/* x-coordinate stays the same */
				if (dy1 >= 0)
					endy += dist_to_next_eqpt;
				else
					endy -= dist_to_next_eqpt;
			} else {
				int slope = (100 * dy1 + dx1 / 2) / dx1;
				int tmp = isqrt(10000 + slope * slope);
				int dx = (100 * dist_to_next_eqpt + tmp / 2) / tmp;
				int dy = (slope * dx + 50) / 100;

				if (dy < 0) dy = -dy;
				if (dx1 >= 0)
					endx += dx;
				else
					endx -= dx;
				if (dy1 >= 0)
					endy += dy;
				else
					endy -= dy;
			}

			equipoints[nequipoints].x = (endx + 50) / 100;
			equipoints[nequipoints].y = (endy + 50) / 100;
			nequipoints++;
/*	    assert(nequipoints <= NCANONICAL);*/
			dist_since_last_eqpt = 0;
			remaining_seglen -= dist_to_next_eqpt;
			dist_to_next_eqpt = equidist;
		}

		dist_since_last_eqpt += remaining_seglen;
	}

   /* Take care of last equipoint. */
   if (nequipoints == NCANONICAL) {
		/* Good. */
   } else if (nequipoints == (NCANONICAL - 1)) {
		/* Make last original point the last equipoint. */
		equipoints[nequipoints] = points->pts[points->npts - 1];
	} else {
		/*	assert(false);*/
		return(-1);
	}

   points->npts = NCANONICAL;
   delete_pen_point_array(points->pts);
   points->pts = equipoints;
   return(0);
}

static int canonicalize_example_stroke(point_list *points) 
{
   int minx, miny, maxx, maxy, xrange, yrange, scale;

	/* Filter out points that are too close. */
   if (filter_points(points) != 0) return(-1);

   /* Must be at least two points! */
   if (points->npts < 2) {
		return(-1);
   }

   /* Scale up to avoid conversion errors. */
   get_bounding_box(points, &minx, &miny, &maxx, &maxy);
   xrange = maxx - minx;
   yrange = maxy - miny;
   scale = (((100 * xrange + CANONICAL_X / 2) / CANONICAL_X) >
				((100 * yrange + CANONICAL_Y / 2) / CANONICAL_Y))
				? (100 * CANONICAL_X + xrange / 2) / xrange
				: (100 * CANONICAL_Y + yrange / 2) / yrange;
	if (translate_points(points, minx, miny, scale, scale) != 0) {
		return(-1);
	}

   /* Compute an equivalent stroke with equi-distant points. */
   if (compute_equipoints(points) != 0) return(-1);

   /* Re-translate the points to the origin. */
   get_bounding_box(points, &minx, &miny, &maxx, &maxy);
   if (translate_points(points, minx, miny, 100, 100) != 0) {
		return(-1);
	}

   /* Store the x and y ranges in the point list. */
   xrange = maxx - minx;
   yrange = maxy - miny;
   points->xrange = xrange;
   points->yrange = yrange;

	return(0);
}

/*************************************************************
  Canonicalization routines
 *************************************************************/
static int canonicalize_examples(rClassifier *rec) 
{
   int i;
   int nclasses;

   /* Initialize canonical-example arrays. */
   for (i = 0; i < MAXSCLASSES; i++) {
		rec->canonex[i] = NULL;
   }

   /* Figure out number of classes. */
   for (nclasses = 0;
			  nclasses < MAXSCLASSES && rec->cnames[nclasses] != NULL;
			nclasses++) ;

   /* Canonicalize the examples for each class. */
   for (i = 0; i < nclasses; i++) {
		int j, k;
		int nex;
		point_list *pts, *tmp, *avg;
		int maxxrange, maxyrange;
		int minx, miny, maxx, maxy;
		int avgxrange, avgyrange, avgxoff, avgyoff, avgscale;

		/* Make a copy of the examples. */
		pts = NULL;
		tmp = rec->ex[i];
		for (nex = 0; tmp != NULL; nex++, tmp = tmp->next) {
			if ((pts = add_example(pts, tmp->npts, tmp->pts)) == NULL) {
				delete_examples(pts);
				return(-1);
			}
		}

		/* Canonicalize each example, and derive the max x and y ranges. */
		maxxrange = 0;
		maxyrange = 0;
		for (j = 0, tmp = pts; j < nex; j++, tmp = tmp->next) {
			if (canonicalize_example_stroke(tmp) != 0) {
				return(-1);
			}

			if (tmp->xrange > maxxrange) maxxrange = tmp->xrange;
			if (tmp->yrange > maxyrange) maxyrange = tmp->yrange;
		}

		/* Normalize max ranges. */
		if (((100 * maxxrange + CANONICAL_X / 2) / CANONICAL_X) >
			((100 * maxyrange + CANONICAL_Y / 2) / CANONICAL_Y)) {
			maxyrange = (maxyrange * CANONICAL_X + maxxrange / 2) / maxxrange;
			maxxrange = CANONICAL_X;
		} else {
			maxxrange = (maxxrange * CANONICAL_Y + maxyrange / 2) / maxyrange;
			maxyrange = CANONICAL_Y;
		}

		/* Re-scale each example to max ranges. */
		for (j = 0, tmp = pts; j < nex; j++, tmp = tmp->next) {
			int scalex = (tmp->xrange == 0) ? 100 : (100 * maxxrange + tmp->xrange / 2) / tmp->xrange;
			int scaley = (tmp->yrange == 0) ? 100 : (100 * maxyrange + tmp->yrange / 2) / tmp->yrange;
			if (translate_points(tmp, 0, 0, scalex, scaley) != 0) {
				delete_examples(pts);
				return(-1);
			}
		}

		/* Average the examples; leave average in first example. */
		avg = pts;				/* careful aliasing!! */
		for (k = 0; k < NCANONICAL; k++) {
			int xsum = 0;
			int ysum = 0;

			for (j = 0, tmp = pts; j < nex; j++, tmp = tmp->next) {
				xsum += tmp->pts[k].x;
				ysum += tmp->pts[k].y;
			}

			avg->pts[k].x = (xsum + j / 2) / j;
			avg->pts[k].y = (ysum + j / 2) / j;
		}

		/* Compute BB of averaged stroke and re-scale. */
		get_bounding_box(avg, &minx, &miny, &maxx, &maxy);
		avgxrange = maxx - minx;
		avgyrange = maxy - miny;
		avgscale = (((100 * avgxrange + CANONICAL_X / 2) / CANONICAL_X) >
				((100 * avgyrange + CANONICAL_Y / 2) / CANONICAL_Y))
				? (100 * CANONICAL_X + avgxrange / 2) / avgxrange
				: (100 * CANONICAL_Y + avgyrange / 2) / avgyrange;
		if (translate_points(avg, minx, miny, avgscale, avgscale) != 0) {
			delete_examples(pts);
			return(-1);
		}

		/* Re-compute the x and y ranges and center the stroke. */
		get_bounding_box(avg, &minx, &miny, &maxx, &maxy);
		avgxrange = maxx - minx;
		avgyrange = maxy - miny;
		avgxoff = -((CANONICAL_X - avgxrange + 1) / 2);
		avgyoff = -((CANONICAL_Y - avgyrange + 1) / 2);
		if (translate_points(avg, avgxoff, avgyoff, 100, 100) != 0) {
			delete_examples(pts);
			return(-1);
		}

		/* Create a point list to serve as the ``canonical representation. */
		if ((rec->canonex[i] = add_example(NULL, avg->npts, avg->pts)) == NULL) {
			delete_examples(pts);
			return(-1);
		}
		(rec->canonex[i])->xrange = maxx - minx;
		(rec->canonex[i])->yrange = maxy - miny;

		/* Compute dominant points of canonical representation. */
		rec->dompts[i] = compute_dominant_points(avg);

		/* Clean up. */
		delete_examples(pts);
	}

   /* Sanity check. */
   for (i = 0; i < nclasses; i++) {
		char *best_name = recognize_stroke(rec, rec->canonex[i]);

		if (best_name != rec->cnames[i])
			;
//			fprintf(stderr, "%s, best = %s\n", rec->cnames[i], best_name);
   }

   return(0);
}

/*************************************************************
  Digest-processing routines
 *************************************************************/
static int read_classifier_digest(rClassifier *rec) 
{
   int nclasses;
//   FILE *fp = NULL;
	DmOpenRef	fp = NULL;

   /* Try to open the corresponding digest file. */
   {
		char *clx_path;
		char *dot;

		/* Get a copy of the filename, with some room on the end. */
		/*	clx_path = safe_malloc(strlen(rec->file_name) + 5); */
		clx_path = allocate(Vstrlen(rec->file_name) + 5, char);
		Vstrcpy(clx_path, rec->file_name);


		// Truncate the path after the last dot. 
		dot = Vstrrchr(clx_path, '.');
		if (dot == NULL) { Vfree(clx_path); return(-1); }
		*(dot + 1) = 0;

		// Append the classifier-digest extension. 
		Vstrcat(clx_path, "clx");


		fp = Vfopen(clx_path, "rt");
		if (fp == NULL) { Vfree(clx_path); return(-1); }

		Vfree(clx_path);
   }

   /* Read-in the name and dominant points for each class. */
   for (nclasses = 0; !Vfeof(fp); nclasses++) {
		point_list *dpts = NULL;
		char class[BUFSIZ];
		int npts;
		int j;

//		if (Vfscanf2(fp, "%s %d", class, &npts) != 2) {
		if (Vfscanf2(fp, "%d %s", &npts, class) != 2) {
			if (Vfeof(fp)) break;

			goto failed;
		}
		rec->cnames[nclasses] = Vstrdup(class);

		/* Allocate a dominant-points list. */
		/* dpts = (point_list *)safe_malloc(sizeof(point_list)); */
		dpts = allocate(1, point_list);
		dpts->pts = make_pen_point_array((UInt16)npts);
		if (dpts->pts == NULL) goto failed;
		dpts->npts = npts;
		dpts->next = NULL;

		/* Read in each point. */
		for (j = 0; j < npts; j++) {
			int x, y;

			if (Vfscanf2(fp, "%d %d", &x, &y) != 2) goto failed;
			dpts->pts[j].x = x;
			dpts->pts[j].y = y;
		}

		/* Compute the chain-code. */
		compute_chain_code(dpts);

		/* Store the list in the rec data structure. */
		rec->dompts[nclasses] = dpts;

		continue;

failed:
		for (; nclasses >= 0; nclasses--) {
			if (rec->cnames[nclasses] != NULL) {
				Vfree(rec->cnames[nclasses]);
				rec->cnames[nclasses] = NULL;
			}
			if (rec->dompts[nclasses] != NULL) {
				delete_examples(rec->dompts[nclasses]);
				rec->dompts[nclasses] = NULL;
			}
		}
		if (dpts != NULL)
			delete_examples(dpts);
		Vfclose(fp);
		return(-1);
   }

   Vfclose(fp);
   return(0);
}

/*read_classifier_points-Read points so classifier can be extended.*/
static int 
//read_classifier_points(FILE* fd,int nclss,point_list** ex,char** cnames)
read_classifier_points(DmOpenRef fd,int nclss,point_list** ex,char** cnames)
{
   int i,j,k;
   char buf[BUFSIZ];
   int nex = 0;
   char* names[MAXSCLASSES];
   point_list* examples[MAXSCLASSES];
   pen_point* pts;
   int	npts;
//	int	pcounts;
	point_list *wexample;
	pen_point	*lpts;

   /*Initialize*/

   for( i = 0; i < MAXSCLASSES; i++ ) {
		names[i] = NULL;
		examples[i] = NULL;
   }

   /*Go thru classes.*/

/* ari */
/* fprintf(stderr, "Classes: [ "); */

   for( k = 0; k < nclss; k++ ) {
		/*Read class name and number of examples.*/
		if( Vfscanf2(fd,"%d %s",&nex,buf) != 2 ) {
			goto unallocate;
		}
	
		/*Save class name*/
		names[k] = Vstrdup(buf);

		wexample = (point_list *)Vmalloc((sizeof(point_list)*nex));
//printf ("[%d],[%x], [%d]\n", k, wexample, allocCounts);
/*
		lpts = (pen_point*)Vmalloc(100 * sizeof(pen_point) * nex);

		for( i = 0; i < 100*nex; i++ ) {
			lpts[i].time = 0;
			lpts[i].x = lpts[i].y = 0;
		}
*/
		/*Read examples.*/
//		pcounts = 0;
		for( i = 0; i < nex; i++ ) {
			/*Read number of points.*/
			if( Vfscanf(fd,"%d",&(npts)) != 1 ) {
				goto unallocate; /*Boy would I like exceptions!*/
			}
	    
			/*Allocate array for points.*/
			if( (pts = make_pen_point_array((UInt16)npts)) == NULL ) {
				goto unallocate;
			}
	    
			/*Read in points.*/
			for( j = 0; j < npts; j++ ) {
				int x,y;
				if( Vfscanf2(fd,"%d %d",&x,&y) != 2 ) {
					delete_pen_point_array(pts);
					goto unallocate;
				}
				pts[j].x = x;
				pts[j].y = y;
			}

			// add example here
			lpts = make_pen_point_array((UInt16)npts);
/*
			if ((pcounts+npts) > 100*nex ) {
				lpts = (pen_point*)Vrealloc(lpts, (pcounts+npts)*sizeof(pen_point));
				for( j = pcounts; j < (pcounts+npts); j++ ) {
					lpts[j].time = 0;
					lpts[j].x = lpts[j].y = 0;
				}
			}
*/
			wexample[i].npts = npts;
//			wexample[i].pts = &(lpts[pcounts]);
			wexample[i].pts = lpts;
			if ( i == (nex-1) )
				wexample[i].next = NULL;
			else
				wexample[i].next = &(wexample[i+1]);       //Order doesn't matter, so we stick on end.

		   //Copy points.
//			Vmemcpy(&(lpts[pcounts]), pts,npts * sizeof(pen_point));
			Vmemcpy(lpts, pts,npts * sizeof(pen_point));

			delete_pen_point_array(pts);
//			pcounts += npts;
		}
/*
		if ( pcounts < 100*nex )
			lpts = (pen_point*)Vrealloc(lpts, pcounts*sizeof(pen_point));
*/
		examples[k] = &(wexample[0]);
		//Vmemcpy (&(examples[k]), (wexample[0]), sizeof(point_list));
   }

   /*Transfer to recognizer.*/

   Vmemcpy(ex, examples, sizeof(examples));
   Vmemcpy(cnames, names, sizeof(names));

   return(0);

   /*Error. Deallocate memory and return.*/
unallocate:
   for( ; k >= 0; k-- ) {
		wdelete_examples(examples[k]);
/*
		if ( examples[k] ) {
			Vfree (examples[k]->pts);
			examples[k]->pts = NULL;
		}
*/
		Vfree(examples[k]);
//		delete_examples(examples[k]);
		Vfree(names[k]);
   }

	if ( lpts )
		Vfree (lpts);
	if ( wexample )
		Vfree (wexample);

//   error("Error in reading example points from classifier file");
   return(-1);
}

char _zdebug_flag[128];

#define Z(f) if(_zdebug_flag[f] > 0)
#define ZZ(f) if(_zdebug_flag[f] >= 2)
#define ZZZ(f) if(_zdebug_flag[f] >= 3)
#define ZZZZ(f) if(_zdebug_flag[f] >= 4)

sClassifier
sNewClassifier()
{
	register sClassifier sc = allocate(1, struct sclassifier);
	sc->nfeatures = -1;
	sc->nclasses = 0;
	sc->classdope = allocate(MAXSCLASSES, sClassDope);
	sc->w = NULL;
	return sc;
}

/*
 * Return a copy of a string
 */
char *
scopy(s)
char *s;
{
	register char *p = allocate(Vstrlen(s) + 1, char);
	char *Vstrcpy();
	(void) Vstrcpy(p, s);
	return p;
}

static sClassDope
sAddClass(sc, classname)
register sClassifier sc;
char *classname;
{
	register sClassDope scd;

	sc->classdope[sc->nclasses] = scd = allocate(1, struct sclassdope);
	scd->name = scopy(classname);
	scd->number = sc->nclasses;
	scd->nexamples = 0;
	scd->sumcov = NULL;
	++sc->nclasses;
	return scd;
}

Vector
InputVector(DmOpenRef f)
//FILE *f;
{
	register Vector v;
	register int i;
	char check[4];
	int nrows;

	if(Vfscanf2(f, "%1s %d", check, &nrows) != 2) {
//		exit_error("InputVector fscanf 1");
	    }
	if(check[0] != 'V') {
//		exit_error("InputVector check");
	    }
	v = NewVector(nrows);
	for(i = 0; i < nrows; i++)
		if(Vfscanf(f, "%lf", &v[i]) != 1) {
//			exit_error("InputVector fscanf 2");
		    }
	return v;
}

Matrix
InputMatrix(DmOpenRef f)
//FILE *f;
{
	register Matrix m;
	register int i, j;
	char check[4];
	int nrows, ncols;

	if(Vfscanf3(f, "%1s %d %d", check, &nrows, &ncols) != 3) {
//		exit_error("InputMatrix fscanf 1");
	    }
	if(check[0] != 'M') {
//		exit_error("InputMatrix check");
	    }
	m = NewMatrix(nrows, ncols);
	for(i = 0; i < nrows; i++)
		for(j = 0; j < ncols; j++)
			if(Vfscanf(f, "%lf", &m[i][j]) != 1) {
//				exit_error("InputMatrix fscanf 2");
			    }

	return m;
}

sClassifier
sRead(DmOpenRef infile)
//FILE *infile;
{
	int i, n;
	register sClassifier sc;
	register sClassDope scd;
	char buf[100];

	
//	Z('a')  printf("Reading classifier \n");
	sc = sNewClassifier();
	Vfgets(buf, 100, infile);
	if(Vsscanf(buf, "%d", &n) != 1) {
//	    error("Input error in classifier file");
	    sFreeClassifier(sc);
	    return(NULL);
	}
//	Z('a')  printf("  %d classes \n", n);
	for(i = 0; i < n; i++) {
		Vfscanf(infile, "%s", buf);
		scd = sAddClass(sc, buf);
//		Z('a'); printf("  %s \n", scd->name);
	}
	sc->w = allocate(sc->nclasses, Vector);
	for(i = 0; i < sc->nclasses; i++) {
		scd = sc->classdope[i];
		scd->average = InputVector(infile);
		scd->sumcov = InputMatrix(infile);
		sc->w[i] = InputVector(infile);
	}
	sc->cnst = InputVector(infile);
	sc->invavgcov = InputMatrix(infile);
//	Z('a'); printf("\n");
	return sc;
}

/*read_classifier-Read a classifier file.*/
//static int read_classifier(FILE* fd,rClassifier* rc)
static int read_classifier(DmOpenRef fd,rClassifier* rc)
{
   sClassifier sc;
    
   li_err_msg = NULL;

//printf ("1: allocCounts[%d]\n", allocCounts);
   /*Read in classifier file.*/
   if( (sc = sRead(fd)) == NULL ) {
		return(-1);
   }
    
//printf ("2: allocCounts[%d]\n", allocCounts);
   /*Read in the example points, so classifier can be extended.*/
   if( read_classifier_points(fd,sc->nclasses,rc->ex,rc->cnames) != 0 ) {
		sFreeClassifier(sc);
		return(-1);
   }

//printf ("3: allocCounts[%d]\n", allocCounts);
   /*Transfer sClassifier to the rClassifier*/
   rc->sc = sc;
    
   return(0);
}

/*
 * API Functions
 */

/*li_recognizer_load-Load a classifier file.*/
static int li_recognizer_load(recognizer r,char* dir,char* filename)
{ 
//   FILE *fd;
	DmOpenRef	fd;
   char* pathname;
   li_recognizer* rec;
   rClassifier* rclass;

   rec = (li_recognizer*)r->recognizer_specific;

   /*Make sure recognizer's OK*/
   if( !CHECK_LI_MAGIC(rec) ) {
		li_err_msg = "Not a LI recognizer";
		return(-1);
   }

   rclass = &(rec->li_rc);

   /*Check parameters.*/
   if( filename == NULL ) {
		li_err_msg = "Invalid parameters";
		return(-1);
   }

   /*We let the directory be null.*/

   if( dir == NULL || (int)Vstrlen(dir) <= 0 ) {
		dir = ".";
   }

   /*Make full pathname and check filename*/
   /* pathname = (char*)safe_malloc(strlen(dir) + strlen(filename) + 2)); */

   pathname = allocate(Vstrlen(dir) + Vstrlen(filename) + 2, char);
   if( file_path(dir,filename,pathname) == -1 ) {
		Vfree(pathname);
		li_err_msg = "Not a LI recognizer classifier file";
		return(-1);
   }

   /* Try to short-circuit the full classifier-file processing. */
   rclass->file_name = pathname;
   if (read_classifier_digest(rclass) == 0)
		return(0);
   rclass->file_name = NULL;

   /*Open the file*/
   if( (fd = Vfopen(pathname,"r")) == NULL ) {
		Vfree(pathname);
		li_err_msg = "Can't open classifier file";
/* ari */
	/* fprintf(stderr, "Trying to open %s.\n", pathname); */
		return(-1);

   }

   /*If rClassifier is OK, then delete it first.*/
   if( rclass->file_name != NULL ) {
      free_rClassifier(rclass);
   }

   /*Read classifier.*/
   if( read_classifier(fd,rclass) < 0 ) {
		Vfree(pathname);
		return(-1);
   }

   /*Close file.*/
   Vfclose(fd);

   /*Add classifier name.*/
   rclass->file_name = pathname;

   /* Canonicalize examples. */
   if (canonicalize_examples(rclass) != 0) {
		Vfree(pathname);
		rclass->file_name = NULL;
		return(-1);
   }

   return(0);
}

/*li_recognizer_save-Save a classifier file.*/
static int li_recognizer_save(recognizer r,char* dir,char* filename)
{ 
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Saving is not supported by the LI recognizer";

	return(-1);
}

static wordset
li_recognizer_load_dictionary(recognizer rec,char* directory,char* name)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Dictionaries are not supported by the LI recognizer";

	return(NULL);
}

static int
li_recognizer_save_dictionary(recognizer rec,
			       char* directory,
			       char* name,
			       wordset dict)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Dictionaries are not supported by the LI recognizer";

	return(-1);
}

static int
li_recognizer_free_dictionary(recognizer rec,wordset dict)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Dictionaries are not supported by the LI recognizer";

	return(-1);
}

static int
li_recognizer_add_to_dictionary(recognizer rec,letterset* word,wordset dict)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Dictionaries are not supported by the LI recognizer";

	return(-1);
}

static int
li_recognizer_delete_from_dictionary(recognizer rec,
				      letterset* word,
				      wordset dict)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Dictionaries are not supported by the LI recognizer";

	return(-1);
}

static char*
li_recognizer_error(recognizer rec)
{
   char* ret = li_err_msg;

   /*Check for LI recognizer.*/
   if( !CHECK_LI_MAGIC(rec->recognizer_specific) ) {
		li_err_msg = "Not a LI recognizer";
		return(NULL);
   }

   li_err_msg = NULL;

   return(ret);
}

static int 
li_recognizer_clear(recognizer r,Boolean delete_points_p)
{
   li_recognizer* rec; 

   rec = (li_recognizer*)r->recognizer_specific;

   /*Check for LI recognizer.*/
   if( !CHECK_LI_MAGIC(rec) ) {
		li_err_msg = "Not a LI recognizer";
		return(0);
   }
  
   return(0);
}

static int 
li_recognizer_set_context(recognizer r,rc* rec_xt)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Contexts are not supported by the LI recognizer";

	return(-1);
}

static rc*
li_recognizer_get_context(recognizer r)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Contexts are not supported by the LI recognizer";

	return(NULL);
}

static int 
li_recognizer_get_buffer(recognizer r, UInt32* nstrokes,pen_stroke** strokes)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Buffer get/set are not supported by the LI recognizer";

	return(-1);
}

static int 
li_recognizer_set_buffer(recognizer r,UInt32 nstrokes,pen_stroke* strokes)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Buffer get/set are not supported by the LI recognizer";

	return(-1);
}

static int
li_recognizer_translate(recognizer r,
			 UInt32 ncs,
			 pen_stroke* tps,
			 Boolean correlate_p,
			 Int32* nret,
			 rec_alternative** ret)
{
   char* clss = NULL;
   li_recognizer* rec; 
   int conf;
   rClassifier* rc;
      
   rec = (li_recognizer*)r->recognizer_specific;

   *nret = 0;
   *ret = NULL;

   /*Check for LI recognizer.*/
   if( !CHECK_LI_MAGIC(rec) ) {
		li_err_msg = "Not a LI recognizer";
		return(-1);
   }

   rc = &(rec->li_rc);

   /*Check for valid parameters.*/
   if (ncs < 1) {
		li_err_msg = "Invalid parameters: ncs";
		return(-1);
   }
   if( tps == NULL) {
		li_err_msg = "Invalid parameters: tps";
		return(-1);
   }
   if( nret == NULL) {
		li_err_msg = "Invalid parameters: nret";
		return(-1);
   }
   if( ret == NULL) {
		li_err_msg = "Invalid parameters: ret";
		return(-1);
   }

/*    if( ncs < 1 || tps == NULL || nret == NULL || ret == NULL) {
	li_err_msg = "Invalid parameters";
	return(-1);
    }
*/

    /*Check for null classifier. It must have at least one.*/
/*
    if( rec->li_rc.sc == NULL ) {
	li_err_msg = "No classifier";
	return(-1);
    }
*/

    /*
     * Go through the stroke array and recognize. Since this is a single
     *   stroke recognizer, each stroke is treated as a separate
     *   character or gesture. We allow only characters or gestures
     *   to be recognized at one time, since otherwise, handling
     *   the display of segmentation would be difficult. 
    */
   clss = recognize_internal(rc,tps,&conf);
   if (clss == NULL) {
/*
	li_err_msg = "unrecognized character";
	return(-1);
*/
		*nret = 1;
		return(0);
   }

   /*Return values.*/
   *nret = 1;
   return(*clss);
}

/*
 * rec_fn
*/
rec_fn* make_rec_fn_array(UInt32 size)
{
//    rec_fn* ri = (rec_fn*)safe_malloc((size + 1) * sizeof(rec_fn));
	rec_fn* ri = (rec_fn*)Vmalloc((size + 1) * sizeof(rec_fn));
	UInt32 i;

	for( i = 0; i < size; i++ ) {
		ri[i] = NULL;
	}

	ri[i] = NULL;

	return(ri);
}

/* getClasses and clearState are by Ari */
static int
recognizer_getClasses (recognizer r, char ***list, int *nc)
{
   int i, nclasses;
   li_recognizer* rec;
   sClassifier sc;
   char **ret;

   rec = (li_recognizer*)r->recognizer_specific;

   /*Check for LI recognizer.*/
   if( !CHECK_LI_MAGIC(rec) ) {
		li_err_msg = "Not a LI recognizer";
		return(-1);
   }
    
   sc = rec->li_rc.sc;
   *nc = nclasses = sc->nclasses;
   /*    ret = (char **) safe_malloc (nclasses * sizeof(char*));*/
   ret = allocate(nclasses, char*);

   for (i = 0; i < nclasses; i++) {
      ret[i] = rec->li_rc.cnames[i];   /* only the 1st char of the cname */
   }
   *list = ret;

	return	0;
}

static int
recognizer_clearState (recognizer r)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Clearing state is not supported by the LI recognizer";

	return(-1);
}

static Boolean isa_li(recognizer r)
{ 
	return(CHECK_LI_MAGIC(r)); 
}

static int
recognizer_train(recognizer r,rc* rec_xt,UInt32 nstrokes,
		    pen_stroke* strokes,rec_element* re,
		    Boolean replace_p)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Training is not supported by the LI recognizer";

	return(-1);
}

static rec_fn*
li_recognizer_get_extension_functions(recognizer rec)
{
   rec_fn* ret;

   /*Check for LI recognizer.*/
   if( !CHECK_LI_MAGIC(rec->recognizer_specific) ) {
		li_err_msg = "Not a LI recognizer";
		return(NULL);
   }

   ret = make_rec_fn_array(LI_NUM_EX_FNS);

/* ari -- clearState & getClasses are mine */
   ret[LI_GET_CLASSES] = (rec_fn)recognizer_getClasses;
   ret[LI_CLEAR] = (rec_fn)recognizer_clearState;
   ret[LI_ISA_LI] = (rec_fn)isa_li;
   ret[LI_TRAIN] = (rec_fn)recognizer_train;

   return(ret);
}

static char**
li_recognizer_get_gesture_names(recognizer r)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Gestures are not supported by the LI recognizer";

	return(NULL);
}

static xgesture
li_recognizer_set_gesture_action(recognizer r,
				  char* name,
				  xgesture fn,
				  void* wsinfo)
{
	/*This operation isn't supported by the LI recognizer.*/
	li_err_msg = "Gestures are not supported by the LI recognizer";

	return(NULL);
}

/*RECOGNIZER_INITIALIZE-Initialize the recognizer.*/
/* note from ari:  this expands via pre-processor to
 *
 * recognizer __recognizer_internal_initialize(rec_info* ri)
*/

RECOGNIZER_INITIALIZE(ri)
{
   recognizer r;
   li_recognizer* rec;
//   char* homedir;
//   char rechomedir[BUFSIZ];
   int i;

   /*Check that locale matches.*/

   if( Vstrcmp(ri->ri_locale,LI_SUPPORTED_LOCALE) != 0 ) {
		li_err_msg = "Not a supported locale";
/* fprintf(stderr, "Locale error.\n");*/
		return(NULL);
   }

   /*
    * Check that character sets match. Note that this is only approximate,
    * since the classifier file will have more information.
   */

   if( ri->ri_subset != NULL ) {
      for(i = 0; ri->ri_subset[i] != NULL; i++ ) {
			if( Vstrcmp(ri->ri_subset[i],UPPERCASE) != 0 &&
					Vstrcmp(ri->ri_subset[i],LOWERCASE) != 0  &&
					Vstrcmp(ri->ri_subset[i],DIGITS) != 0 &&
					Vstrcmp(ri->ri_subset[i],GESTURE) != 0 ) {
				li_err_msg = "Not a supported character set";
/* fprintf(stderr, "charset error.\n"); */
				return(NULL);
			}
      }
   }
	     
/* ari */
   r = make_recognizer(ri);
/* fprintf(stderr, "past make_recognizer.\n"); */

   if( r == NULL ) {
		li_err_msg = "Can't allocate storage";
		return(NULL);
   }

   /*Make a LI recognizer structure.*/
   /* rec = (li_recognizer*)safe_malloc(sizeof(li_recognizer))) == NULL ); */

   rec = allocate(1, li_recognizer);
   r->recognizer_specific = rec;

   rec->li_rc.file_name = NULL;
   rec->li_rc.sc = NULL;

   /*Initialize the recognizer struct.*/

   r->recognizer_load_state = li_recognizer_load;
   r->recognizer_save_state = li_recognizer_save;
   r->recognizer_load_dictionary = li_recognizer_load_dictionary;
   r->recognizer_save_dictionary = li_recognizer_save_dictionary;
   r->recognizer_free_dictionary = li_recognizer_free_dictionary;
   r->recognizer_add_to_dictionary = li_recognizer_add_to_dictionary;
   r->recognizer_delete_from_dictionary = li_recognizer_delete_from_dictionary;
   r->recognizer_error = li_recognizer_error;
   r->recognizer_translate = li_recognizer_translate;
   r->recognizer_get_context = li_recognizer_get_context;
   r->recognizer_set_context = li_recognizer_set_context;
   r->recognizer_get_buffer = li_recognizer_get_buffer;
   r->recognizer_set_buffer = li_recognizer_set_buffer;
   r->recognizer_clear = li_recognizer_clear;
   r->recognizer_get_extension_functions = 
      li_recognizer_get_extension_functions;
   r->recognizer_get_gesture_names = li_recognizer_get_gesture_names;
   r->recognizer_set_gesture_action = 
      li_recognizer_set_gesture_action;

   /*Initialize LI Magic Number.*/
   rec->li_magic = LI_MAGIC;

   /*Initialize rClassifier.*/
   rec->li_rc.file_name = NULL;

   for( i = 0; i < MAXSCLASSES; i++ ) {
		rec->li_rc.ex[i] = NULL;
		rec->li_rc.cnames[i] = NULL;
   }

   initialize(&rec->li_rc);

   /*Get rid of error message. Not needed here.*/
   li_err_msg = NULL;

   return(r);
}

/*RECOGNIZER_FINALIZE-Deallocate the recognizer, finalize.*/
RECOGNIZER_FINALIZE(r)
{
   li_recognizer* rec = (li_recognizer*)r->recognizer_specific;

   /*Make sure this is a li_recognizer first*/
   if( !CHECK_LI_MAGIC(rec) ) {
		li_err_msg = "Not a LI recognizer";
		return(-1);
   }

   /*Deallocate rClassifier resources.*/
   free_rClassifier(&(rec->li_rc));

   /*Deallocate the li_recognizer struct.*/
   Vfree(rec);

   /*Deallocate the recognizer*/
   delete_recognizer(r);

   return(0);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    filter_points
//
// DESCRIPTION: This routine filter out points that are too close.
//
// PARAMETERS:  (point_list *) points - stroke list of input point
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static int filter_points(point_list *points) 
{
   int filtered_npts;
   pen_point *filtered_pts = make_pen_point_array((UInt)points->npts);
   int i;

   if (filtered_pts == NULL) {
//		error("can't allocate memory in lialg_filter_points");
		return(-1);
   }

   filtered_pts[0] = points->pts[0];
   filtered_npts = 1;
   for (i = 1; i < points->npts; i++) {
		int j = filtered_npts - 1;
		int dx = points->pts[i].x - filtered_pts[j].x;
		int dy = points->pts[i].y - filtered_pts[j].y;
		int magsq = dx * dx + dy * dy;

		if (magsq >= DIST_SQ_THRESHOLD) {
			filtered_pts[filtered_npts] = points->pts[i];
			filtered_npts++;
		}
   }

   points->npts = filtered_npts;
   delete_pen_point_array(points->pts);
   points->pts = filtered_pts;
   return(0);
}

/*************************************************************
  Utility routines
 *************************************************************/
////////////////////////////////////////////////////////////////////////
// FUNCTION:    compute_pathlen_subset
//
// DESCRIPTION: This routine calculate the total length of stroke path.
//
// PARAMETERS:  (point_list *) stroke - stroke list of input point
//					 (int) start - start point of stroke list
//					 (int) end - end point of stroke list
//
// RETURNED:    Returns the length of stroke path.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static int compute_pathlen_subset(point_list *points,
					   int start, int end) 
{
   int pathlen;
   int i;

   pathlen = 0;
   for (i = start + 1; i <= end; i++) {
		int dx = points->pts[i].x - points->pts[i-1].x;
		int dy = points->pts[i].y - points->pts[i-1].y;
		int dist = isqrt(10000 * (dx * dx + dy * dy));
		pathlen += dist;
	}

   return(pathlen);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    compute_pathlen
//
// DESCRIPTION: This routine calculate the total length of stroke path.
//
// PARAMETERS:  (point_list *) stroke - stroke list of input point
//
// RETURNED:    Returns the length of stroke path.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static int compute_pathlen(point_list *points) 
{
	return(compute_pathlen_subset(points, 0, points->npts - 1));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    get_bounding_box
//
// DESCRIPTION: This routine calculate the bounding box of input stroke
//					 path
//
// PARAMETERS:  (point_list *) points - stroke list of input point
//					 (int *) pminx - horizontal coordinate of left-top corner
//									of bounding box
//					 (int *) pminy - vertical coordinate of left-top corner
//									of bounding box
//					 (int *) pmaxx - horizontal coordinate of right-bottom
//									corner of bounding box
//					 (int *) pmaxy - vertical coordinate of right-bottom
//									corner of bounding box
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static void get_bounding_box(point_list *points,
				    int *pminx, int *pminy,
				    int *pmaxx, int *pmaxy) 
{
   int minx, miny, maxx, maxy;
   int i;

   minx = maxx = points->pts[0].x;
   miny = maxy = points->pts[0].y;
   for (i = 1; i < points->npts; i++) {
		pen_point *pt = &(points->pts[i]);
		if (pt->x < minx) minx = pt->x;
		if (pt->x > maxx) maxx = pt->x;
		if (pt->y < miny) miny = pt->y;
		if (pt->y > maxy) maxy = pt->y;
   }

   *pminx = minx;
   *pminy = miny;
   *pmaxx = maxx;
   *pmaxy = maxy;
}

/* scalex and scaley are x 100. */
/* Note that this does NOT update points->xrange and points->yrange! */
////////////////////////////////////////////////////////////////////////
// FUNCTION:    translate_points
//
// DESCRIPTION: This routine calculate the bounding box of input stroke
//					 path
//
// PARAMETERS:  (point_list *) points - stroke list of input point
//					 (int) minx - horizontal coordinate of left-top corner
//									of bounding box
//					 (int) miny - vertical coordinate of left-top corner
//									of bounding box
//					 (int) scalex - scaling rate of horizontal direction
//					 (int) scaley - scaling rate of vertical direction
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static int translate_points(point_list *points,
				   int minx, int miny,
				   int scalex, int scaley) 
{
   int i;

   for (i = 0; i < points->npts; i++) {
		points->pts[i].x = ((points->pts[i].x - minx) * scalex + 50) / 100;
		points->pts[i].y = ((points->pts[i].y - miny) * scaley + 50) / 100;
   }

   return(0);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    preprocess_stroke
//
// DESCRIPTION: This routine is main recognition routine.
//
// PARAMETERS:  (point_list *) points - stroke list of input point
//
// RETURNED:    Returns the resulting character.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static int preprocess_stroke(point_list *points) 
{
   int minx, miny, maxx, maxy, xrange, yrange, scale, xoff, yoff;

   // Scale up to avoid conversion errors. 
   get_bounding_box(points, &minx, &miny, &maxx, &maxy);
   xrange = maxx - minx;
   yrange = maxy - miny;
   scale = ( ((100 * xrange + CANONICAL_X / 2) / CANONICAL_X) > 
      ((100 * yrange + CANONICAL_Y / 2) / CANONICAL_Y))
      ? (100 * CANONICAL_X + xrange / 2) / xrange
      : (100 * CANONICAL_Y + yrange / 2) / yrange;

	if (translate_points(points, minx, miny, scale, scale) != 0)
		return(-1);

   // Center the stroke. 
   get_bounding_box(points, &minx, &miny, &maxx, &maxy);
   xrange = maxx - minx;
   yrange = maxy - miny;
   xoff = -((CANONICAL_X - xrange + 1) / 2);
   yoff = -((CANONICAL_Y - yrange + 1) / 2);
   if (translate_points(points, xoff, yoff, 100, 100) != 0) return(-1);

   // Store the x and y ranges in the point list. 
   xrange = maxx - minx;
   yrange = maxy - miny;
   points->xrange = xrange;
   points->yrange = yrange;

   return(0);
}

/* This implementation is due to Kenny Hoff. */
////////////////////////////////////////////////////////////////////////
// FUNCTION:    bresline
//
// DESCRIPTION: This routine compute the dominant points
//
// PARAMETERS:  (point_list *) points - stroke list of input point
//
// RETURNED:    Returns the point list of result
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static void bresline(pen_point *startpt, pen_point *endpt,
			    point_list *newpts, int *j) 
{
   int Ax, Ay, Bx, By, dX, dY, Xincr, Yincr;

   Ax = startpt->x;
   Ay = startpt->y;
   Bx = endpt->x;
   By = endpt->y;

   /* INITIALIZE THE COMPONENTS OF THE ALGORITHM THAT ARE NOT AFFECTED */
   /* BY THE SLOPE OR DIRECTION OF THE	LINE */
   dX = Vabs(Bx-Ax);	/* store the change in X and Y of the line endpoints */
   dY = Vabs(By-Ay);

   /* DETERMINE "DIRECTIONS" TO INCREMENT X AND Y (REGARDLESS OF DECISION) */
   if (Ax > Bx) { Xincr=-1; } else { Xincr=1; }    /* which direction in X? */
   if (Ay > By) { Yincr=-1; } else { Yincr=1; }    /* which direction in Y? */

   /* DETERMINE INDEPENDENT VARIABLE (ONE THAT ALWAYS INCREMENTS BY 1 (OR -1) ) */
   /* AND INITIATE APPROPRIATE LINE DRAWING ROUTINE (BASED ON FIRST OCTANT */
   /* ALWAYS). THE X AND Y'S MAY BE FLIPPED IF Y IS THE INDEPENDENT VARIABLE. */
   if (dX >= dY) {	    /* if X is the independent variable */
		int dPr	= dY<<1;	    /* amount to increment decision if right is chosen (always) */
		int dPru = dPr - (dX<<1);   /* amount to increment decision if up is chosen */
		int P =	dPr - dX;	    /* decision variable start value */

		/* process each point in the line one at a time (just use dX) */
		for (; dX>=0; dX--) {
			newpts->pts[*j].x = Ax;
			newpts->pts[*j].y = Ay;
			(*j)++;

			if (P > 0) {	/* is the pixel	going right AND	up? */
				Ax+=Xincr;	/* increment independent variable */
				Ay+=Yincr;	/* increment dependent variable */
				P+=dPru;	/* increment decision (for up) */
			} else {		/* is the pixel just going right? */
				Ax+=Xincr;	/* increment independent variable */
				P+=dPr;		/* increment decision (for right) */
			}
		}
   } else {		    /* if Y is the independent variable */
		int dPr	= dX<<1;	    /* amount to increment decision if right is chosen (always) */
		int dPru = dPr - (dY<<1);   /* amount to increment decision if up is chosen */
		int P  = dPr - dY;	    /* decision variable start value */

		/* process each point in the line one at a time (just use dY) */
		for (; dY>=0; dY--) {
			newpts->pts[*j].x = Ax;
			newpts->pts[*j].y = Ay;
			(*j)++;
	
			if (P > 0) {	/* is the pixel going up AND right? */
				Ax+=Xincr;	/* increment dependent variable */
				Ay+=Yincr;	/* increment independent variable */
				P+=dPru;	/* increment decision (for up) */
			} else {		/* is the pixel just going up? */
				Ay+=Yincr;	/* increment independent variable */
				P+=dPr;		/* increment decision (for right) */
			}
		}
   }
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    compute_unit_chain_code
//
// DESCRIPTION: This routine compute the dominant points
//
// PARAMETERS:  (point_list *) pts - stroke list of input point
//
// RETURNED:    Returns the point list of result
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static void compute_unit_chain_code(point_list *pts) 
{
   int i;

   for (i = 0; i < (pts->npts - 1); i++) {
		pen_point *startpt = &(pts->pts[i]);
		pen_point *endpt = &(pts->pts[i+1]);
		int dx = endpt->x - startpt->x;
		int dy = endpt->y - startpt->y;
		int dircode = lialg_dctbl[dx+1][dy+1];

/*	assert(dircode < 8);*/
		startpt->chaincode = dircode;
   }
}

/* Input points are assumed to be integer-valued! */
////////////////////////////////////////////////////////////////////////
// FUNCTION:    interpolate_points
//
// DESCRIPTION: This routine compute the dominant points
//
// PARAMETERS:  (point_list *) points - stroke list of input point
//
// RETURNED:    Returns the point list of result
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static point_list *interpolate_points(point_list *points) 
{
   int i, j;
   int maxpts;
   point_list *newpts;

   /* Compute an upper-bound on the number of interpolated points. */
   maxpts = 0;
   for (i = 0; i < (points->npts - 1); i++) {
		pen_point *pta = &(points->pts[i]);
		pen_point *ptb = &(points->pts[i+1]);
		maxpts += Vabs(pta->x - ptb->x) + Vabs(pta->y - ptb->y);
   }

   /* Allocate an array of the requisite size. */
   maxpts += points->npts;
   /* newpts = (point_list *)safe_malloc(sizeof(point_list)); */
   newpts = allocate(1, point_list);
   newpts->pts = make_pen_point_array((UInt)maxpts);
   if (newpts->pts == NULL) {
		Vfree(newpts);
		return(NULL);
   }
   newpts->npts = maxpts;
   newpts->next = NULL;

   /* Interpolate each of the segments. */
   j = 0;
   for (i = 0; i < (points->npts - 1); i++) {
		pen_point *startpt = &(points->pts[i]);
		pen_point *endpt = &(points->pts[i+1]);

		bresline(startpt, endpt, newpts, &j);

		j--;	/* end point gets recorded as start point of next segment! */
   }

   /* Add-in last point. */
   newpts->pts[j++] = points->pts[points->npts - 1];
   newpts->npts = j;

   /* Compute the chain code for P (the list of points). */
   compute_unit_chain_code(newpts);

   return(newpts);
}

static int *compute_contour_angle_set(point_list *pts, region_list *regions) 
{
   int *V = NULL;
   region_list *curr_reg, *prev_reg;
   int i;

   //    V = (int *)safe_malloc(pts->npts * sizeof(int));
   V = allocate(pts->npts, int);
   V[0] = 18000;
   for (curr_reg = regions; curr_reg != NULL;
	    prev_reg = curr_reg, curr_reg = curr_reg->next) {
		for (i = curr_reg->start; i <= curr_reg->end; i++) {
			if (curr_reg->type == RGN_PLAIN) {
				V[i] = 18000;
			} else {
#ifdef	notdef
		/* XXX - eliminate floating point */
				region_list *next_reg = curr_reg->next;
				int b = curr_reg->start;
				int h = prev_reg->start;
				int t = next_reg->end;
				int pts_before = i - h;
				int pts_after = t - i;
				int min_pts = (pts_before < pts_after) ? pts_before : pts_after;
				int k = (min_pts < T_ONE) ? T_ONE:(min_pts > T_TWO) ? T_TWO:min_pts;
				float sum = 0.0;
				int	j;

				for (j = 1; j <= k; j++) {
					int ptA = i - j;
					int ptB = i + j - 1;
					int d_A = pts->pts[ptA].chaincode;
					int d_B = pts->pts[ptB].chaincode;
					int a_i;

					if (d_A < d_B)
						d_A += 8;

					a_i = (d_A - d_B) % 8;

					/* convert to radians */
					if (a_i == 4 && curr_reg->type == RGN_CONVEX)
						sum += M_2_PI;
					else
						sum += (float)((12 - a_i) % 8) / 4.0 * M_PI;
				}
				V[i] = sum / (float)k;
#else
				/* For now, simply choose the mid-point. */
				int isMidPt = (i == (curr_reg->start +
				     (curr_reg->end - curr_reg->start) / 2));
				V[i] = (curr_reg->type == RGN_CONVEX)
					? (isMidPt ? 18000 : 0)
					: (isMidPt ? 0 : 18000);
#endif
			}
		}
   }
   V[pts->npts - 1] = 18000;

   return(V);
}

static void compute_chain_code(point_list *pts) 
{
   int i;

   for (i = 0; i < (pts->npts - 1); i++) {
		pen_point *startpt = &(pts->pts[i]);
		pen_point *endpt = &(pts->pts[i+1]);
		int dx = endpt->x - startpt->x;
		int dy = endpt->y - startpt->y;
		int tmp = quadr(likeatan(dy, dx));
		int dircode = (12 - tmp) % 8;

		startpt->chaincode = dircode;
   }
}

static point_list *compute_dompts(point_list *pts, region_list *regions) 
{
   point_list *dpts = NULL;
   int ndpts;
   int *cas = NULL;
   int nonplain;
   region_list *r;

	/* Compute contour angle set. */
   cas = compute_contour_angle_set(pts, regions);
/*    assert(cas != NULL);*/

   /* Dominant points include:  start_pt, end_pt, extrema_of_non_plain_regions, midpts of the preceding. */
   nonplain = 0;
   for (r = regions; r != NULL; r = r->next)
		if (r->type != RGN_PLAIN) nonplain++;
   
	ndpts = 2 * (2 + nonplain) - 1;
   /* dpts = (point_list *)safe_malloc(sizeof(point_list)); */
   dpts = allocate(1, point_list);
   dpts->pts = make_pen_point_array((UInt)ndpts);
   if (dpts->pts == NULL) {
		Vfree(dpts);
		return(NULL);
   }
   dpts->npts = ndpts;
   dpts->next = NULL;

	/* Pick out dominant points. */
   {
		region_list *curr;
		int dp;
		int previx;
		int currix;

		/* Record start point. */
		dp = 0;
		previx = 0;
		dpts->pts[dp++] = pts->pts[previx];

		for (curr = regions; curr != NULL; curr = curr->next)
			if (curr->type != RGN_PLAIN) {
				int max_v = 0;
				int min_v = MAXINT;
				int max_ix = -1;
				int min_ix = -1;
				int i;

				for (i = curr->start; i <= curr->end; i++) {
					int v = cas[i];
					if (v > max_v) { max_v = v; max_ix = i; }
					if (v < min_v) { min_v = v; min_ix = i; }
				}

				currix = (curr->type == RGN_CONVEX ? max_ix : min_ix);
				/* Record midpoint. */
				dpts->pts[dp++] = pts->pts[previx + (currix - previx) / 2];

				/* Record extreme point. */
				dpts->pts[dp++] = pts->pts[currix];

				previx = currix;
			}

		/* Record last mid-point and end point. */
		currix = pts->npts - 1;
		dpts->pts[dp++] = pts->pts[previx + (currix - previx) / 2];
		dpts->pts[dp++] = pts->pts[currix];
	}

	/* Compute chain-code. */
	compute_chain_code(dpts);
	Vfree(cas);
	return(dpts);
}

static void compute_lpf_parameters() 
{
   int i;

   for (i = LP_FILTER_WIDTH; i >= 0; i--) {
		float x = (float)(0.04 * (i * i));
//#ifdef ARM_LINUX
		double tmp = 100.0 * Vexp((double)x);
//#else
//		float tmp = 100.0 * expf(x);
//#endif
//		int wt = rint((double)tmp);
		int wt = (int)tmp;

		lialg_lpfwts[LP_FILTER_WIDTH - i] = wt;
		lialg_lpfwts[LP_FILTER_WIDTH + i] = wt;
	}
   lialg_lpfconst = 0;
   for (i = 0; i < (2 * LP_FILTER_WIDTH + 1); i++) {
		lialg_lpfconst += lialg_lpfwts[i];
	}
}

static region_list *compute_regions(point_list *pts) 
{
   region_list *regions = NULL;
   region_list *curr_reg = NULL;
   int *R[2 + LP_FILTER_ITERS];
   int *junk;
   int *curr, *next;
   int i, j;

   /* Initialize low-pass filter parameters if necessary. */
   if (lialg_lpfconst == -1)
		compute_lpf_parameters();

   /* Allocate a 2 x pts->npts array for use in computing the (filtered) Angle set, A_n. */
   /*    junk = (int *)safe_malloc((2 + LP_FILTER_ITERS) * pts->npts * sizeof(int)); */
   junk = allocate((2 + LP_FILTER_ITERS) * pts->npts, int);
   for (i = 0; i < (2 + LP_FILTER_ITERS); i++)
		R[i] = junk + (i * pts->npts);
   curr = R[0];

   /* Compute the Angle set, A, in the first element of array R. */
   /* Values in R are in degrees, x 100. */
   curr[0] = 18000;				/* a_0 */
   for (i = 1; i < (pts->npts - 1); i++) {
		int d_i = pts->pts[i].chaincode;
		int d_iminusone = pts->pts[i-1].chaincode;
		int a_i;

		if (d_iminusone < d_i)
			d_iminusone += 8;

		a_i = (d_iminusone - d_i) % 8;

		/* convert to degrees, x 100 */
		curr[i] = ((12 - a_i) % 8) * 45 * 100;
   }
   curr[pts->npts - 1]	= 18000;		/* a_L-1 */

   /* Perform a number of filtering iterations. */
   next = R[1];
   for (j = 0; j < LP_FILTER_ITERS; j++, curr = R[j], next = R[j+1]) {
		for (i = 0; i < pts->npts; i++) {
			int k;

			next[i] = 0;

			for (k = i - LP_FILTER_WIDTH; k <= i + LP_FILTER_WIDTH; k++) {
				int oldval = (k < 0 || k >= pts->npts) ? 18000 : curr[k];
				next[i]	+= oldval * lialg_lpfwts[k - (i	- LP_FILTER_WIDTH)];	/* overflow? */
			}

			next[i] /= lialg_lpfconst;
		}
   }

   /* Do final thresholding around PI. */
   /* curr and next are set-up correctly at end of previous loop! */
   for (i = 0; i < pts->npts; i++) {
		next[i] = (Vabs(curr[i] - 18000) < LP_FILTER_THLD) ? 18000 : curr[i];
   }

   curr = next;

   /* Do the region segmentation. */
   {
		int start, end;
		int currtype;

#define	RGN_TYPE(val)\
    (((val) == 18000)\
	? RGN_PLAIN\
	: ((val) < 18000 ? RGN_CONCAVE : RGN_CONVEX))

		start = 0;
		currtype = RGN_TYPE(curr[0]);
		/*	regions = (region_list *)safe_malloc(sizeof(region_list));*/
		regions = allocate(1, region_list);
		curr_reg = regions;
		curr_reg->start = start;
		curr_reg->end = 0;
		curr_reg->type = currtype;
		curr_reg->next = NULL;

		for (i = 1; i < pts->npts; i++) {
		   int nexttype = RGN_TYPE(curr[i]);

		   if (nexttype != currtype) {
				region_list *next_reg = NULL;

				end = i - 1;
				curr_reg->end = end;

				start = i;
				currtype = nexttype;
				/* next_reg = (region_list *)safe_malloc(sizeof(region_list));*/
				next_reg = allocate(1, region_list);
				next_reg->start = start;
				next_reg->end = 0;
				next_reg->type = nexttype;
				next_reg->next = NULL;
	
				curr_reg->next = next_reg;
				curr_reg = next_reg;
			}
		}
		end = i - 1;
		curr_reg->end = end;

		/* Filter out convex/concave regions that are too short. */
		for (curr_reg = regions; curr_reg; curr_reg = curr_reg->next)
		   if (curr_reg->type == RGN_PLAIN) {
				region_list *next_reg;

				for (next_reg = curr_reg->next;
						next_reg != NULL &&
						(next_reg->end - next_reg->start) < LP_FILTER_MIN;
						next_reg = curr_reg->next) {
			/* next_reg must not be plain, and it must be followed by a plain */
			/* assert(next_reg->type != RGN_PLAIN); */
			/* assert(next_reg->next != NULL && (next_reg->next)->type == RGN_PLAIN); */

					curr_reg->next = (next_reg->next)->next;
					curr_reg->end = (next_reg->next)->end;

					Vfree(next_reg->next);
					Vfree(next_reg);
				}
			}

		/* Add-in pseudo-extremes. */
		{
			region_list *tmp, *prev_reg;

			tmp = regions;
			regions = NULL;
			prev_reg = NULL;
		   for (curr_reg = tmp; curr_reg; curr_reg = curr_reg->next) {
				if (curr_reg->type == RGN_PLAIN) {
					int arclen = compute_pathlen_subset(pts,
								curr_reg->start,
								curr_reg->end);
					int dx = pts->pts[curr_reg->end].x -
						pts->pts[curr_reg->start].x;
					int dy = pts->pts[curr_reg->end].y -
						pts->pts[curr_reg->start].y;
					int chordlen = isqrt(10000 * (dx * dx + dy * dy));
					int atcr = (chordlen == 0) ? 0 : (100 * arclen + chordlen / 2) / chordlen;

					/* Split region if necessary. */
					if (arclen >= PE_AL_THLD && atcr >= PE_ATCR_THLD) {
						int mid = curr_reg->start + (curr_reg->end - curr_reg->start) / 2;
						int end = curr_reg->end;
						region_list *saved_next = curr_reg->next;

						curr_reg->end = mid - 1;
						if (prev_reg == NULL)
							regions = curr_reg;
						else
							prev_reg->next = curr_reg;
						prev_reg = curr_reg;

						/* curr_reg = (region_list *)safe_malloc(sizeof(region_list));*/
						curr_reg = allocate(1, region_list);
						curr_reg->start = mid;
						curr_reg->end = mid;
						curr_reg->type = RGN_PSEUDO;
						curr_reg->next = NULL;
						prev_reg->next = curr_reg;
						prev_reg = curr_reg;

						/* curr_reg = (region_list *)safe_malloc(sizeof(region_list)); */
						curr_reg = allocate(1, region_list);
						curr_reg->start = mid + 1;
						curr_reg->end = end;
						curr_reg->type = RGN_PLAIN;
						curr_reg->next = NULL;
						prev_reg->next = curr_reg;
						prev_reg = curr_reg;

						curr_reg->next = saved_next;
						continue;
					}
				}

				if (prev_reg == NULL)
					regions = curr_reg;
				else
					prev_reg->next = curr_reg;
				prev_reg = curr_reg;
			}
		}
   }

   Vfree(junk);
   return(regions);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    compute_dominant_points
//
// DESCRIPTION: This routine compute the dominant points
//
// PARAMETERS:  (point_list *) points - stroke list of input point
//
// RETURNED:    Returns the point list of result
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static point_list *compute_dominant_points(point_list *points) 
{
   point_list *ipts = NULL;
   region_list *regions = NULL;
   point_list *dpts = NULL;

   /* Interpolate points. */
   ipts = interpolate_points(points);
   if (ipts == NULL) return(NULL);

   /* Compute regions. */
   regions = compute_regions(ipts);

   /* Compute dominant points. */
   dpts = compute_dompts(ipts, regions);

   /* Delete region data structure. */
   {
		region_list *curr, *next;
		for (curr = regions; curr != NULL; ) {
			next = curr->next;
			Vfree(curr);
			curr = next;
		}
   }

   delete_examples(ipts);
   return(dpts);
}

static int compute_similarity(point_list *input_dompts,
				     point_list *curr_dompts) 
{
   int sim = 0;
   point_list *A, *B;
   int N, M;
   int **G = NULL;
   int *junk = NULL;
   int i, j;

   /* A is the	longer sequence, length	N. */
   /* B is the shorter sequence, length M. */
   if (input_dompts->npts >= curr_dompts->npts) {
		A = input_dompts;
		N = input_dompts->npts;
		B = curr_dompts;
		M = curr_dompts->npts;
   } else {
		A = curr_dompts;
		N = curr_dompts->npts;
		B = input_dompts;
		M = input_dompts->npts;
   }

   /* Allocate and initialize the Gain matrix, G. */
   /* The size of G is M x (N + 1). */
   /* Note that row 0 is unused. */
   /* Similarities are x 10. */
   {
      /*	G = (int **)safe_malloc(M * sizeof(int *));*/
      G = allocate(M, int *);
      /*	junk = (int *)safe_malloc(M * (N + 1) * sizeof(int)); */
		junk = allocate(M * (N + 1), int);
		for (i = 0; i < M; i++)
			G[i] = junk + (i * (N + 1));

		for (i = 1; i < M; i++) {
			int bval = B->pts[i-1].chaincode;

			/* Source column. */
			G[i][0] = 0;

			for (j = 1; j < N; j++) {
				int aval = A->pts[j-1].chaincode;
				int diff = Vabs(bval - aval);
				if (diff > 4) diff = 8 - diff;

				G[i][j] = (diff == 0) ? 10 : (diff == 1) ? 6 : 0;
			}

			/* Sink column. */
			G[i][N] = 0;
		}
   }

   /* Do the DP algorithm. */
   /* Proceed in column order, from highest column to the lowest. */
   /* Within each column, proceed from the highest row to the lowest. */
   /* Skip the highest column. */
   {
		for (j = N - 1; j >= 0; j--)
			for (i = M - 1; i > 0; i--) {
				int max = G[i][j + 1];

				if (i < (M - 1)) {
					int tmp = G[i + 1][j + 1];
					if (tmp > max) max = tmp;
				}

				G[i][j] += max;
			}

		sim = (10 * G[1][0] + (N - 1) / 2) / (N - 1);
   }

   if (G != NULL) {
		Vfree(G);
		G = NULL;
	}
   if (junk != NULL) {
		Vfree(junk);
		junk = NULL;
	}
   return(sim);
}

static int compute_distance(point_list *input_dompts,
				   point_list *curr_dompts) 
{
   int dist = MAX_DIST;
   point_list *A, *B;
   int N, M;
   int **C = NULL;
   int *junk = NULL;
   int *BE = NULL;
   int *TE = NULL;
   int i, j;

   /* A is the	longer sequence, length	N. */
   /* B is the shorter sequence, length M. */
   if (input_dompts->npts >= curr_dompts->npts) {
		A = input_dompts;
		N = input_dompts->npts;
		B = curr_dompts;
		M = curr_dompts->npts;
   } else {
		A = curr_dompts;
		N = curr_dompts->npts;
		B = input_dompts;
		M = input_dompts->npts;
   }

   /* Construct the helper vectors, BE and TE, which say for each column */
   /* what are the ``bottom'' and ``top'' rows of interest. */
   {
        /*	BE = (int *)safe_malloc((N + 1) * sizeof(int));*/
		BE = allocate((N + 1), int);
	/*	TE = (int *)safe_malloc((N + 1) * sizeof(int)); */
		TE = allocate((N + 1), int);

		for (j = 1; j <= N; j++) {
			int bot, top;

			bot = j + (M - DP_BAND);
			if (bot > M) bot = M;
			BE[j] = bot;

			top = j - (N - DP_BAND);
			if (top < 1) top = 1;
			TE[j] = top;
		}
   }

   /* Allocate and initialize the Cost matrix, C. */
   /* The size of C is (M + 1) x (N + 1). */
   /* Note that row and column 0 are unused. */
   /* Costs are x 100. */
   {
      /*	C = (int **)safe_malloc((M + 1) * sizeof(int *)); */
		C = allocate((M + 1), int *);
		/*	junk = (int *)safe_malloc((M + 1) * (N + 1) * sizeof(int)); */
		junk = allocate((M + 1) * (N + 1), int);
		for (i = 0; i <= M; i++)
			C[i] = junk + (i * (N + 1));

		for (i = 1; i <= M; i++) {
			int bx = B->pts[i-1].x;
			int by = B->pts[i-1].y;

			for (j = 1; j <= N; j++) {
				int ax = A->pts[j-1].x;
				int ay = A->pts[j-1].y;
				int dx = bx - ax;
				int dy = by - ay;
				int dist = isqrt(10000 * (dx * dx + dy * dy));

				C[i][j] = dist;
			}
		}
   }

   /* Do the DP algorithm. */
   /* Proceed in column order, from highest column to the lowest. */
   /* Within each column, proceed from the highest row to the lowest. */
   {
		for (j = N; j > 0; j--)
			for (i = M; i > 0; i--) {
				int min = MAX_DIST;

				if (i > BE[j] || i < TE[j] || (j == N && i == M))
					continue;

				if (j < N) {
					if (i >= TE[j+1]) {
						int tmp = C[i][j+1];
						if (tmp < min) min = tmp;
					}

					if (i < M) {
						int tmp = C[i+1][j+1];
						if (tmp < min) min = tmp;
					}
				}

				if (i < BE[j]) {
					int tmp = C[i+1][j];
					if (tmp < min) min = tmp;
				}

				C[i][j] += min;
			}

			dist = (C[1][1] + N / 2) / N;
	}

	if (C != NULL) Vfree(C);
	if (junk != NULL) Vfree(junk);
	if (BE != NULL) Vfree(BE);
	if (TE != NULL) Vfree(TE);
	return(dist);
}

/*
 *  First compute the similarity between the two strings.
 *  If it's above a threshold, compute the distance between
 *  the two and return it as the ``score.''
 *  Otherwise, return the constant WORST_SCORE.
 *
 */
static void score_stroke(point_list *input_dompts, 
										 point_list *curr_dompts, int *sim, int *dist) 
{
   *sim = MIN_SIM;
   *dist = MAX_DIST;

   *sim = compute_similarity(input_dompts, curr_dompts);
   if (*sim < SIM_THLD)	return;

   *dist = compute_distance(input_dompts, curr_dompts);

}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    recognize_stroke
//
// DESCRIPTION: This routine is main recognition routine.
//
// PARAMETERS:  (point_list *) stroke - stroke list of input point
//
// RETURNED:    Returns the resulting character.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static char *recognize_stroke(rClassifier *rec, point_list *stroke) 
{
   int i;
   char *name = NULL;
   point_list *input_dompts = NULL;
   char *best_name = NULL;
   int best_score = WORST_SCORE;
   char *curr_name;
   point_list *curr_dompts = NULL;

   if (stroke->npts < 1) goto done;

   /* Check for tap. */
   {
		// First thing is to filter out ``close points.'' 
		if (filter_points(stroke) != 0) return(NULL);

		// Unfortunately, we don't have the actual time that each point
		// was recorded (i.e., dt is invalid).  Hence, we have to use a 
		// heuristic based on total distance and the number of points. 
		if (stroke->npts == 1 || compute_pathlen(stroke) < TAP_PATHLEN)
			return(TAP_CHARS);
	}

	// Pre-process input stroke. 
	if (preprocess_stroke(stroke) != 0) goto done;

	// Compute its dominant points. 
	input_dompts = compute_dominant_points(stroke);
	if (input_dompts == NULL) goto done;

	// Score input stroke against every class in classifier. 
	for (i = 0, curr_name = rec->cnames[i], curr_dompts = rec->dompts[i];
			i < MAXSCLASSES && curr_name != NULL && curr_dompts != NULL;
			i++, curr_name = rec->cnames[i], curr_dompts = rec->dompts[i]) {
		int sim;
		int dist;
		int curr_score;

		score_stroke(input_dompts, curr_dompts, &sim, &dist);
		curr_score = dist;

		// Is it the best so far? 
		if (curr_score < best_score && curr_score <= DIST_THLD) {
			best_score = curr_score;
			best_name = curr_name;
		}
   }

   // No errors. 
   name = best_name;

done:
   delete_examples(input_dompts);

   return(name);
}

/*
 * intl_initialize-Initialize the internationaliztion of messages for
 * the recognition manager.
*/

static void intl_initialize()
{
	char* dirname;

	/*Get recognizer home directory name from environment.*/

	if( (dirname = Vgetenv(RECHOME)) == NULL ) {
		dirname = "REC_DEFAULT_HOME_DIR";
	}

	/*Bind the text domain.*/

	bindtextdomain(dirname,INTL_DOMAIN);
}

/*
 * recognizer_unload - Unload the recognizer.
*/


int
recognizer_unload(recognizer rec)
{
//   recognizer_internal_finalize rif;
    
   /*Make sure magic numbers right.*/
	if( !RI_CHECK_MAGIC(rec) ) {
		the_last_error = dgettext(INTL_DOMAIN,"Bad recognizer object.");
		return(-1);
   }
    
   __recognizer_internal_finalize(rec);

   return(0);
}

recognizer recognizer_load(char* directory,char* name,char** subset)
{
   recognizer rec;                     /*the recognizer*/
//   recognizer_internal_initialize rii; /*the initialization function*/
   rec_info* rinf;                     /*rec_info for recognizer information*/
   static Boolean intl_init = false;	/*true if recog. manager initted.*/

   if( intl_init == false ) {
      intl_init = true;

      intl_initialize();
   }

   /*The name takes precedence.*/
   rinf = make_rec_info(directory,name,subset);
   if (rinf == NULL) {
		the_last_error = dgettext(INTL_DOMAIN,
		   "Ran out of memory during prelinking initialization.");
		return((recognizer)NULL);
   } 

   /*Let recognition code create recognizer and initialize*/
   rec = __recognizer_internal_initialize(rinf);
   if (rec == NULL) {
		return((recognizer)NULL);
   }
   
	/*Check whether it's been correctly initialized*/
   if( rec->recognizer_load_state == NULL ||
        rec->recognizer_save_state == NULL ||
        rec->recognizer_load_dictionary == NULL ||
        rec->recognizer_save_dictionary == NULL ||
        rec->recognizer_free_dictionary == NULL ||
        rec->recognizer_add_to_dictionary == NULL ||
        rec->recognizer_delete_from_dictionary == NULL ||
        rec->recognizer_error == NULL ||
        rec->recognizer_set_context == NULL ||
        rec->recognizer_get_context == NULL ||
        rec->recognizer_clear == NULL ||
        rec->recognizer_get_buffer == NULL ||
        rec->recognizer_set_buffer == NULL ||
        rec->recognizer_translate == NULL ||
        rec->recognizer_get_extension_functions == NULL ||
        rec->recognizer_get_gesture_names == NULL ||
        rec->recognizer_set_gesture_action == NULL
       ) {

		recognizer_unload(rec);
		the_last_error = dgettext(INTL_DOMAIN,
		   "One or more recognizer function pointers is NULL.");
		return((recognizer)NULL);
   }

   /*Set the rec_info structure.*/
   rec->recognizer_info = rinf;

   return(rec);
}

RecInterface rec_alloc() 
{
    RecInterface rec;
    rec = (RecInterface) Vmalloc(sizeof(RecInterfacePrivate));
    return (rec);
}

void rec_free(RecInterface rec) {
    Vfree (rec);
}

/*
 * recognizer_error-Return the last error message, or NULL if none.
*/

char* recognizer_error(recognizer rec)
{
    
    /*Make sure magic numbers right and function there.*/

    if( !RI_CHECK_MAGIC(rec) && the_last_error == NULL ) {
      return(dgettext(INTL_DOMAIN,"Bad recognizer object."));

    } else if( the_last_error != NULL ) {
      char* error = the_last_error;

      the_last_error = NULL;
      return(error);
    }

    /*Do the function.*/

    return(rec->recognizer_error(rec));
}

/*
 * recognizer_load_state-Get any recognizer state associated with name
 * in dir. Note that name may not be simple file name, since
 * there may be more than one file involved. Return 0 if successful,
 * -1 if not.
*/

int recognizer_load_state(recognizer rec,char* dir,char* name)
{
    /*Make sure magic numbers right.*/

	if( !RI_CHECK_MAGIC(rec) ) {
		the_last_error = dgettext(INTL_DOMAIN,"Bad recognizer object.");
		return(-1);
	}

    /*Do the function.*/

    return(rec->recognizer_load_state(rec,dir,name));
}

/*
 * recognizer_get_extension_functions-Return a null terminated array
 * of functions providing extended functionality. Their interfaces
 * will change depending on the recognizer.
*/

rec_fn* recognizer_get_extension_functions(recognizer rec)
{
    /*Make sure magic numbers right.*/

    if( !RI_CHECK_MAGIC(rec) ) {
	the_last_error = dgettext(INTL_DOMAIN,"Bad recognizer object.");
	return((rec_fn*)NULL);
    }

    /*Do the function.*/

    return(rec->recognizer_get_extension_functions(rec));
}

/* This functions purpose is to take the location of a configuration
 * File, and with it load any configurations needed for character
 * recognition. 
 * file_name -- location of primary config file CURRENTLY NOT USED
 * returns 0 on success, non 0 on failure;
 */

int
rec_load_configuration(RecInterface rec, char *file_name,
        KeySym* kc2ks_table, KeyCode min_kc, KeyCode max_kc, int ks_per_kc) 
{
    Boolean usingDefault;
    char* homedir;
    int i;
    rec_fn *fns;

    if (!rec) 
        return -1;

    /* save state */
    rec->tmpShift = 0;
    rec->puncShift = 0;
    rec->ctrlShift = 0; 
    rec->curCharSet = 0;
    rec->capsLock = 0;
    /* save mapping table */
    rec->kc2ks_table = kc2ks_table;
    rec->kc2ks_start = min_kc;
    rec->kc2ks_end = max_kc;
    rec->kc2ks_width = ks_per_kc;
    
    for(i = 0; i < NUM_RECS; i++) {
		/* Load the recognizer itself... */
		rec->rec[i] = recognizer_load(DEFAULT_REC_DIR, rec_name, NULL);
		if (rec->rec[i] == NULL) {
//			fprintf(stderr,"Error loading recognizer from %s.", DEFAULT_REC_DIR);
			return -1;
		}
		if ((* (int *)(rec->rec[i])) != 0xfeed) {
//			fprintf(stderr,"Error in recognizer_magic. %s, %s", DEFAULT_REC_DIR, rec_name);
			return -1;
		}
	}

    /* ...then figure out where the classifiers are... */
    if ( (homedir = (char*)Vgetenv("HOME")) == NULL) {
        Vstrcpy(rec->cldir, REC_DEFAULT_USER_DIR);
        usingDefault = true;
    } else {
        Vstrcpy(rec->cldir, homedir);
        Vstrcat(rec->cldir, "/");
        Vstrcat(rec->cldir, CLASSIFIER_DIR);
        usingDefault = false;
    }


	/* ...then load the classifiers... */
    for (i = 0; i < NUM_RECS; i++) {
		int rec_return;

		rec_return = recognizer_load_state(rec->rec[i],
                //rec->cldir, cl_name[i]);
                "classifiers", cl_name[i]);
        if ((rec_return == -1) && (usingDefault == false)) {
            rec_return = recognizer_load_state(rec->rec[i],
                    REC_DEFAULT_USER_DIR, cl_name[i]);
        }
		if (rec_return == -1) {
			return -1;
		}
	}

	/* We have recognizers and classifiers now.   */
	/* Get the vector of LIextension functions..     */
	fns = recognizer_get_extension_functions(rec->rec[CS_LETTERS]);
	if (fns == NULL) {
//		fprintf(stderr, "LI Recognizer Training:No extension functions!");
		return -1;
	}
	
	/* ... and make sure the training & get-classes functions are okay. */
	if( (rec->rec_train = (li_recognizer_train)fns[LI_TRAIN]) == NULL ) {
//		fprintf(stderr, "LI Recognizer Training:li_recognizer_train() not found!");
		if (fns != NULL) {
			Vfree(fns);
		}
		return -1;
	}
  
	if( (rec->rec_getClasses = (li_recognizer_getClasses)fns[LI_GET_CLASSES]) == NULL ) {
//		fprintf(stderr, "LI Recognizer Training:li_recognizer_getClasses() not found!");
		if (fns != NULL) {
			Vfree(fns);
		}
		return -1;
	}
	Vfree(fns);
	return 0;
}

/* not static, used from xscribble.c */
void
Initialize_recorder (Widget gw)
{
    KeySym* table_pointer=NULL;
    int min_key_code=0;
    int max_key_code=255;
    int keysyms_per_keycode=0;

    if(!recIFace) {
        /* initialize recogniser */
        /* need to pass the keysym - keycode mapping as well
         * TABLE MUST NOT BE CHANGED */
        recIFace = rec_alloc();
        rec_load_configuration(recIFace, "recrc",
                table_pointer, (KeyCode)min_key_code, (KeyCode)max_key_code, keysyms_per_keycode);
    }
}

void Finalize_recorder ()
{
	int	i;

	if ( recIFace ) {
		for(i = 0; i < NUM_RECS; i++) {
			recognizer_unload (recIFace->rec[i]);
		}

		Vfree (recIFace);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    hwAddPoint
//
// DESCRIPTION: This routine add one point into point list.
//
// PARAMETERS:  (int) x - x coordinate of input point.
//					 (int) y - x coordinate of input point.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void hwAddPoint (int x, int y)
{
	if ( (lpts == NULL) || ((x != currentPnt->x) && (y != currentPnt->y)) ) {
		if ( lpts == NULL ) {
			lpts = (point_list *) Vmalloc (sizeof(point_list));
			lpts->npts = 1;
			lpts->pts = (pen_point *) Vmalloc (sizeof(pen_point));
		} else {
			lpts->npts++;
			lpts->pts = (pen_point *) Vrealloc (lpts->pts, lpts->npts*sizeof(pen_point));
		}

		lpts->pts[lpts->npts-1].x = x;
		lpts->pts[lpts->npts-1].y = y;
		currentPnt = &(lpts->pts[lpts->npts-1]);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    hwRecognizeStart
//
// DESCRIPTION: This routine start to recognize the input data
//
// PARAMETERS:  (UInt8) grfInputState - The status of current graffiti input.
//
// RETURNED:    Returns the resulting character.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Char hwRecognizeStart (UInt8 grfInputState)
{
	Char	*res=NULL, ch;

	if ( lpts != NULL ) {
		recognizer		rec;
		li_recognizer	*lrec;
		rClassifier		*rClass;

		rec = recIFace->rec[grfInputState];
		lrec = (li_recognizer *)rec->recognizer_specific;
		rClass = &(lrec->li_rc);
		res = recognize_stroke (rClass, lpts);

		Vfree (lpts->pts);
		Vfree (lpts);
		lpts = NULL;
		
		ch = res[0];
		if ( ch ) {
			if ( grfInputState!=grfPUNC ) {
				// not punctuation mode, return special character mode
				switch (ch) {
					case 'B' :	// from right to left
						ch = ASCII_BS;
						break;
					case 'A':	// from left to right
						ch = ' ';
						break;
					case 'S':	// from bottom to top
						ch = ASCII_TEMPCAPS;
						break;
					case 'R':	// from fight-top to left-bottom
						ch = ASCII_LF;
						break;
					case 'N':	// pen from left-bottom to right-top
						ch = ASCII_LINK;
						break;
					case 'P':
						ch = 'c';
						break;
					case 'W':
						ch = 'w';
						break;
				}
			} else {
				// punctuation mode, return punctuation
				switch (ch) {
					case 'B' :	// from right to left
						ch = ASCII_BS;
						break;
					case 'a':	// from left to right
						ch = '^';
						break;
					case 'S':	// from bottom to top
						ch = ASCII_TEMPCAPS;
						break;
					case 'R':	// from fight-top to left-bottom
						ch = ',';
						break;
					case 'N':	// pen from left-bottom to right-top
						ch = ASCII_LINK;
						break;
					case 'P':
						ch = 'c';
						break;
					case 'W':
						ch = 'w';
						break;
				}
			}

			return	ch;
		} else {
			return	0;
		}
	} else {
		return	0;
	}
}