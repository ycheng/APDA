/*========================================================
  HWUtility.c
  all routine is running with Platform non-related,
  all utility is for hand writing recognition.


  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0518, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>
#include <HWUtility.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

#define	allocate(n, type)		((type *) myalloc(n, sizeof(type), "type"))

#define REC_DEFAULT_LOCALE  	"C"
#define LANG			"LANG"

extern char* REC_VERSION;

void delete_examples(point_list* l)
{
   point_list* p;

   for( ; l != NULL; l = p ) {
		p = l->next;
		Vfree(l->pts);
		Vfree(l);
   }
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    delete_pen_point_array
//
// DESCRIPTION: This routine delete the pen_point array and free the
//					 allocated memory.
//
// PARAMETERS:  (pen_point *) pp - Pointer to pen_point structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void delete_pen_point_array(pen_point* pp)
{
	if( pp != NULL ) {
		Vfree(pp);
   }
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    delete_rec_info
//
// DESCRIPTION: This routine free the allocated memory for rec_info 
//					 struture.
//
// PARAMETERS:  (rec_info *) ri - Pointer to rec_info structure
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/21/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void delete_rec_info(rec_info* ri)
{
	if( ri != NULL ) {
		if( ri->ri_locale != NULL ) {
			Vfree(ri->ri_locale);
		}
		if( ri->ri_subset != NULL ) {
			int i;
			for( i = 0; ri->ri_subset[i] != NULL; i++) {
				Vfree(ri->ri_subset[i]);
			}
			Vfree(ri->ri_subset);
		}
	
		Vfree(ri);
	}
}

void delete_recognizer(recognizer rec)
{

    if( rec != NULL ) {
	if( rec->recognizer_info != NULL ) {
	    delete_rec_info(rec->recognizer_info);
	}
	Vfree(rec);
    }
}

/* Result is x 100. */
/* Code from Joseph Hall (jnhall@sat.mot.com). */
////////////////////////////////////////////////////////////////////////
// FUNCTION:    isqrt_long
//
// DESCRIPTION: This routine calculate the square value of input integer
//
// PARAMETERS:  (int) n - calculate the long square value of input 
//									integer
//
// RETURNED:    Returns the long square value of input integer.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
int isqrt_long(int n) 
{
   register int i;
   register unsigned long k0, k1, nn;

   for (nn = i = n, k0 = 2; i > 0; i >>= 2, k0 <<= 1)	;
   nn <<= 2;
   for (;;) {
		k1 = (nn / k0 + k0) >> 1;
		/*      printf("%8x %8x\n", k0, k1);*/
		if (((k0 ^ k1) & ~1) == 0)
			break;
		k0 = k1;
	}
   return (int) ((k1 + 1) >> 1);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    isqrt
//
// DESCRIPTION: This routine calculate the square value of input integer
//
// PARAMETERS:  (int) n - calculate the square value of input integer
//
// RETURNED:    Returns the square value of input integer.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
int isqrt(int n) 
{
   register int i;
   register unsigned long k0, k1, nn;

   if (n > 107374*10000) return(isqrt_long(n));

   for (nn = i = n, k0 = 2; i > 0; i >>= 2, k0 <<= 1)	;
   nn <<= 2;
   for (;;) {
		k1 = (nn / k0 + k0) >> 1;
		if (((k0 ^ k1) & ~1) == 0)
			break;
		k0 = k1;
	}
   return (int) ((k1 + 1) >> 1);
}

/* Helper routines from Mark Hayter. */
////////////////////////////////////////////////////////////////////////
// FUNCTION:    likeatan
//
// DESCRIPTION: This routine calculate the atan of input value
//
// PARAMETERS:  (int) tantop - top of tan value.
//					 (int) tanbot - bottom of tan value.
//
// RETURNED:    Returns the atan value.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
int likeatan(int tantop, int tanbot) 
{ 
   int t;
   /* Use tan(theta)=top/bot --> order for t */
   /* t in range 0..0x40000 */

   if ((tantop == 0) && (tanbot == 0)) 
		t = 0;
   else {
		t = (tantop << 16) / (Vabs(tantop) + Vabs(tanbot));
		if (tanbot < 0) 
			t = 0x20000 - t;
		else 
			if (tantop < 0) t = 0x40000 + t;
	}
   return t;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    make_pen_point_array
//
// DESCRIPTION: This routine allocate memory for pen_point array with
//					 specifies size.
//
// PARAMETERS:  (UInt) size - Size of pen_point array to allocate.
//
// RETURNED:    Returns the pointer of allocated pen_point array.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
pen_point* make_pen_point_array(UInt size)
{
	pen_point* pp = (pen_point*)Vmalloc(size * sizeof(pen_point));
   int i;

   for( i = 0; i < size; i++ ) {
		pp[i].time = 0;
		pp[i].x = pp[i].y = 0;
   }

   return(pp);
}

/*make_rec_info-Create a rec_info structure*/

////////////////////////////////////////////////////////////////////////
// FUNCTION:    make_rec_info
//
// DESCRIPTION: This routine allocate the memory with for rec_info 
//					 struture.
//
// PARAMETERS:  (char *) directory - Directory name.
//					 (char *) name - File name.
//					 (char **) subset - 
//
// RETURNED:    Returns the pointer of allocated memory.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/21/01	Initial Revision
////////////////////////////////////////////////////////////////////////
rec_info* make_rec_info(char* directory,char* name,char** subset)
{
	int i,len;
   rec_info* ri;
   char* locale;

//   ri = (rec_info*)safe_malloc(sizeof(rec_info));
   ri = (rec_info*)Vmalloc(sizeof(rec_info));
   ri->ri_locale = NULL;
   ri->ri_name = NULL;
   ri->ri_subset = NULL;

   /*Get locale*/

   if( (locale = Vgetenv(LANG)) == NULL ) {
		locale = Vstrdup(REC_DEFAULT_LOCALE);
   }

   if( (ri->ri_locale = Vstrdup(locale)) == NULL ) {
		delete_rec_info(ri);
		return(NULL);
   }

   /*Initialize the subset information.*/
   if( subset != NULL ) {
	
		/*Count the subset strings.*/
		for( len = 1; subset[len] != NULL; len++ ) ;
			/*Copy the subset strings.*/
//			ri->ri_subset = (char**)safe_malloc((len +1)*sizeof(char*));
			ri->ri_subset = (char**)Vmalloc((len +1)*sizeof(char*));
		
		for( i = 0; i < len; i++ ) {
			if( subset[i] != NULL ) {
				if( (ri->ri_subset[i] = Vstrdup(subset[i])) == NULL ) {
					delete_rec_info(ri);
					return(NULL);
				}
			} else {
				ri->ri_subset[i] = subset[i];
			}
		}

		ri->ri_subset[i] = NULL;
   } else {
		ri->ri_subset = NULL;
   }

	Vfree (locale);
   return(ri);
}

/*
 * Constructor functions for making structures.
 *
 *    The general philosophy here is that we control all memory
 *    in connected data structures, *except* for pen_point arrays.
 *    There are likely to be lots and lots of points, they are likely
 *    to come from the window system; so if we wanted to control them,
 *    we would have to copy which would be slow. We require the client
 *    to deal with them directly, or the client can give us permission
 *    to delete them.
*/

/*
 * recognizer
*/

recognizer make_recognizer(rec_info* rif)
{
    recognizer rec;
    
    /*Allocate it.*/

//    rec = (recognizer)safe_malloc(sizeof(*rec));
    rec = (recognizer)Vmalloc(sizeof(*rec));
    rec->recognizer_magic = REC_MAGIC;
    rec->recognizer_version = REC_VERSION;
    rec->recognizer_info = rif;
    rec->recognizer_specific = NULL;
    rec->recognizer_end_magic = REC_END_MAGIC;
    rec->recognizer_load_state = NULL;
    rec->recognizer_save_state = NULL;
    rec->recognizer_load_dictionary = NULL;
    rec->recognizer_save_dictionary = NULL;
    rec->recognizer_free_dictionary = NULL;
    rec->recognizer_add_to_dictionary = NULL;
    rec->recognizer_delete_from_dictionary = NULL;
    rec->recognizer_error = NULL;
    rec->recognizer_set_context = NULL;
    rec->recognizer_get_context = NULL;
    rec->recognizer_clear = NULL;
    rec->recognizer_get_buffer = NULL;
    rec->recognizer_set_buffer = NULL;
    rec->recognizer_translate = NULL;
    rec->recognizer_get_extension_functions = NULL;
    rec->recognizer_get_gesture_names = NULL;
    rec->recognizer_set_gesture_action = NULL;
    return(rec);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    myalloc
//
// DESCRIPTION: This routine allocate the memory with specifiies size.
//
// PARAMETERS:  (int) nitmes - Number of items.
//					 (int) itemsize - size of each item.
//					 (char *) typename - type name of items.
//
// RETURNED:    Returns the pointer of allocated memory.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
char *myalloc(nitems, itemsize, typename)
char *typename;
{
	register unsigned int bytes = nitems * itemsize;
	register char *p = Vmalloc(bytes);
	return p;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    quadr
//
// DESCRIPTION: This routine return the quardrature of input value
//
// PARAMETERS:  (int) t - input value to calculate
//
// RETURNED:    Returns the quardrature of input value
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
int quadr(int t) 
{
   return (8 - (((t + 0x4000) >> 15) & 7)) & 7;
}
