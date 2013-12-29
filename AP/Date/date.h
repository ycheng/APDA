#ifndef    DATE_H
#define    DATE_H



//------------------- Constants-------------------------------------//
#define      DateDbName        "DATEDB"  
#define      CreatorID         'CATS'
#define      DbType            'DATA'
//--------------------function prototype declaration-----------------//
static   int      GetDatabase(DWord  creatorid ,Word  mode);
static   void     DateViewInit(FormPtr  form);
static   void     DrawMonth (int year, int month);

static   void     VCPCtlSetLabel(Word id, char *s);
static   void     MonthDrawTodayInversionCell (SWord year, SWord month, SWord day);
static   int      GetYear(FormPtr form,FieldPtr field);

#endif