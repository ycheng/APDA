 /**********************************************************
 * Company     : Wiscore Inc                              * 
 *                                                        *  
 * Filename    : memo.c                                  *
 *                                                        * 
 * Description : a memo test AP for palm		  *	
 *		 					  *	
 * History     : 2001/08/23  by Vincent Chen	          *	
 *********************************************************/ 

#include <Pilot.h>
#include <System/SysAll.h>
#include <UI/UIAll.h>
#include "memo.h"
#include "memoRsc.h"

/*************Constants***********************************/
#define      newRecordSize                  16                    // initial record size
#define      MaxTitleSize                   26 
#define      startPosition                   0
#define     categoryDefaultEditCategoryString   10001


//----------------------------------------------------
#define      Memo_Index_Start		    0

#define      RecordPerPage                  11
#define      RecordHeight                   11

#define      FNameX       		    0
#define      FNameY			    15


#define      TitleMaxWidth                 150	

#define	     BLACK_UP_ARROW			   "\x01"
#define	     BLACK_DOWN_ARROW		           "\x02"
#define	     GRAY_UP_ARROW			   "\x03"
#define	     GRAY_DOWN_ARROW			   "\x04"
		
/*************Global Variables****************************/
static   SystemPreferencesType    prefs;
static   DmOpenRef                dbRef;                    
 
static   DWord          TextSize=0,TitleTextSize=0;         
static   Word           recNumInCategory; 
static   SWord          currentRecIndex=0;   
static   SWord          firstVisibleMemoIndex=0;
static   Word           currentCategory=dmAllCategories;
static   Word           prevCategory=dmAllCategories;  
static   char           categoryName[dmCategoryLength];          
static   FontID         currentFont=stdFont;  
                    
static   Word           *VisibleRecordList=NULL;
static   Boolean         check;

static   Boolean         NewButtonSelected=false;
static   Boolean         InMainForm=false,InEditForm=false;  
static   char            String[5];  
//************Function Prototype Declaration ***********************************************

static  Err  StartApplication(void);
static  void EventLoop(void);
static  void StopApplication(void);

static Boolean  ApplicationHandleEvent(EventPtr event);
static Boolean  MainForm1000EventHandler(EventPtr  event);
static Boolean  EditForm1100EventHandler(EventPtr  event);
static Boolean  AboutForm1200EventHandler(EventPtr  event);

//**********Main Function of program**********************************************************

DWord  PilotMain (Word cmd, Ptr cmdPBP, Word launchFlags)
{    
     Err    err;	  
      

  if  (cmd == sysAppLaunchCmdNormalLaunch)
     {
      err=StartApplication();           
      if(err)
         return   err; 
      EventLoop();                  
      StopApplication ();           
    }
    return 0;
}

//----------------------------------------------------------------------------


static Err StartApplication(void)
{  
   
   Err     err;  	 
                  
   err=OpenDatabase();                            
   FrmGotoForm(MainForm1000);
   return err;
}



//----------------------------------------------------------------------------

static  void  EventLoop(void)
{ 
   short                err  ;
   EventType            event;
 
 do 
   {
      EvtGetEvent (&event, evtWaitForever);
     
    
       if ( ! SysHandleEvent(&event) )
       
          if ( ! MenuHandleEvent(NULL,&event,&err) )
        
             if  ( ! ApplicationHandleEvent(&event) )
           
             FrmDispatchEvent(&event); 
    } while(event.eType != appStopEvent);                 
}


//----------------------------------------------------------------------------

static void  StopApplication(void)
{
   FormPtr      form; 
   FieldPtr     field,titleField;	
   
       if(InEditForm)  {   
           form=FrmGetFormPtr(EditForm1100); 
           field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,Field1101) );	
           titleField=FrmGetObjectPtr(form,FrmGetObjectIndex(form,TitleField1109) );
              if(FldGetTextLength(field)==0 && FldGetTextLength(titleField)==0)  { 
                 DmRemoveRecord(dbRef,currentRecIndex);
              } 
              else  EditFormSaveRecord(form);
       }
   if(VisibleRecordList) {             
      MemPtrFree(VisibleRecordList);          
      VisibleRecordList=NULL;
   }
              
   FrmSaveAllForms ();
   FrmCloseAllForms();
   DmCloseDatabase (dbRef);
}


//********************************************************************************************
 //  This Function handles the event "frmLoadEvent" only.
   //  It should load the form resource and active the form;
     //  next,set the event handler for the specific active form in this routine!
          
      
static Boolean ApplicationHandleEvent(EventPtr event)
{
     FormPtr       form;
     Word          formID;
     Boolean       handled=false;
  	  
  	  
  	  
  if (event->eType == frmLoadEvent)          
 {
      formID=event->data.frmLoad.formID;
      form=FrmInitForm(formID);
      FrmSetActiveForm(form);
      
      switch (formID)
     {
      case MainForm1000 :
                         FrmSetEventHandler(form,MainForm1000EventHandler);
                         break;

      case EditForm1100 :
                         FrmSetEventHandler(form,EditForm1100EventHandler);
                         break;

      case AboutForm1200 :
                         FrmSetEventHandler(form,AboutForm1200EventHandler);
                         break;  
                                      
      } 	      
            
                               
      handled=true;
  }
   
  return  handled;
   
}



//---------------------------------------------------------------------
   // This Function handles the possible events in the current active form
     //  Being responsed to each event .
     
     
static Boolean  MainForm1000EventHandler(EventPtr  event)
{
   FormPtr       form;	
   Word          maxNum; 
   ControlPtr    trigger,upArrow,downArrow;
   Boolean       handled=false; 
    
	form = FrmGetActiveForm();
	trigger=FrmGetObjectPtr(form,FrmGetObjectIndex(form,MainFormCategoryTrigger1003) );
            
	if ( event->eType ==  ctlRepeatEvent ) {    
		upArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,UpRepeatButton1005));
		downArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,DownRepeatButton1006));
		maxNum = DmNumRecordsInCategory (dbRef,currentCategory);
		switch (event->data.ctlRepeat.controlID) {
			case  UpRepeatButton1005:
				{
					firstVisibleMemoIndex-=RecordPerPage;
					if ( firstVisibleMemoIndex <= 0 ) {
						CtlSetLabel( upArrow, GRAY_UP_ARROW );
						CtlSetEnabled( upArrow, false );
						firstVisibleMemoIndex = 0;
					}

					if ( maxNum > RecordPerPage ) {
						CtlSetLabel( downArrow, BLACK_DOWN_ARROW );
						CtlSetEnabled( downArrow, true );
					}
					MainFormListMemo(form);             

               break;
				}

			case DownRepeatButton1006:
				{
					firstVisibleMemoIndex+=RecordPerPage;
					if ( (firstVisibleMemoIndex+RecordPerPage) > maxNum ) {
						CtlSetLabel ( downArrow, GRAY_DOWN_ARROW );
						CtlSetEnabled( downArrow, false );
						firstVisibleMemoIndex = maxNum-RecordPerPage;
					}

					if ( firstVisibleMemoIndex > 0 ) {
						CtlSetLabel( upArrow, BLACK_UP_ARROW );
						CtlSetEnabled( upArrow, true );
					}
					MainFormListMemo(form);             
					break;
				}
			default:
 				break;
		} 
		handled=false;         
	} else  if ( event->eType == ctlSelectEvent ) {   
                   	 switch (event->data.ctlSelect.controlID)
		       { 
                   	case NewButton1002:            
                   	               
                   	                   NewButtonSelected=true;
										   if(VisibleRecordList) {             
												MemPtrFree(VisibleRecordList);          
												VisibleRecordList=NULL;
											}
              				   prevCategory=currentCategory;
              				   if(prevCategory==dmAllCategories)
              				      prevCategory=dmUnfiledCategory;
                	                   FrmGotoForm(EditForm1100); 
                   	                   handled=true;
                   	                   break;    
                   	                
                   	case  MainFormCategoryTrigger1003:
                   	 
                   	                          MainFormCategorySelect(form);                                                              
                   	              	          handled=true;
                   	              	          break;
                       }	
                   	
                   }	 
       else  if  ( event->eType == frmOpenEvent )
       
                   {    
  		        maxNum = DmNumRecordsInCategory (dbRef,currentCategory);
                        CategoryGetName(dbRef,currentCategory,categoryName);
                        CategorySetTriggerLabel(trigger,categoryName);
                	FrmDrawForm(form);
                	if(prevCategory!=currentCategory) { 
                	   firstVisibleMemoIndex=0;
                	}
                	else { 
                              if((firstVisibleMemoIndex+RecordPerPage) > maxNum ) {
                                 firstVisibleMemoIndex--;
                                 if(firstVisibleMemoIndex < 0)
                                    firstVisibleMemoIndex=0;
                              }
                             // else firstVisibleMemoIndex+= (maxNum-(firstVisibleMemoIndex+RecordPerPage));
                        }             	    
                        MemoNumsDisplay();             
                	RptBtnInit(form);
                        MainFormListMemo(form);
          	
                        InMainForm=true;
                        InEditForm=false;
                     	handled=true;
                     
                   }	
                   
       else  if  ( event->eType ==  penDownEvent )
       		   {	
       		   	NewButtonSelected=false;
         		handled = MemoViewHandlePen(event);
         	   }		
                   
        return    handled;
         	 
}


//-------------------------------------------------------------------------  
    	 
 
    
 static Boolean  EditForm1100EventHandler(EventPtr  event)   	 
{
	FormPtr       form;	
	FieldPtr      field,titleField;
	ControlPtr    trigger,checkBox;
	Word          command; 
	Word          maxNum;
	Boolean       handled=false; 
   
	form = FrmGetActiveForm();
	field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,Field1101) );
	titleField=FrmGetObjectPtr(form,FrmGetObjectIndex(form,TitleField1109) );
	trigger=FrmGetObjectPtr(form,FrmGetObjectIndex(form,EditCategoryTrigger1105) );
	//checkBox=FrmGetObjectPtr(form ,FrmGetObjectIndex(form,PrivateBox1107));
               
	if  (event->eType==frmOpenEvent) { 
		FldSetMaxChars(titleField,MaxTitleSize);
		(NewButtonSelected==true)?  CreateRecord() : EditFormGetRecord(form,field,titleField); 
		if(!NewButtonSelected)   
			EditFormCheckBoxInit(form); 
		FrmDrawForm(form);
		FrmSetFocus(form, FrmGetObjectIndex(form,TitleField1109) ); 
		EditFormCategoryListInit(trigger);
		InMainForm=false;  
		InEditForm=true; 
		handled=true;    			  
	} else  if  ( event->eType ==  ctlSelectEvent ) {     
		maxNum=DmNumRecordsInCategory(dbRef,currentCategory);
 		switch(event->data.ctlSelect.controlID) { 
 	      case  SaveButton1102:                 
 	      	EditFormSaveRecord(form);
 	      	if(maxNum > RecordPerPage)
 	      		firstVisibleMemoIndex++;
 	      	FrmGotoForm(MainForm1000);
   			handled=true;
 				break;		
 	      	    		               
 	      case  CancelButton1103 :                  // "CANCLE" Button  
				if(NewButtonSelected && (DmNumRecordsInCategory(dbRef,currentCategory)!=0))
					DmRemoveRecord(dbRef,currentRecIndex);
				FrmGotoForm(MainForm1000);  	     
 				handled=true;
				break;  
                                
			case  EditCategoryTrigger1105 :
				EditFormCategorySelect();
				handled=true;                       	     	   
    			break; 
    			               
    		case  PrivateBox1107 :       
    			//check=CtlGetValue(checkBox);
 	      	handled=true;
 	      	break;                             
 	  	}
	} else  if  ( event->eType == menuEvent ) {     // if one item in the menu is chosen
		command = event-> data.menu.itemID; 	
		if( MenuDoCommand(command) )	
                            handled = true;   	
	} else  if  (event->eType == fldChangedEvent) {
		EditFormUpdateScrollBar (form,field);
		handled = true;
	} else  if  ( event->eType == sclRepeatEvent ) {       
		ScrollLine(form,field,event->data.sclRepeat.newValue, event->data.sclRepeat.value);
		handled = false;
	}     
     	
	return    handled;
}


//-------------------------------------------------------------------------  
static Boolean  AboutForm1200EventHandler(EventPtr  event)
{ 
    FormPtr    form;	 
    Boolean    handled=false;
    
    	      form=FrmGetActiveForm();	 
	      if(event->eType == ctlSelectEvent)
                    {
       	                 switch(event->data.ctlSelect.controlID)
       	                {
       	                        case  OKButton1201: 
       	                                            
       	                                            FrmReturnToForm(EditForm1100);
       	                                            handled=true; 	 
       	                }  	  
       	 
                    }	
        	
      else   if( event->eType == frmOpenEvent)
                  {
                      FrmDrawForm(form);	
                      handled=true; 	 	
                  }  	 
	  
     return  handled;	
    
}

//********************************************************************************************
  //  This function opens the database(or create a new one if necessary)
             
   static Err OpenDatabase(void) 
{ 
//  LocalID   dbId;	
//  Byte      cardNo=0;                              // only one mem-card 
    Err       error;
    Word      mode;      
                   
  	   mode = dmModeReadWrite; 	
           PrefGetPreferences(&prefs);
           if(!prefs.hideSecretRecords)
              mode |= dmModeShowSecret;	  
                  //Open a database if it exists,or creates a new one         
	// Find the application's data file.  If it doesn't exist create it.
	error = DmCreateDatabase(0,dBName,creatorID,dBType,false);

	if ((error == 0)||(error == dmErrAlreadyExists)) {
		mode = dmModeReadWrite;

  	   dbRef=DmOpenDatabaseByTypeCreator(dBType,creatorID,mode);   

      DbAppInfoInit(); 	 //Initialize appInfo-block
		if (!dbRef)
			return (1);
	}

/*        
    	   dbRef=DmOpenDatabaseByTypeCreator(dBType,creatorID,mode);   
   	   if(!dbRef)            
   	{   
           if( DmCreateDatabase(0,dBName,creatorID,dBType,false) !=0 )    
                  return  -1;// error=DmGetLastErr();
           dbRef=DmOpenDatabaseByTypeCreator(dBType,creatorID,mode);
   	   if( !dbRef)
   	   return   -1;//error=DmGetLastErr();        
   	 }  
*/   	 
             error=0 ;
      return error;
 }  
 
//-----------------------------------------------------------------------------

  //  We define this function to set database information,
     //  Here  handles  Attributes field of Database Header only . 
  
  static Err SetDatabaseInfo(Word flag)  
  { 
    LocalID   id;
    Word      cardNum;
    Word      attribute; 
    Word      mask=0xffff;
    
    DmOpenDatabaseInfo(dbRef,&id,NULL,NULL,&cardNum,NULL);
    
    DmDatabaseInfo(cardNum,id,NULL,&attribute,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
     attribute &= ~mask  ; //clear field
     attribute |=  flag  ; //set   attributes
     DmSetDatabaseInfo(cardNum,id,NULL,&attribute,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); 
     
     
    return 0;	   	   
   } 

//------------------------------------------------------------------------------- 
  //This routine initialize the AppInfo Block of a database 
    // if the block doesn't exist ,create a new one.
    
 static  Err  DbAppInfoInit(void)
 {
 	  LocalID   dbID;
 	  Word      cardNum;
 	  LocalID   appInfoID;
 	  VoidHand  appInfoH;
 	  VoidPtr   appInfoP;  
 	  Word	    i;   	
	  Char	    *name[4] = { "Unfiled", "Business", "Personal", "" };
 	  
 	  
 	  
 	      //retrieve appInfoID
 	  
 	if ( DmOpenDatabaseInfo(dbRef ,&dbID ,NULL ,NULL ,&cardNum ,NULL) )
 	  
 	    return dmErrInvalidParam ;
 	    
 	if ( DmDatabaseInfo(cardNum , dbID , NULL,NULL,NULL,NULL,NULL,NULL,NULL,&appInfoID,NULL,NULL,NULL) )
 	
 	      return dmErrInvalidParam ;
 	      
      
             // create a new appInfo block if necessary
             
         if ( appInfoID == 0 )
              {    
                   appInfoH = DmNewHandle(dbRef , sizeof(AppInfoType));
                   
                   appInfoID =MemHandleToLocalID (appInfoH);      //convert handle to mem chunk                         
 								  //  LocalID 	
                     
                   DmSetDatabaseInfo(cardNum,dbID,NULL,NULL,NULL,NULL,NULL,NULL,NULL, &appInfoID,NULL,NULL,NULL);
              } 
              
                 appInfoP = MemLocalIDToLockedPtr(appInfoID , cardNum);                                     
                                                
                 DmSet(appInfoP , 0 , sizeof(AppInfoType) , 0);       // clear appInfo block
                                         
                 CategoryInitialize( (AppInfoPtr) appInfoP ,MainFormCategoryList1004);
		 for ( i = 0; i < 3; i++ ) {
			CategorySetName (dbRef, i, name[i]);
	 	 }

		 for ( i = 3; i < 16; i++ ) {
			CategorySetName (dbRef, i, name[3]);
	 	 }
                 
                 MemPtrUnlock(appInfoP);
                 
                 return 0;
  
       //     CategoryCreateList(dbRef,CategoryList,1,true,true,4,categoryDefaultEditCategoryString,false);   
       //     CategoryFreeList(dbRef,CategoryList,true,categoryDefaultEditCategoryString);             
 
 
 }
 
 

//-----------------------------------------------------------------------------------------
/*   
static void LocalizeAppInfo(AppInfoPtr appInfoP)
{
	VoidHand       localAppInfoH;
	VoidPtr        localAppInfoP;
	VoidHand        stringsH;
	Char**         stringsP;
	AppInfoPtr      nilP=NULL;  
	Word             i=0;
	      
	localAppInfoH = DmGetResource( 'tSTL', AppInfoString1000);
	if (localAppInfoH)
      {
	    localAppInfoP = MemHandleLock(localAppInfoH);
	    stringsH = SysFormPointerArrayToStrings(localAppInfoP+ StrLen((Char *)localAppInfoP) + 3,dmRecNumCategories);
            stringsP = MemHandleLock(stringsH);  	
	  for (i = 0; i < dmRecNumCategories ; i++)
	              {
			if (stringsP[i][0] == '\0') break;
//			if (stringsP[i][0] != '\0')
			DmStrCopy(appInfoP, (DWord) nilP->categoryLabels[i], stringsP[i]);
		      }
                MemPtrFree(stringsP);
		MemPtrUnlock(localAppInfoP);
		DmReleaseResource(localAppInfoH);
       }
}

*/
//******************************************************************************************

static Boolean CreateRecord (void)
{    
      VoidHand    recordH;
      VoidPtr     recordP;  
      Word        index;	 
      DWord       offset=0;
      char        null=0;
      Word        category;
                     
 
      index= DmNumRecords(dbRef);         // put the record to the end of the database. 

      //   index=0;                      // put the record to the start of the database. 
      recordH=DmNewRecord(dbRef,&index,newRecordSize);  //if no record found
         if ( !recordH )                               // create a new record & set its busy bit
      	    return 0; 	                                 //return a handle for the record
      recordP=MemHandleLock(recordH);                // Lock the handle
      DmSet( recordP , offset , newRecordSize , 0);       //clear the record
      MemHandleUnlock(recordH); 
       
      currentRecIndex =index;
      
        //set the category of the record
       category = currentCategory;
       SetRecordCategory(&category);  
      
      // set the secret attribute of the record 
       //  SetRecordSecret();     
        
     DmReleaseRecord(dbRef,index,true);       //clear the busy bit for the record 
                                 		  //and set its dirty bit
        
     return(true);
        
}  
 


//--------------------------------------------------------------------------------------
  // this routine sets the record  category.
 
  
  static  void  SetRecordCategory(Word* category)   
{       
  
   	Word        attribute; 
   	Word        index=currentRecIndex;
   
         DmRecordInfo(dbRef,index,&attribute,NULL,NULL);    
         attribute &= ~dmRecAttrCategoryMask;                
         if( *category == dmAllCategories)
                    attribute |= dmUnfiledCategory ;
         else       attribute |= *category;
         DmSetRecordInfo(dbRef , index , &attribute , NULL); 
              
 } 


//---------------------------------------------------------------------------------------

static    Word   GetRecordCategory(Word  *index)
{   
	Word  category;
        Word  attribute;
	
    DmRecordInfo(dbRef,*index,&attribute,NULL,NULL);
    category=attribute&dmRecAttrCategoryMask;
    return(category); 	 
}

//--------------------------------------------------------------------------------------

static    void   SetRecordSecret(FormPtr form)

{       
/*
	FormPtr     form=FrmGetActiveForm();
	ControlPtr  checkBox=FrmGetObjectPtr(form ,FrmGetObjectIndex(form,PrivateBox1107));
        Word        attribute; 
   	Word        index=currentRecIndex;
         
         if(CtlGetValue(checkBox))  {
         DmRecordInfo(dbRef , currentRecIndex ,&attribute ,NULL,NULL);    //retrieve the attribute of record
                 
         
         attribute |= dmRecAttrSecret;                //  set the secret bit
           
        DmSetRecordInfo(dbRef , currentRecIndex , &attribute , NULL);   //set attribute  of record
          }    
*/

}
//-------------------------------------------------------------------------------------

static    void   SetRecordUnsecret(FormPtr form)

{       
/*
	FormPtr     form=FrmGetActiveForm();
	ControlPtr  checkBox=FrmGetObjectPtr(form ,FrmGetObjectIndex(form,PrivateBox1107));
        Word        attribute; 
   	Word        index=currentRecIndex;
         
         if(!CtlGetValue(checkBox))  
            {
              DmRecordInfo(dbRef , currentRecIndex ,&attribute ,NULL,NULL);    //retrieve the attribute of record
                 
              attribute &= 0xef;                
         
              DmSetRecordInfo(dbRef , currentRecIndex , &attribute , NULL);   //set attribute  of record
            }    
*/
}
//--------------------------------------------------------------------------------------
  // This function saves the record we edit,
    // Write the data into the record
  
static  void    EditFormSaveRecord(FormPtr form)
{
	FieldPtr        field,titleField;
	CharPtr         textP,titleTextP;
	Boolean         dirty,empty,noTitle;
	VoidHand        recordH;
	VoidPtr         recordP;	
	DWord           offset=0;
	char            null=0;
      
	field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,Field1101) );
	titleField=FrmGetObjectPtr(form,FrmGetObjectIndex(form,TitleField1109) );
	textP =  FldGetTextPtr(field);     
	titleTextP= FldGetTextPtr(titleField); 
	dirty=  FldDirty(field);                // being true if the record modified 
	empty= (textP==NULL)||(FldGetTextLength(field)==0);   
	noTitle=(titleTextP==NULL)||(FldGetTextLength(titleField)==0);    
	FldReleaseFocus(field); FldReleaseFocus(titleField);   
//       FldCompactText(field);    FldCompactText(titleField);
        
	if (!empty ||!noTitle) {     
		TitleTextSize=(titleTextP==NULL)? 1 : StrLen(titleTextP)+1;
		TextSize = (textP==NULL)? 1 : StrLen(textP)+1;
		recordH =DmResizeRecord(dbRef,currentRecIndex,TitleTextSize+TextSize);    
		recordP =MemHandleLock(recordH) ;
		if(titleTextP!=NULL) {
			DmStrCopy(recordP,offset,titleTextP);
			offset=TitleTextSize;
			(textP==NULL)?DmWrite(recordP,offset,&null,sizeof(char)):
								DmWrite(recordP,offset,textP,TextSize);  
		} else{
			DmWrite(recordP,offset,&null,sizeof(char));
			offset++;
			(textP==NULL)?DmWrite(recordP,offset,&null,sizeof(char)):
								DmWrite(recordP,offset,textP,TextSize); 
		}              
		MemHandleUnlock(recordH);
		DmReleaseRecord (dbRef, currentRecIndex, true );  
                     
		if(check)   SetRecordSecret(form);
		else        SetRecordUnsecret(form);  
		dirty=false; 
	} else
		DmRemoveRecord (dbRef, currentRecIndex);
}         
 
 
 
//------------------------------------------------------------------------------------
  // This routine deletes the record indeed .
    // When deleted,display the alert dialog to confirm
         
  
  static Boolean    DeleteRecord(Word index)
{
     Boolean    result; 
     Word       hitButton; 
     
     FormPtr    form;
     FieldPtr   field;           
     char *     textP;
     Boolean    empty;          
     
        
        
           form  =   FrmGetActiveForm();
           field =   FrmGetObjectPtr(form,FrmGetObjectIndex(form,Field1101) );
           textP =   FldGetTextPtr(field) ;
           empty = (textP==NULL);      

      if (!empty)          
            {   
                 //alert    = FrmInitForm(DeleteAlert3100);      // load & initial the Delete-Alert resource
                                   		                // returns the alert ptr. 	
                // hitButton= FrmDoDialog(alert);                //  display the dialog & return the button ID
                hitButton= FrmAlert(DeleteAlert3100);              // which is tapped.
                 //FrmDeleteForm( alert );                                              
               //hitButton= FrmCustomAlert( DeleteAlert3100 ,"OK","CANCEL",NULL);
                                                                
                 if ( hitButton == alert_Cancel_Button )
                       {    
          		 result = false;
          	 	 return(result);                     
                       }
                  
                     else  { 
                     	      DmRemoveRecord (dbRef, index);   
                  	     
                	   }      
              }        	       
                  	       
      else {   
                 
              DmRemoveRecord (dbRef, index);          	       
           }         	       
                    
               result=true;   
               return(result);             
}          
                  


//--------------------------------------------------------------------------------



//--------------------------------------------------------------------------------

static  void   EditFormGetRecord(FormPtr form,FieldPtr field,FieldPtr  titleField)

{
     
     VoidHand     recordH;
     CharPtr      recordP;
     Word         index;
   
  
     	index=currentRecIndex;
        recordH = DmGetRecord(dbRef,index);     
        if(recordH)  {
           recordP = MemHandleLock(recordH);
           if(recordP)  {
              FldInsert(titleField, recordP, StrLen(recordP) );
 	      recordP += (StrLen(recordP)+1); 	
              FldInsert(field,recordP,StrLen(recordP));
           }
           MemHandleUnlock(recordH);
           DmReleaseRecord(dbRef,index,true);
        }
	     	   
}     	            


//--------------------------------------------------------------------------------------

static void EditFormCategoryListInit(ControlPtr  trigger)
{
	FormPtr   form=FrmGetActiveForm();
	
	if(!NewButtonSelected)
		currentCategory=GetRecordCategory(&currentRecIndex);
	else {
		if(NewButtonSelected && (currentCategory==dmAllCategories))
		currentCategory=dmUnfiledCategory;
	} 
	CategoryGetName(dbRef,currentCategory ,categoryName);
	CategorySetTriggerLabel(trigger, categoryName); 
}	
 
//**********************************************************************************************






//------------------------------------------------------------------------------

static  void     MainFormCategorySelect(FormPtr  form)    

{ 
	Word       category;
	Boolean    selected;	
	//Word       recNumInCategory;
	 
	category=currentCategory;
	selected= CategorySelect(dbRef,form,MainFormCategoryTrigger1003,MainFormCategoryList1004,true,&category,categoryName,
	                                 1,categoryDefaultEditCategoryString);  
	 
	if(selected || (category != currentCategory))  {
		FrmEraseForm(form);
		FrmDrawForm(form);  
		currentCategory=category; 
		firstVisibleMemoIndex=0;   
		if(VisibleRecordList) {
			MemPtrFree(VisibleRecordList);
			VisibleRecordList=NULL; 
		} 
		MemoNumsDisplay();	
		RptBtnInit(form);
		MainFormListMemo(form);
	}   	
}	



//------------------------------------------------------------------------------------
/*
static      void     MainFormCategoryListInit(ControlPtr  trigger)
{
	
	    
	    if(currentCategory==dmUnfiledCategory)
               currentCategory=dmAllCategories;
            CategoryGetName(dbRef,currentCategory ,categoryName);
            CategorySetTriggerLabel(trigger, categoryName);
	
}	
*/
//********************************************************************************************
 // This routine executes the command of the menu item
 
 
 static   Boolean   MenuDoCommand(Word command)	
 { 
 	FormPtr    form ; 
 	FieldPtr   fieldFocusP;        
 	FieldPtr   field,titleField;
 	Word       index,fieldIndex;
        Word       maxNum; 
 	Word       textLength;
 	Boolean    handled=false;
       	
         form  = FrmGetActiveForm();
         field =  FrmGetObjectPtr(form,FrmGetObjectIndex(form,Field1101) );
         titleField= FrmGetObjectPtr(form,FrmGetObjectIndex(form,TitleField1109) );
         fieldIndex = FrmGetFocus(form);  

			maxNum=DmNumRecordsInCategory(dbRef,currentCategory); 
 
        switch( command )
     {
         case    NewItem2101:                            // To create a new record
            						NewButtonSelected=true;
                               EditFormSaveRecord(form);
                               if(maxNum > RecordPerPage)
 	      	      		  firstVisibleMemoIndex++;
                               CreateRecord();
                               FldFreeMemory (field);
                               FldFreeMemory(titleField);
                               FldDrawField (field); 
                               FldDrawField(titleField);
                               FrmSetFocus (form, FrmGetObjectIndex(form,TitleField1109) );      
                               handled=true;
                               break; 
         case    DeleteItem2102:                         // To delete a record
                                 index=currentRecIndex;
                                 if( DeleteRecord(index) ) {
                                     firstVisibleMemoIndex--;
                                     if(firstVisibleMemoIndex < 0)
                                        firstVisibleMemoIndex=0;  	
                                     FrmGotoForm(MainForm1000); 
                                 }    
                                 handled=true;
                                 break;
         case    CutItem2104 : 
         case    UndoItem2103:                     // Undo the last change made to the field object
         case    CopyItem2105: 
         case    PasteItem2106:
         case    SelectAllItem2107:
				if (fieldIndex == noFocus )
					return (false);
				fieldFocusP = FrmGetObjectPtr(form , fieldIndex);
            
				switch (command) {
					case    UndoItem2103:                     // Undo the last change made to the field object
						FldUndo (fieldFocusP);
						handled=true;
						break;
          
					case    CutItem2104 : 
						FldCut ( fieldFocusP );
						handled=true;  
         			break;	 
         
					case    CopyItem2105: 
         			FldCopy (fieldFocusP);
						handled=true;
						break;       
					case    PasteItem2106:
						FldPaste (fieldFocusP ); 
						handled=true;
						break;
                                 
					case    SelectAllItem2107:
   					textLength=FldGetTextLength(fieldFocusP);
   					FldSetSelection (fieldFocusP, startPosition ,startPosition + textLength);	       
           		  	handled=true;			  
						break;
				}
				break;   
          
          
         case    AboutItem2108:  
                                  if(maxNum > RecordPerPage)
 	      	      		     firstVisibleMemoIndex++;
                                  FrmPopupForm(AboutForm1200);                   
             	                  break; 
     	  
         case    KeyboardItem2109:  
                                    SysKeyboardDialog(kbdDefault);
                                    handled=true;
                                    break;
       
         case    Graffiti2110:   
//                                   SysGraffitiReferenceDialog(referenceDefault);
                                   handled=true;
                                    break;   
      }    
          
      return(handled);    
}



//***************************************************************************************



//--------------------------------------------------------------------------------------

static  void     EditFormCategorySelect(void)
{      
	FormPtr  form=FrmGetActiveForm();
	Word     index;	
	Word     attribute,category;
	Boolean  selected;
       
	// get current record's category
	index=currentRecIndex;
	DmRecordInfo(dbRef,index,&attribute,NULL,NULL);
	category = attribute&dmRecAttrCategoryMask;       
	selected=CategorySelect(dbRef,form,EditCategoryTrigger1105,EditCategoryList1106,false,&category,  
										categoryName,1,categoryDefaultEditCategoryString);
	if(selected || (category !=(attribute&dmRecAttrCategoryMask)))  {
		SetRecordCategory(&category); 
		currentCategory=category; 	
	}
}        	                             
        


//******************************************************************************************

static void 	EditFormUpdateScrollBar(FormPtr form,FieldPtr  field)
{  
  
   ScrollBarPtr   scrollP;
   Word           scrollPosition;
   Word           textHeight;
   Word           fieldHeight;
   SWord          maxValue; 	
	     
	 
	
	FldGetScrollValues(field ,&scrollPosition,&textHeight,&fieldHeight);
	//ErrFatalDisplayIf(true,StrIToA(String, scrollPosition));
	if (textHeight > fieldHeight)
	{  
           maxValue =(textHeight-fieldHeight)+FldGetNumberOfBlankLines(field);
        }   
   else if (scrollPosition)
           { 
             maxValue = scrollPosition;
           }  
       else
	    maxValue = 0;
              
        scrollP=FrmGetObjectPtr(form,FrmGetObjectIndex(form,Scrollbar1104));
	SclSetScrollBar(scrollP, scrollPosition, 0, maxValue, fieldHeight-1);

}      


//-------------------------------------------------------------------------------------


static  void    ScrollLine(FormPtr form,FieldPtr field,SWord newValue ,SWord value)
{
      	 
    Word             linesToScroll;
    Boolean          direction;
   
  
   
    	   linesToScroll=(newValue > value)?(newValue-value):(value-newValue);
    	   direction=(newValue < value)? up : down;
    	   FldScrollField(field,linesToScroll,direction);
    	   //if( FldGetNumberOfBlankLines (field) ) 
    	   EditFormUpdateScrollBar(form,field);
       
      /*     scrollP= FrmGetObjectPtr( form,FrmGetObjectIndex(form,Scrollbar1104) );
    	     SclGetScrollBar(scrollP,&currentPosition,&min,&max,&pagesize);
    	     if(direction==up)
    	         currentPosition -= linesToScroll;
    	   else  currentPosition += linesToScroll;     
          SclSetScrollBar (scrollP, currentPosition, min, max, pagesize);
       */
          
}  



//***************************************************************************************

  static  void  EditFormCheckBoxInit(FormPtr form)
 {
/*  	
    ControlPtr  checkBox;
    Word        index=currentRecIndex;	           
    Word        attribute;
     	       
     	      checkBox=FrmGetObjectPtr(form ,FrmGetObjectIndex(form,PrivateBox1107));
     	      DmRecordInfo(dbRef , index ,&attribute ,NULL,NULL);   
     	      attribute &= 0x10;
     	      if(attribute) 
     	      CtlSetValue(checkBox,1);
*/     	      
     	    
 }   	           
     
     
     
//*****************************************************************************************//

void    MemoNumsDisplay()
{
	Word     memoNum=DmNumRecordsInCategory(dbRef,currentCategory);
	char     totalMemoIndex[4];
	Word     totalMemoIndexLength=0;
	
	StrIToA(totalMemoIndex,memoNum);
	while (memoNum) {
		memoNum /= 10;
		totalMemoIndexLength++;
	}
	totalMemoIndex[totalMemoIndexLength]=0;
	
	if(totalMemoIndex[0]!=0) 
	WinDrawChars(totalMemoIndex,StrLen(totalMemoIndex),Memo_Index_Start+45,1);
	else 
	WinDrawChars("0",1,Memo_Index_Start+45,1);
	WinDrawChars("Memos",5,Memo_Index_Start+60,1);

}
   
   
void   RptBtnInit(FormPtr  form)
{
	
	ControlPtr	upArrow;
	ControlPtr	downArrow;
	Word            memoNum;

	upArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,UpRepeatButton1005));
	downArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,DownRepeatButton1006));
	memoNum = DmNumRecordsInCategory (dbRef,currentCategory);
        
        if(memoNum <=  RecordPerPage)  {
             CtlHideControl(upArrow);
             CtlHideControl(downArrow);
             return;
        }
        else  {
        	 CtlShowControl(upArrow);
                 CtlShowControl(downArrow);
        }     	
	if ( firstVisibleMemoIndex <= 0 ) {
	     CtlSetLabel( upArrow, GRAY_UP_ARROW ); 
	     CtlSetEnabled( upArrow, false );
	} else {
		CtlSetLabel( upArrow, BLACK_UP_ARROW );
		CtlSetEnabled( upArrow, true );
	  }
	if ( memoNum > RecordPerPage ) {
	     CtlSetLabel( downArrow, BLACK_DOWN_ARROW );
	     CtlSetEnabled( downArrow, true );
	} else {
		CtlSetLabel( downArrow, GRAY_DOWN_ARROW );
		CtlSetEnabled( downArrow, false );
	}
	if(firstVisibleMemoIndex+RecordPerPage >= memoNum) {
		CtlSetLabel( downArrow, GRAY_DOWN_ARROW );
		CtlSetEnabled( downArrow, false );
        }		
	
}	
	


   void  MainFormListMemo(FormPtr  form)       
{   
   
	VoidHand	recordH;
	VoidPtr		recordP;	
	Word		indexStart=0,count=0; 
	Char		numBuffer[4];
        CharPtr         titleP; 
	Word		numLength, tcount;	
	Word            titleMaxLength;
	RectangleType	eraseRect;
	Word            totalRec=DmNumRecords(dbRef); 
	
	RctSetRectangle (&eraseRect, 0, 15, 160, 121);
	WinEraseRectangle (&eraseRect, 0);
	
	recNumInCategory=DmNumRecordsInCategory(dbRef,currentCategory);
	if(recNumInCategory) 
	   VisibleRecordList=MemPtrNew(recNumInCategory*sizeof(Word)) ;
	while (!DmSeekRecordInCategory (dbRef, &indexStart, 0, dmSeekForward, currentCategory)) {  
		recordH = DmQueryRecord (dbRef, indexStart+firstVisibleMemoIndex);  
		if(VisibleRecordList)
		*(VisibleRecordList+count/*+firstVisibleMemoIndex*/)=indexStart+firstVisibleMemoIndex;  
		if (recordH) {
			tcount = firstVisibleMemoIndex+count+1;
			StrIToA (numBuffer, tcount);
			numLength = 0;
			while (tcount) {
				tcount = tcount/10;
				numLength++;
			}
			tcount =  firstVisibleMemoIndex+count+1;
			recordP = MemHandleLock(recordH);
		        titleP=MemPtrNew(StrLen(recordP)+1);
		        if(titleP) {
             		   MemSet(titleP,StrLen(recordP)+1,0);
             		   MemMove((void*)titleP,recordP,StrLen(recordP)+1);
             		}

			numBuffer[numLength+1] = 0;
			numBuffer[numLength] = '.';
				if ( tcount < 10 ) {
					WinDrawChars (numBuffer, StrLen(numBuffer), FNameX+5, count*RecordHeight+15);
				} else {
					WinDrawChars (numBuffer, StrLen(numBuffer), FNameX, count*RecordHeight+15);
				}
				if(titleP)  {
			 	   titleMaxLength=FntWordWrap(titleP,TitleMaxWidth);
			 	   WinDrawChars (titleP, titleMaxLength, FNameX+15, count*RecordHeight+15);
			 	}   
				count++;
		        
			MemHandleUnlock(recordH);
			MemPtrFree(titleP);
			
			if ( count >= RecordPerPage )
			     break;
		}
		indexStart++;
	}

	     	  
  	 
}
      	           
      	           
      	           

/***********************************************************************
 *
 * FUNCTION:    MailViewHandlePen
 *
 * DESCRIPTION: Handle pen movement in the MailViewDisplay. 
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if handled.
 *
 * REVISION HISTORY:
 *         Name   Date      Description
 *         ----   ----      -----------
 *         roger   11/27/95   Cut from RecordViewHandleEvent
 *
 ***********************************************************************/
static Boolean MemoViewHandlePen (EventType * event)
{
	Boolean        handled = false;
	RectangleType  r,invertRec;
	Word           x, y;
	Boolean        penDown;
	Word           maxNum = DmNumRecordsInCategory (dbRef,currentCategory);
   	Word           rows,orderInCategory;
  
   // If the user taps in the MemoViewDisplay take them to the Edit View
   	rows=Min(RecordPerPage,maxNum);
	RctSetRectangle (&r, 0,FNameY, 160, rows*RecordHeight);
    
	if (RctPtInRectangle (event->screenX, event->screenY, &r)) {
		invertRec=MemoInvert(event->screenY);
		do {
			PenGetPoint (&x, &y, &penDown);
        } while (penDown);
      
		if (RctPtInRectangle (x, y, &invertRec)) {
			orderInCategory = ((y-15)/RecordHeight)/*+firstVisibleMemoIndex*/;
			currentRecIndex=VisibleRecordList[orderInCategory];
			if ( currentRecIndex < DmNumRecords(dbRef))  {
			   if(VisibleRecordList) {             
					MemPtrFree(VisibleRecordList);          
					VisibleRecordList=NULL;
				}
                                prevCategory=currentCategory;
                                if(prevCategory==dmAllCategories)
              		           prevCategory=dmUnfiledCategory;
				FrmGotoForm (EditForm1100);
				return handled;
			}
		}
		else  {
		       	MemoInvert(event->screenY);
         	}
		handled = true;
	}
	return handled;
}



 RectangleType  MemoInvert(SWord  y)
{
       RectangleType   r;
       Word             index;
       

	index = ((y-15)/RecordHeight);
       	  y =	index*RecordHeight+15;
       RctSetRectangle(&r,FNameX,y,160 ,RecordHeight);
       
       WinInvertRectangle(&r,0);	
       return r;
	
}	
      	           