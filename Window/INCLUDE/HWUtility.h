#ifndef __HWUTILITY_H__
#define __HWUTILITY_H__


#define	allocate(n, type)		((type *) myalloc(n, sizeof(type), "type"))

/*
 * These magic numbers are used to ensure the integrity of the
 * recognizer structure.
*/
#define REC_MAGIC       0xfeed
#define REC_END_MAGIC   0xbeef

extern void delete_examples(point_list* l);
extern void delete_pen_point_array(pen_point* pp);
extern void delete_recognizer(recognizer rec);
extern int isqrt_long(int n);
extern int isqrt(int n);
extern int likeatan(int tantop, int tanbot);
extern pen_point* make_pen_point_array(UInt size);
extern rec_info* make_rec_info(char* directory,char* name,char** subset);
extern recognizer make_recognizer(rec_info* rif);
extern char *myalloc(nitems, itemsize, typename);
extern int quadr(int t) ;


#endif // __HWUTILITY_H__
