/**********************************************************
 * Company     : Wiscore Inc                              * 
 *                                                        *  
 * Filename    : memo.h                                  *
 *                                                        * 
 * Description : a memo-test  header file		  *	
 *							  *	
 * History     : 2001/08/23  by Vincent Chen	          *	
 *********************************************************/ 
 
 




//  Database related Functions

static  Err  OpenDatabase(void);
static  Err  SetDatabaseInfo(Word flag);
static  Err  DbAppInfoInit(void); 
//static void  LocalizeAppInfo(AppInfoPtr appInfoP);

//  Record  related  Functions

static Boolean    CreateRecord (void);
static Boolean    DeleteRecord(Word index);
static void       EditFormSaveRecord(FormPtr form);
static void       EditFormGetRecord(FormPtr form,FieldPtr field,FieldPtr  titleField); 
static  void      SetRecordCategory(Word* category) ; 
static  Word      GetRecordCategory(Word  *index);
static  void      EditFormCategorySelect(void);
static  void      SetRecordSecret(FormPtr form);
static  void      SetRecordUnsecret(FormPtr form);

static  void      MainFormLoadRecord(FormPtr form,ListPtr list);
static  void      MainFormCategoryListInit(ControlPtr  trigger);
static  void      EditFormCategoryListInit(ControlPtr  trigger);
static  void     MainFormCategorySelect(FormPtr  form);     
static  Boolean  MenuDoCommand( Word   command);

static  void 	EditFormUpdateScrollBar(FormPtr form,FieldPtr field);
static  void    ScrollLine(FormPtr form,FieldPtr field ,SWord newValue ,SWord value);
static  void    EditFormCheckBoxInit(FormPtr form);
static  void    SetFont(FontID  currentFont);


static    void    FontDialogFormInit(FormPtr  form);
static    void    FontSetCurrentFont(FormPtr  form);
static    void    FontUpdateTextFont();	
//--------------------------------------------------------------------------------
//Constant Definition

#define  dBName        "MEMO"           
#define  creatorID     'CATS'           /* Define the information of the database */
#define  dBType        'DATA'



#define  alert_OK_Button         0
#define  alert_Cancel_Button     1


#define  LocalizedAppInfoStr      1000
//--------------------------------------------------------------------------------

void    MemoNumsDisplay  (void);
void    RptBtnInit(FormPtr  form);
void    MainFormListMemo(FormPtr  form);
static  Boolean MemoViewHandlePen (EventType * event);
 RectangleType  MemoInvert(SWord  y);



#define      Max(x,y)    ((x) > (y)) ? x : y
#define      Min(x,y)    ((x) < (y)) ? x : y 
