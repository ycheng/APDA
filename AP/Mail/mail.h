

			//Constant Definition

#define  dBName        "PMail"           
#define  creatorID     'CATS'           /* Define the information of the database */
#define  dBType        'DATA'

//----------------------------------------------------------------------------------------------



		      //  Database related Functions

static  Err      OpenDatabase(void);
static  Err      SetDatabaseInfo(Word flag);

static  void      MainFormListMail(FormPtr  form) ;      
static  void      ViewFormInit(FormPtr  form,Word mailIndex);

static  Boolean     DeleteMail(FormPtr form,Word index);
static  void*       ViewFormGetRecord(FormPtr form,Word mailIndex); 
static  void        MainFormLoadRecord(FormPtr form,ListPtr list);
static  Boolean     MailViewHandlePen (EventType * event);
static  void        MailIndexDisplay(Word   index);
static  void	    RptBtnInit(FormPtr  form);
static  void        MailNumsDisplay();
static  RectangleType    MailInvert(SWord y);

		     //  others...
		     	
static  void 	    ViewFormUpdateScrollBar(FormPtr form,FieldPtr field);
static  void        ScrollLine(FormPtr form,FieldPtr field ,SWord newValue ,SWord value);

static  Boolean     MenuDoCommand(Word command)	;


//--------------------------------------------------------------------------------

#define  alert_OK_Button         0
#define  alert_Cancel_Button     1


#define      Max(x,y)    ((x) > (y)) ? x : y
#define      Min(x,y)    ((x) < (y)) ? x : y 
