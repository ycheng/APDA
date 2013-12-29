#define       upArrowOn           "\001"
#define       downArrowOn         "\002"
#define       upArrowOff          "\003"
#define       downArrowOff        "\004" 

//--------------------------------------------------------------------------------------
#define        NumOfItems          16
#define        ItemLength          16 
#define        FieldLength         255

#define        categoryDefaultEditCategoryString        10001
//----------------Address Record  structure---------------------------------------------
typedef  struct{ 
                 char      Custom1[ItemLength];
                 char      Custom2[ItemLength];
                 char      Custom3[ItemLength];
                 char       Custom4[ItemLength];
                
} CustomFieldType;                        

typedef    CustomFieldType  CustomFieldPtr;

typedef   enum {
	        firstName,
	        lastName,
	        title,
	        company,
	        work,
	        home,
	        email,
	        address,
	        city,
	        zip,
}FieldConvertType; 	        
	  
//----------------Database  related  function--------------------------------------------

extern    Err  OpenAddressDatabase(void);  
extern    Err  OpenNoteDatabase(void);
extern    Err  AddressAppInfoInit(void);
extern    Err  NoteDatabaseAppInfoInit(void);

//----------------Record   related   function--------------------------------------------
static    Boolean   CreateAddressRecord (void);
static    void      CreateNoteRecord(void);
static    void      DuplicateAddressRecord(FormPtr  form);
static    void      SetRecordCategory(Word* category); 
static    Word      GetRecordCategory(Word  *index); 
static    Boolean   SaveAddressRecord(FormPtr form);

//--------------- EditForm  related  fuction---------------------------------------------
  
extern    Err  EditFormInit(FormPtr  form);

extern   void  SetFieldAttribute(FieldPtr field);
static   void  EditFormGetAddressRecord(FormPtr  form);
static   void  EditFormCategorySelect(FormPtr  form);
static   void  EditFormChangeFieldHeight(EventPtr event,FormPtr form);
static   void  EditFormResetObjectPosition(FormPtr  form);
static   void  EditFormPageModify(Word  id);
static   void  EditFormDrawLabel(void); 
static   void  EditFormUpdate(FormPtr  form);
//--------------- MainForm  related  function -------------------------------------------

static  void     MainFormCategorySelect(FormPtr  form); 

//----------------NoteForm  related  function --------------------------------------------

static  Boolean  NoteFormSaveAddressNote(FormPtr  form ,FieldPtr  field);
static  void     NoteFormInit(FormPtr form,FieldPtr field) ;
static  void 	 NoteFormUpdateScrollBar(FormPtr form,FieldPtr  field);
static  void     NoteFormScrollLine(FormPtr form,FieldPtr field,SWord newValue ,SWord value);
static  Boolean  NoteFormDeleteNote(FormPtr  form);

//----------------FontDialogForm   related routine ------------------------------------------
  
static    void    FontDialogFormInit(FormPtr  form);
static    void    SetCurrentFont(FormPtr  form);
static    void    UpdateTextFont(void);

//----------------CustomFieldForm related routine ------------------------------------------

static  void     CustomFieldFormInit(FormPtr  form);
static  void     StoreCustomField(FormPtr  form);
static  void     UpdateCustomField(FormPtr  form);

//----------------SecretAddressForm related routine ------------------------------------------

static    void   SecretAddressFormInit(FormPtr form,ControlPtr  checkBox);
static    void   SecretAddressFormSetRecordSecret(FormPtr form,ControlPtr  checkBox);

//----------------Other      Routines ------------------------------------------------------------------------
static   Boolean   MenuDoCommand(Word command);
static   Boolean   MenuBarDeleteRecord(FormPtr  form);
//------------------------------Database  Constants-----------------------------------

#define  addressDbName        "ADDRESS"           
#define  noteDbName           "ADDRESSNOTE"
#define  creatorID           'CHEN'           /* Define the information of the database */
#define  noteCreatorID       'NOTE' 
#define  dBType        'DATA'


#define  alert_OK_Button         0
#define  alert_Cancel_Button     1



//---------------------------------
void    AddressNumsDisplay();
void    RptBtnInit(FormPtr  form);
void    MainFormListAddress(FormPtr  form);
static  Boolean AddressViewHandlePen (EventType * event);

RectangleType  AddressInvert(SWord  y);


#define      Max(x,y)    ((x) > (y)) ? x : y
#define      Min(x,y)    ((x) < (y)) ? x : y 


typedef  struct {
        
         Char	categoryLabels [dmRecNumCategories] [dmCategoryLength];
	      

}MyAppInfoType;	     