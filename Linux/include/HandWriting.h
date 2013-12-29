#ifndef __HANDWRITING_H__
#define __HANDWRITING_H__


// for graffiti status
#define	grfLETTERS	0
#define	grfDIGITS	1
#define	grfPUNC		2
#define	grfNONE		9

/* Overload the time field of the pen_point struct with the chain-code. */
#define	MAXSCLASSES	100
#define	chaincode   time
#define	RECHOME			"RECHOME"
#define	INTL_DOMAIN "recognition_manager"
#define DEFAULT_REC_DIR         "classsifiers"
#define rec_name                "libli_recog.so"
#define DEFAULT_LETTERS_FILE    "letters.cl"
#define DEFAULT_DIGITS_FILE     "digits.cl"
#define DEFAULT_PUNC_FILE       "punc.cl"

#define GESTURE		"GESTURE"	/* gestures only */
#define UPPERCASE	"UPPERCASE"	/* upper case alphabetics, no digits */
#define LOWERCASE	"LOWERCASE"	/* lower case alphabetics, no digits */
#define DIGITS		"DIGITS"	/* digits 0-9 only */

/* Note: this structure is prepended at the beginning of a Vector, and causes
   the Vector data type to be 32-byte aligned, but not 64-byte aligned.
   If this were a problem, filler could be filler[5] (or more) instead. 
   --Sharon Perl, 12/17/98. */

struct array_header {
	unsigned char	ndims;	/* 1 = vector, 2 = matrix */
	unsigned char	nrows;
	unsigned char	ncols;
	unsigned char	filler;
};

typedef double **Matrix;
typedef double *Vector;
typedef struct sclassifier *sClassifier; /* single feature-vector classifier */
typedef int		sClassIndex; /* single feature-vector class index */
typedef struct sclassdope  *sClassDope;	 /* single feature-vector class dope */
//typedef void	*recognizer;

typedef unsigned int WChar_t;
typedef UInt16	KeySym;
typedef UInt16	KeyCode;

static char* cl_name[] = 
{
    DEFAULT_LETTERS_FILE,
    DEFAULT_DIGITS_FILE,
    DEFAULT_PUNC_FILE
};

typedef struct {
    UInt32	time;
    short	x, y;
} pen_point;

typedef struct PointList {
    int			npts;
    int			xrange, yrange;
    pen_point* pts;
    struct PointList* next;
} point_list;

typedef struct RegionList {
    int start;
    int end;
    int type;
    struct RegionList *next;
} region_list;

typedef Byte rec_confidence;

typedef struct {
	char tc_id[20];			   /*tablet identifier, null terminated*/
	UInt16 tc_button;      	   /*button capabilities*/
	UInt16 tc_pen;		       	   /*pen capabilities*/
	UInt16 tc_angle;         	   /*pen angle reporting*/
	UInt32 tc_sensor : 8;		   /*sensor capabilities*/
	UInt32 tc_units : 8;	   	   /*units for xy reporting*/
	UInt32 tc_default_units : 8; 	   /*default units*/
	UInt32 tc_origin : 8;	   	   /*where origin located*/
	Int16 tc_x[2];			   /*minimum/maximum x*/
	Int16 tc_y[2];			   /*minimum/maximum y*/
	Int16 tc_pressure[2];		   /*minimum/maximum pressure/height*/
	UInt32 tc_sample_rate;		   /*rate of event reporting*/
	UInt32 tc_sample_distance;	   /*xy coords per sample*/

} tablet_cap;

typedef struct {
    Int16 x,y;                    /*Upper left corner.*/
    Int16 width,height;           /*Width and height.*/
} pen_rect;    

typedef struct {
	pen_rect pr_area;
	Int16 pr_row, pr_col;
	double pr_rowpitch, pr_colpitch;
} pen_frame; 


/*
 * Pen state parameters. "Basic" state is pen up/down, barrel buttons 
 * (if any), and in/out of range. Others may be reported by particular pens.
*/

typedef struct {
    UInt16 pt_button;      /*button state - same as tc_button*/
    UInt16 pt_pen;         /*other state - same as tc_pen*/
    Int16 pt_pressure;      /*Pressure. + against tablet, - above tablet.*/
    double pt_anglex;       /*angle of tilt in the x direction, in radians.*/
    double pt_angley;       /*angle of tilt in the y direction, in radians.*/
    double pt_barrelrotate; /*angle of barrel rotation, in radians.*/
} pen_state;

/*
 * Stroke structure. 
*/

typedef struct {
    UInt32 ps_npts;                        /*Number of pen_point in array.*/
    pen_point* ps_pts;                    /*Array of points.*/
    UInt32 ps_nstate;			  /*Number of pen_state in array.*/
    UInt32* ps_trans;			  /*State transition point indicies.*/
    pen_state* ps_state;                  /*Array of state.*/
} pen_stroke;

/*
 * Recognizer information. Gives the locale, category of the character
 * set returned by the recognizer, and any subsets to which the
 * recognition can be limited. The locale and category should be
 * suitable for the setlocale(3). Those recognizers which don't do text
 * can simply report a blank locale and category, and report the
 * graphics types they recognize in the subset. 
*/

typedef struct {
    char* ri_locale;        /*The locale of the character set.*/
    char* ri_name;          /*Complete pathname to the recognizer.*/
    char** ri_subset;       /*Null terminated list of subsets supported*/
} rec_info;

typedef struct _letterset {
        char ls_type;
        union _ls_set {
                char* aval;
                WChar_t* wval;
        } ls_set;
} letterset;

#define wordset void*

typedef struct {
    UInt16 rc_upref;           /*User preference. */
    Boolean rc_gesture;            /*Look for gesture if true.*/
    UInt16 rc_direction;       /*Primary and secondary writing direction.*/
    rec_confidence rc_cutoff;	/*Cut off recognition below this confidence*/
    tablet_cap* rc_tinfo;       /*Tablet capabilities.*/
    char** rc_subset;           /*Confine recognition to these subsets.*/
    pen_frame* rc_frame;        /*If nonNULL, writing area geometry.*/
    wordset rc_wordset;         /*If nonNULL, dictionary.*/
    letterset rc_letterset;     /*If nonNULL, constrain to these chars.*/
    void* rc_context;           /*For recognizer-specific context.*/
} rc;

/*
 * Gestures. The toolkit initializes the recognizer with a
 * set of gestures having appropriate callbacks. 
 * When a gesture is recognized, it is returned as part of a
 * recognition element. The recognizer fills in the bounding
 * box and hotspots. The toolkit fills in any additional values,
 * such as the current window, and calls the callback.
*/

typedef struct Gesture {
    char* g_name;                      /*The gesture's name.*/
    UInt32 g_nhs;                       /*Number of hotspots.*/
    pen_point* g_hspots;               /*The hotspots.*/
    pen_rect g_bbox;                   /*The bounding box.*/
    void (*g_action)(struct Gesture*);       /*Pointer to execution function.*/
   void* g_wsinfo;	    	     /*For toolkit to fill in.*/
} gesture;

typedef void (*xgesture)(gesture*);

#define rec_correlation void

typedef struct {
    char re_type;                  /*Union type flag.*/
    union {
	gesture* gval;             /*Gesture.*/
	char* aval;                /*ASCII and variable width.*/
	WChar_t* wval;             /*Unicode.*/
	rec_correlation* rcval;    /*rec_correlation*/
    } re_result;                   
    rec_confidence re_conf;        /*Confidence (0-100).*/
} rec_element;

/*
 * Recognition alternative. The recognition alternative gives
 * a translated element for a particular segmentation, and
 * a pointer to an array of alternatives for the next position
 * in the segmentation thread.
*/

struct _Rec_alternative {
	rec_element ra_elem; 		/*the translated element*/
	UInt32 ra_nalter;		/*number of next alternatives*/
	struct _Rec_alternative* ra_next; /*the array of next alternatives*/
};

typedef struct _Rec_alternative rec_alternative;

/*For pointers to extra functions on recognizer.*/
typedef void (*rec_fn)();

/*
 * Internal view of the recognizer struct. This view is only available
 * to OEM clients who implement a recognizer shared library. Clients
 * of the recognizer itself see it as an opaque data type. The struct
 * contains a function pointer for each function in the client API.
*/

struct _Recognizer {
	UInt32 recognizer_magic;
/* ari */
/* 	const char* recognizer_version;  */
        char* recognizer_version; 

	rec_info* recognizer_info;
	void* recognizer_specific;
	Int32
		(*recognizer_load_state)(
			struct _Recognizer*,
			char*, char*);
/*			char* dir,
			char* name);
*/
	Int32
		(*recognizer_save_state)(
			struct _Recognizer*,
			char*, char*);
/*			char* dir,
			char* name); 
*/
	char*
		(*recognizer_error)(
			struct _Recognizer*);
	wordset
		(*recognizer_load_dictionary)(
/*			struct _Recognizer* rec,
			char* directory,
			char* name);
*/
			struct _Recognizer*,
                        char*, char*);
	Int32
		(*recognizer_save_dictionary)(
/*			struct _Recognizer* rec,
			char* directory,
			char* name,
			wordset dict);
*/
			struct _Recognizer*,
                        char*, char*, wordset);

	Int32
	  	(*recognizer_free_dictionary)(
/*			struct _Recognizer* rec,
			wordset dict);
*/
			struct _Recognizer*,
                        wordset);
	Int32
	  	(*recognizer_add_to_dictionary)(
/*			struct _Recognizer* rec,
			letterset* word,
			wordset dict);
*/
			struct _Recognizer*,
                        letterset*, wordset);
	Int32
	  	(*recognizer_delete_from_dictionary)(
/*			struct _Recognizer* rec,
			letterset* word,
			wordset dict);
*/
			struct _Recognizer*,
                        letterset*, wordset);
	Int32
	 (*recognizer_set_context)(
/*		struct _Recognizer* rec,
		rc* rec_xt);
*/
			struct _Recognizer*,rc*);
	rc*
	 (*recognizer_get_context)(
/*		struct _Recognizer* rec);
*/
			struct _Recognizer*);
				   
	Int32
	 (*recognizer_clear)(
/*		struct _Recognizer* rec,
		bool delete_ponts_p);
*/
			struct _Recognizer*, Boolean);
	Int32
	 (*recognizer_get_buffer)(
/*		struct _Recognizer* rec,
		u_int* nstrokes,
		pen_stroke** strokes);
*/
			struct _Recognizer*, UInt32*, pen_stroke**);

	Int32
	 (*recognizer_set_buffer)(
/*		struct _Recognizer* rec,
		u_int nstrokes,
		pen_stroke* strokes);
*/
			struct _Recognizer*, UInt32, pen_stroke*);
	Int32
	 (*recognizer_translate)(
/*		struct _Recognizer* rec,
		u_int nstrokes,
		pen_stroke* strokes,
		bool correlate_p,
		int* nret,
		rec_alternative** ret);
*/
			struct _Recognizer*, UInt32, pen_stroke*,
			Boolean, Int32*, rec_alternative**);
	rec_fn*
	 (*recognizer_get_extension_functions)(
		struct _Recognizer*);
	char**
		(*recognizer_get_gesture_names)(
			struct _Recognizer*);
	xgesture
		(*recognizer_set_gesture_action)(
			struct _Recognizer*,
/*			char* name,
			xgesture fn,
			void* wsinfo);
*/
                        char*, xgesture, void*);
	UInt32 recognizer_end_magic; 
};

typedef struct _Recognizer* recognizer;

#undef wordset
typedef struct _wordset {
	char* ws_pathname;		/*Path name to word set file.*/
	recognizer ws_recognizer;	/*To whom it belongs.*/
	void* ws_internal;		/*Internal data structures.*/
} *wordset;

typedef int (*li_recognizer_train)(recognizer r,
				    rc* rec_xt,
				    UInt32 nstrokes,
				    pen_stroke* strokes,
				    rec_element* re,
				    Boolean replace_p);
typedef int (*li_recognizer_getClasses)(recognizer r, char ***list, int *nc);
typedef recognizer (*recognizer_internal_initialize)(rec_info* ri);
typedef int (*recognizer_internal_finalize)(recognizer r);

struct sclassdope {
	char 		*name;
	sClassIndex	number;
	Vector		average;
	Matrix		sumcov;
	int		nexamples;
};

struct sclassifier {
	int		nfeatures;
	int		nclasses;
	sClassDope	*classdope;

	Vector		cnst;	/* constant term of discrimination function */
	Vector		*w;	/* array of coefficient weights */
	Matrix		invavgcov; /* inverse covariance matrix */
};

typedef struct {
    char* file_name;              /*The classifier file name.*/
    sClassifier sc;               /*The classifier.*/
    point_list* ex[MAXSCLASSES];   /*The training examples.*/
    char* cnames[MAXSCLASSES];    /*The class names.*/
    point_list*	canonex[MAXSCLASSES];	/* Canonicalized versions of the strokes. */
    point_list*	dompts[MAXSCLASSES];	/* Dominant points */
} rClassifier;

/*This structure contains extra fields for instance-specific data.*/

typedef struct {
    /*Instance-specific data.*/
    UInt32 li_magic;            /*Just to make sure nobody's cheating.*/
    rClassifier li_rc;         /*The character classifier.*/
} li_recognizer;

typedef struct _RecInterfacePrivate {
    /* config file location */
    char cldir[200];
    /* recognizer structs */
    recognizer rec[3];
    li_recognizer_train rec_train;
    li_recognizer_getClasses rec_getClasses;
    /* state variables */
    int curCharSet;
    int tmpShift;
    int puncShift;
    int ctrlShift;
    int capsLock;
    /* Keysym to Keycode and modifier mapping table */
    KeySym* kc2ks_table;
    KeyCode kc2ks_start;
    KeyCode kc2ks_end;
    int kc2ks_width;

} RecInterfacePrivate;

typedef RecInterfacePrivate *RecInterface;



#endif // __HANDWRITING_H__
