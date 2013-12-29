 /**********************************************************
 * Company     : Wiscore Inc                               * 
 *                                                         *  
 * Filename    : Address.c                                 *
 *                                                         * 
 * Description : The AP of Address Book                    *	
 *		 					   *	
 * History     : 2001/09/10  by Vincent Chen	           *	
 **********************************************************/ 

#include <Pilot.h>
#include <System/SysAll.h>
#include <UI/UIAll.h>

#include "address.h"
#include "addressRsc.h"

//***********************Symbol  Redefine ***************************************************************
#define      textStartPosition       0

#define      NoAddressRecordID      -1
#define      newRecordSize          16

#define      totalFieldNum          16
#define      fieldNumInPage         10
#define      CustomFieldNum          4

#define      TopLabelLeftPosition     0
#define      TopLabelTopPosition     18
#define      TopFieldLeftPosition    48
#define      TopFieldTopPosition     18      
#define      FieldTopPosition           18
#define      FieldBottomPosition       128
#define      FieldWidth		       110

//-------------------------------------------
#define      Address_Index_Start             0

#define      RecordPerPage                  11
#define      RecordHeight                   11

#define      FNameX       		    0
#define      FNameY			    15

#define      FirstNameMaxWidth              65	
#define      LastNameMaxWidth	            65
#define	     BLACK_UP_ARROW		    "\x01"
#define	     BLACK_DOWN_ARROW		    "\x02"
#define	     GRAY_UP_ARROW	    	    "\x03"
#define	     GRAY_DOWN_ARROW		    "\x04"


//*************************Global  Variables**************************************************
static      DmOpenRef          AddressDb;
static      AppInfoPtr         appInfoP;
static      SystemPreferencesType  prefs;
static      Word               cardNum;
static      SWord              currentRecIndex=0;
static      SWord              firstVisibleAddressIndex=0;
static      Word               currentCategory=dmAllCategories;        
static      Word               prevCategory=dmAllCategories;  
static      Word               recNumInCategory;
static      char               categoryName[dmCategoryLength]; 
static      Word*	       VisibleRecordList;	

static      Boolean            NewButtonSelected=false;
static      Boolean            currentRecordSaved=false;
static      Boolean            check;

static      SWord              fieldCountStart=0;
static      SWord              fieldCount;
static      SWord              fieldCountEnd=fieldNumInPage-1;     
static      FontID             currentFont; 

static      char*              CustomFieldList[4]={"Custom1 :", "Custom2 :", "Custom3 :", "Custom4 :" };                                   
static      char               String[5];              // just for debug...

//************************Function Prototype Declaration******************************************
static  Err      StartApplication(void);    
static  void     EventLoop(void);
static  void     StopApplication(void);
static  Boolean  ApplicationHandleEvent(EventPtr event);
static  Boolean  MainForm1000HandleEvent(EventPtr  event);
static  Boolean  EditForm1100HandleEvent(EventPtr  event);
static  Boolean  AboutForm1300HandleEvent(EventPtr  event); 
static  Boolean  CustomFieldForm1400HandleEvent(EventPtr  event); 
static  Boolean  SecretAddressForm1600HandleEvent(EventPtr event);       
//**********Main Function of program,where the entry point is**********************************************************

DWord  PilotMain (Word cmd, Ptr cmdPBP, Word launchFlags)
{    
     Err    err;	  
      

  if  (cmd == sysAppLaunchCmdNormalLaunch)
     {
      err=StartApplication();            // Application start code
      ErrFatalDisplayIf( (err),"Database Not Found");
      EventLoop();                   // Event loop
      StopApplication ();            // Application stop code
    }
    return 0;
}



//----------------------------------------------------------------------------


static Err StartApplication(void)
{  
   Word    flag;
   Err     err;  	 
                                   
                                 
                  
   err=OpenAddressDatabase();                               // Open database or create a new one  if necessary  
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
    
   
   fieldCountStart=0;
   fieldCountEnd=fieldNumInPage-1;
   
   FrmSaveAllForms ();

   FrmCloseAllForms();
   DmCloseDatabase (AddressDb);
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
                         FrmSetEventHandler(form,MainForm1000HandleEvent);
                         break;

      case EditForm1100 :
                         FrmSetEventHandler(form,EditForm1100HandleEvent);
                         break;
                         
      case AboutForm1300:    
                         FrmSetEventHandler(form,AboutForm1300HandleEvent);
                         break;         
                         
      case CustomFieldForm1400:    
                         FrmSetEventHandler(form,CustomFieldForm1400HandleEvent);
                         break;  
                                               
      case SecretAddressForm1600:
                         FrmSetEventHandler(form,SecretAddressForm1600HandleEvent);
                         break; 
                                                                                          
      } 	  
            
                               
      handled=true;
  }
   
  return  handled;
   
}


//--------------------------------------------------------------------------------------

static   Boolean    MainForm1000HandleEvent(EventPtr  event)
{
     FormPtr        form;	
     ControlPtr     trigger,upArrow,downArrow; 
     Word           maxNum;
     Boolean        handled=false;
         	
   	  
   	 form = FrmGetActiveForm(); 
   	 trigger=FrmGetObjectPtr(form,FrmGetObjectIndex(form,MainFormCategoryTrigger1001) ); 
   	  
         if(event->eType == frmOpenEvent)
              { 
              	CategoryGetName(AddressDb,currentCategory ,categoryName);
                CategorySetTriggerLabel(trigger, categoryName);
                FrmDrawForm(form);
                if(prevCategory!=currentCategory) { 
                    firstVisibleAddressIndex=0;
                }
                else {
                      if((firstVisibleAddressIndex+RecordPerPage) > maxNum ) {
                          firstVisibleAddressIndex--;
                          if(firstVisibleAddressIndex < 0)
                             firstVisibleAddressIndex=0;
                      }
                }             	    
                AddressNumsDisplay();             
                RptBtnInit(form);
                MainFormListAddress(form);
                handled=true;
                	 
              }
    else if ( event->eType ==  penDownEvent )
       		   {	
       		   	NewButtonSelected=false;
         		handled = AddressViewHandlePen(event);
         	   }		
              
    else if(event->eType == ctlSelectEvent)
    
              {    
              	   switch(event->data.ctlSelect.controlID)
              	  {
              	         case  NewButton1004:
              	         	              currentRecIndex=NoAddressRecordID;
              	         	              NewButtonSelected=true;
              				      
              				      prevCategory=currentCategory;
              				      if(prevCategory==dmAllCategories)
              				         prevCategory=dmUnfiledCategory;
              	                              FrmGotoForm(EditForm1100);
              	                              handled=true;
              	                              break;
              	                           
              	         case  MainFormCategoryTrigger1001:
              	                                            MainFormCategorySelect(form);  
              	                                            handled=true;
              	                                            break;                                          
              	  }       
              	 
              }
    else if(event->eType == ctlRepeatEvent)
    
               {
		upArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,UpRepeatButton1005));
		downArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,DownRepeatButton1006));
		maxNum = DmNumRecordsInCategory (AddressDb,currentCategory);
		
		switch (event->data.ctlRepeat.controlID) {
				
			case  UpRepeatButton1005:
				{
				  firstVisibleAddressIndex-=RecordPerPage;
				  if ( firstVisibleAddressIndex <= 0 ) {
					CtlSetLabel( upArrow, GRAY_UP_ARROW );
					CtlSetEnabled( upArrow, false );
					firstVisibleAddressIndex = 0;
				  }

				  if ( maxNum > RecordPerPage ) {
					CtlSetLabel( downArrow, BLACK_DOWN_ARROW );
					CtlSetEnabled( downArrow, true );
				  }
                        	  MainFormListAddress(form);             
               			  break;
				 }

            		case DownRepeatButton1006:
				{
				  firstVisibleAddressIndex+=RecordPerPage;
				  if ( (firstVisibleAddressIndex+RecordPerPage) > maxNum ) {
					CtlSetLabel ( downArrow, GRAY_DOWN_ARROW );
					CtlSetEnabled( downArrow, false );
					firstVisibleAddressIndex = maxNum-RecordPerPage;
				  }

				  if ( firstVisibleAddressIndex > 0 ) {
					CtlSetLabel( upArrow, BLACK_UP_ARROW );
					CtlSetEnabled( upArrow, true );
				  }
                       		  MainFormListAddress(form);             
				  break;
				 }
             		 default:
 				  break;
                     
		              	handled=false;         
                }
   
               } 
   
     return    handled;     
}           	              	 
   
//--------------------------------------------------------------------------------------

static   Boolean      EditForm1100HandleEvent(EventPtr  event)
{
	FormPtr         form = FrmGetActiveForm();  
	ControlPtr      trigger,upArrowButton,downArrowButton;  
	Word            command,maxNum, i;
        DirectionType   direction;
	Boolean         handled=false;


	 
	 trigger=FrmGetObjectPtr(form,FrmGetObjectIndex(form,EditCategoryTrigger1101) );
	 downArrowButton=FrmGetObjectPtr(form,FrmGetObjectIndex(form,DownButton1108) );
	
         if(event->eType == frmOpenEvent)
              { 
                (NewButtonSelected)? CreateAddressRecord() : EditFormGetAddressRecord(form) ;
                UpdateCustomField(form);
          		EditFormPageModify(UpButton1107);
               FrmSetFocus(form,noFocus);
                FrmDrawForm(form);
		     
                currentCategory=(currentCategory==dmAllCategories)&&(NewButtonSelected==true)? dmUnfiledCategory : GetRecordCategory(&currentRecIndex);
                CategoryGetName(AddressDb,currentCategory,categoryName);
                CategorySetTriggerLabel(trigger,categoryName);  
                CtlSetLabel(downArrowButton,downArrowOn);
                FrmSetFocus(form,FrmGetObjectIndex(form,FNameField1126));
                handled=true;
              }
               
    else if(event->eType == ctlSelectEvent)
    
              {    
              	   maxNum=DmNumRecordsInCategory(AddressDb,currentCategory);
              	   switch(event->data.ctlSelect.controlID)
              	  {
              	         case   DoneButton1104:   
              	                                  SaveAddressRecord(form);
              	                                  fieldCountStart=0;
              	                                  fieldCountEnd=fieldNumInPage-1;
                                                  if(maxNum > RecordPerPage)
 	      	      		                     firstVisibleAddressIndex++;
 	      	      		                  FrmGotoForm(MainForm1000);   
              	                                  handled=true;
              	                                  break; 
              	                                  
              	         case   CancelButton1105:  
              	                                    
              	                                   if(NewButtonSelected) {
              	                                      DmRemoveRecord(AddressDb,currentRecIndex);
              	                                   }  
              	                                   fieldCountStart=0;
              	                                   fieldCountEnd=fieldNumInPage-1;
              	                                   FrmGotoForm(MainForm1000);
              	                                   handled=true;
              	                                   break;
              	         case   EditCategoryTrigger1101: 
              	                                         EditFormCategorySelect(form);
                                                         handled=true;                       	     	   
    			                                 break;                           
              	                  	 
              	   }
              	   
              	 
              	 
              }
    else if(event->eType == menuEvent)
    
               {
                     command= event-> data.menu.itemID;   
                  if( MenuDoCommand(command) )	
                      handled = true;   	
                        	
               }	    
               
    else if(event->eType == fldHeightChangedEvent)
        
                {           	
                   EditFormChangeFieldHeight(event,form);
                   EditFormUpdate(form);
                   FldSetInsPtPosition(event->data.fldHeightChanged.pField,event->data.fldHeightChanged.currentPos);
                   handled=false;                
                }   

    else if(event->eType == ctlRepeatEvent)
    
               { 
               	        switch(event->data.ctlRepeat.controlID)
               	    {
               	           case    UpButton1107:   
               	                                EditFormPageModify(UpButton1107);
               	                                FrmSetFocus(form,noFocus);
               	                                handled=false;
               	                                break;
               	           case    DownButton1108: 
               	                                EditFormPageModify(DownButton1108);
               	                                FrmSetFocus(form,noFocus);
                                                handled=false;
               	                                break;    
               	    }                               
               }    
               
  
     
     return  handled;     
}           	              	 


//-------------------------------------------------------------------------------------

static  Boolean  AboutForm1300HandleEvent(EventPtr  event)
{
	
	FormPtr    form;	 
        Boolean    handled=false;
    
    	      form=FrmGetActiveForm();	
    	      
    	      if( event->eType == frmOpenEvent)
                  {
                      FrmDrawForm(form);	
                      handled=true; 	 	
                  }  
                  
                    
	 else if( event->eType == ctlSelectEvent)
                    {
       	                 switch(event->data.ctlSelect.controlID)
       	                {
       	                         case  OKButton1301: 
       	                                            
       	                                            FrmGotoForm(EditForm1100);
       	                                            handled=true; 
       	                                            break;
       	                                            
       	                                default:    break;                   	 
       	                }  	            
       	 
                    }	
        	
         
	  
     return  handled;	
    
}


//----------------------------------------------------------------------------------------

static  Boolean    CustomFieldForm1400HandleEvent(EventPtr  event)
{
	FormPtr    form;	 
        Boolean    handled=false;
       
    	      form=FrmGetActiveForm();	
    	      
    	      if( event->eType == frmOpenEvent)
                  {   
                      FrmDrawForm(form);	
                      CustomFieldFormInit(form);
                      handled=true; 	 	
                  }  
                  
                    
	 else if( event->eType == ctlSelectEvent)
                    {
       	                 switch(event->data.ctlSelect.controlID)
       	                {
       	                         case  OKButton1405: 
       	                                            StoreCustomField(form);
       	                                            FrmReturnToForm(EditForm1100);
       	                                            UpdateCustomField(FrmGetFormPtr(EditForm1100));   	                                            
       	                                            handled=true; 
       	                                            break;
       	                                            
       	                         case  CancelButton1406: 
       	                                                 FrmReturnToForm(EditForm1100);
       	                                                 handled=true;
       	                                                 break;
       	                                                 
       	                                                                      
       	                         default:    break;                   	 
       	                }  	            
       	 
                    }	
        	
         
	  
     return  handled;	
    
}
	
		


//-----------------------------------------------------------------------------------	
	
	
static  Boolean  SecretAddressForm1600HandleEvent(EventPtr event)
{
	FormPtr      form;	
	ControlPtr   checkBox;
        Boolean      handled=false;
       
    	      form=FrmGetActiveForm();	
    	      checkBox=FrmGetObjectPtr(form,FrmGetObjectIndex(form,PrivateCheckBox1601));
    	      
    	      if( event->eType == frmOpenEvent)
                  {   
                      SecretAddressFormInit(form,checkBox); 	
                      FrmDrawForm(form);	
                      handled=true; 	 	
                  }  
                  
                    
	 else if( event->eType == ctlSelectEvent)
                    {
       	                 switch(event->data.ctlSelect.controlID)
       	                {
       	                         case  OKButton1602: 
       	                                            SecretAddressFormSetRecordSecret(form,checkBox);
       	                                            FrmReturnToForm(EditForm1100);
       	                                            handled=true; 
       	                                            break;
       	                                            
       	                         case  CancelButton1603: 
       	                                                 FrmReturnToForm(EditForm1100);
       	                                                 handled=true;
       	                                                 break;
       	                                                 
       	                         case  PrivateCheckBox1601:
       	                                                   check=CtlGetValue(checkBox);
 	      	      		                           handled=true;
 	      	      		                           break;   
       	                                                                          
       	                                                                      
       	                         default:    break;                   	 
       	                }  	            
       	 
                    }	
        	
     return  handled;	
    
}
	
	
		

//*********************************************************************************************
  //  This function opens the database(or create a new one if necessary)
         

  Err OpenAddressDatabase(void)  
{ 

    Err       error;
    Word      mode;      
                   
  	   
  	   
  	   mode = dmModeReadWrite; 	
           PrefGetPreferences(&prefs);
           if(!prefs.hideSecretRecords)
              mode |= dmModeShowSecret;	           
                    //Open a database if it exists,or creates a new one         
	error = DmCreateDatabase(0,addressDbName,creatorID,dBType,false);

	if ((error == 0)||(error == dmErrAlreadyExists)) {
		mode = dmModeReadWrite;

      AddressDb=DmOpenDatabaseByTypeCreator(dBType,creatorID,mode);

		if (!AddressDb)
			return (1);
      AddressAppInfoInit(); 	 
	}
/*
           AddressDb=DmOpenDatabaseByTypeCreator(dBType,creatorID,mode);   
   	   if(!AddressDb)            
   	{   
           if( DmCreateDatabase(0,addressDbName,creatorID,dBType,false) !=  0 )    
                  return   -1;//error=DmGetLastErr();	
          
           AddressDb=DmOpenDatabaseByTypeCreator(dBType,creatorID,mode);
   	   if(!AddressDb)
               return   -1;//error=DmGetLastErr();    
                   
            //Initialize appInfo-block
           AddressAppInfoInit(); 	 
   	 }  
*/   	 
   	       
   	  
   	 
            
      return 0;
}

//------------------------------------------------------------------------------- 
  //This routine initialize the AppInfo Block of a database 
    // if the block doesn't exist ,create a new one.
    
  Err  AddressAppInfoInit(void)
 {
 	  LocalID   dbID;
 	  LocalID   appInfoID;
 	  VoidHand  appInfoH;
 	  Word	    i;   	
	  Char	    *name[4] = { "Unfiled", "Business", "Personal", "" };
 	  
 	  
 	  
 	      //retrieve appInfoID
 	  
 	if ( DmOpenDatabaseInfo(AddressDb ,&dbID ,NULL ,NULL ,&cardNum ,NULL) )
 	     return dmErrInvalidParam ;
 	if ( DmDatabaseInfo(cardNum , dbID , NULL,NULL,NULL,NULL,NULL,NULL,NULL,&appInfoID,NULL,NULL,NULL) )
 	     return dmErrInvalidParam ;
 	      
               // create a new appInfo block if necessary
             
         if ( appInfoID == 0 )
              {    
                   appInfoH = DmNewHandle( AddressDb, sizeof(AppInfoType));
                   appInfoID =MemHandleToLocalID(appInfoH);      
                   DmSetDatabaseInfo(cardNum,dbID,NULL,NULL,NULL,NULL,NULL,NULL,NULL, &appInfoID,NULL,NULL,NULL);
              } 
         appInfoP = MemLocalIDToLockedPtr(appInfoID , cardNum);                                     
         DmSet(appInfoP , 0 , sizeof(AppInfoType) , 0);       // clear appInfo block
         CategoryInitialize( (AppInfoPtr) appInfoP ,MainFormCategoryList1002);

	 for ( i = 0; i < 3; i++ ) {
		CategorySetName (AddressDb, i, name[i]);
	 }

	 for ( i = 3; i < 16; i++ ) {
		CategorySetName (AddressDb, i, name[3]);
	 }

         MemPtrUnlock(appInfoP);
         return 0;
  
 
 }



//--------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
//******************************************************************************************* 



   
       

//----------------------------------------------------------------------------------
 
  void    SetFieldAttribute(FieldPtr field)
 {       
 	 FieldAttrType      attribute;
 	  
  	    
  	   FldGetAttributes(field,&attribute);
  	   attribute.singleLine=false;
  	   attribute.dynamicSize=true;
  	   FldSetAttributes(field,&attribute); 
  	   
 }
 
  	  
  	  
//*******************************************************************************************

 static     Boolean    CreateAddressRecord(void)
{
      VoidHand    addressH;
      VoidPtr     addressP;  
      Word        index;	 
      DWord       offset=0;
      Word        category;
     
                      
 
      index    = DmNumRecords(AddressDb);        
      addressH = DmNewRecord(AddressDb,&index,newRecordSize);  
      ErrFatalDisplayIf( (!addressH),"New Record Failed");
      addressP=MemHandleLock(addressH);                   // Lock the handle
      DmSet( addressP , offset , newRecordSize , 0);       //clear the record
      MemHandleUnlock(addressH); 
      currentRecIndex =index;
      
      category = currentCategory;
      SetRecordCategory(&category);    //set the category of the record
   
      DmReleaseRecord(AddressDb,index,true);       //clear the busy bit for the record 
                                 		  //and set its dirty bit
     return(true);
        
}  	

//--------------------------------------------------------------------------------------
  // this routine sets the record  category.
 
  
  static  void  SetRecordCategory(Word* category)   
{       
  
   	Word        attribute; 
   	Word        index=currentRecIndex;
   
         DmRecordInfo(AddressDb , index ,&attribute ,NULL,NULL);    //retrieve the attribute of record
         attribute &= ~dmRecAttrCategoryMask;                // clear it 
         if( *category == dmAllCategories)
                    attribute |= dmUnfiledCategory ;
         else       attribute |= *category;
         DmSetRecordInfo(AddressDb , index , &attribute , NULL);   //set attribute  of record
              
 } 

//---------------------------------------------------------------------------------------

static    Word   GetRecordCategory(Word  *index)
{   
	Word  category;
        Word  attribute;
	
    DmRecordInfo(AddressDb,*index,&attribute,NULL,NULL);
    category=attribute&dmRecAttrCategoryMask;
    return(category); 	 
}


//--------------------------------------------------------------------------------------------
static   Boolean    SaveAddressRecord(FormPtr form)

{ 
     VoidHand         addressH;
     CharPtr          addressP;
     FieldPtr         field;
     char *           textP;
     Word             i;
     DWord            offset=0,tempSize=0,fieldTextSize=0;
     char             null=0;
       
             	
      for( i=0 ; i < NumOfItems ; i++)
    {   
    	field = FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+i));
    	textP = FldGetTextPtr(field);
    	FldReleaseFocus(field);    
//        FldCompactText(field);
         if(textP==NULL)
            tempSize=1;
        else 
            tempSize=StrLen(textP)+1;
        fieldTextSize += tempSize;   
        addressH=DmResizeRecord(AddressDb,currentRecIndex,fieldTextSize);
        addressP=MemHandleLock(addressH);
        if(textP==NULL) {    
           DmWrite((void*) addressP,offset,&null,1);
           offset++; 
        }  
        else{
           DmStrCopy((void*) addressP,offset,(void*) textP);
           offset += StrLen(textP)+1;
        } 
      MemHandleUnlock(addressH);
   } 
     currentRecordSaved=true; 
     return true;
}



//--------------------------------------------------------------------------------------------
#define        copyString      "(Copy)"
#define        copyStringSize     7

static  void   DuplicateAddressRecord(FormPtr  form)

{       VoidHand    oldAddressH,newAddressH;
        CharPtr     oldAddressP,newAddressP;
        DWord       offset=0;
        char*       bufferP;
        Word        oldRecIndex=currentRecIndex;
        

	       CreateAddressRecord();
	       oldAddressH=DmQueryRecord(AddressDb,oldRecIndex);
	       oldAddressP=MemHandleLock(oldAddressH);
	       newAddressH=DmResizeRecord(AddressDb,currentRecIndex,MemPtrSize(oldAddressP)+copyStringSize);
	       newAddressP=MemHandleLock(newAddressH);     
	       DmWrite(newAddressP,offset,oldAddressP,MemPtrSize(oldAddressP));
	       bufferP=StrChr(oldAddressP,nullChr);    
	       DmWrite(newAddressP,(DWord)(bufferP-oldAddressP)+copyStringSize,bufferP+1,MemPtrSize(oldAddressP)-StrLen(oldAddressP)-1);
	       DmStrCopy(newAddressP,(DWord)(bufferP-oldAddressP),copyString);    
	       MemHandleUnlock(oldAddressH);
	       MemHandleUnlock(newAddressH);
	       DmReleaseRecord(AddressDb,currentRecIndex,true);
	           
	       if(currentRecIndex!=oldRecIndex+1)  {
	       	  DmMoveRecord(AddressDb,currentRecIndex,oldRecIndex+1);
	       	  currentRecIndex=oldRecIndex+1;
	       }	  
	     
}               	
 



//**********************MainForm*******************************************************************

 	  
      



//----------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------

static  void     MainFormCategorySelect(FormPtr  form)    

{ 
    
    Word       category;
    Boolean    selected;	
	 
	  category=currentCategory;
	  selected= CategorySelect(AddressDb,form,MainFormCategoryTrigger1001,MainFormCategoryList1002,true,&category,categoryName,
	                                 1,categoryDefaultEditCategoryString);  
	 
          if(selected || (category != currentCategory))  {
              FrmEraseForm(form);
	      FrmDrawForm(form);  
              currentCategory=category; 
              firstVisibleAddressIndex=0;   
              if(VisibleRecordList) {
	         MemPtrFree(VisibleRecordList);
                 VisibleRecordList=NULL; 
              } 
              AddressNumsDisplay();	
              RptBtnInit(form);
              MainFormListAddress(form);
          }   	
    
           
}	

//-----------------------------------------------------------------







//******************************EditForm*********************************************************

//static  void       EditFormInit(FormPtr form)

	 
	
	
	
//--------------------------------------------------------------------------------------

 static   void      EditFormGetAddressRecord(FormPtr  form)
{
	VoidHand         addressH,textH;
	CharPtr          addressP,textP; 
	VoidHand         bufferH;
	CharPtr            bufferP;	
	FieldPtr         field,topField;
	CharPtr          tempP;
	Word             i, size=0,recordSize;
	DWord            offset=0;
	char             string[3];
	Word             count=0,lineHeight,totalFieldHeight=0;
	//Boolean          test;
	     
	addressH=DmGetRecord(AddressDb,currentRecIndex);     
	addressP=MemHandleLock(addressH);      
	tempP=addressP;
	size=(Word)(StrChr(addressP,nullChr)-addressP); 
	for (i=0 ; i < NumOfItems ;i++) {
		field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+i));
		if(size) 
			FldInsert(field,tempP, size );  
		tempP=StrChr(tempP,nullChr);      
		tempP++;			
		StrStr(addressP,tempP);    
		size=StrLen(tempP);
	}
	
	MemHandleUnlock(addressH);
	DmReleaseRecord(AddressDb,currentRecIndex,true);

	i=0;
	fieldCountStart=0;
	lineHeight=FntLineHeight();
	while(totalFieldHeight <  FieldBottomPosition-FieldTopPosition) {  
		topField=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+fieldCountStart+i));
		//lineHeight=FldGetTextHeight(field);
		totalFieldHeight+=FldCalcFieldHeight (FldGetTextPtr (topField), FieldWidth)*lineHeight;  
		if((totalFieldHeight > FieldBottomPosition-FieldTopPosition)||(fieldCountStart+(++i) >= totalFieldNum))
		break;
	}   

	fieldCountEnd=fieldCountStart+i-1;   
}	   
	   	  
	     
//----------------------------------------------------

 static    void    EditFormChangeFieldHeight(EventPtr event,FormPtr form)
{       
        FieldPtr         field;  	
	RectangleType    rect,eraseRect;
	Word             fieldWidth,fieldIndex,fieldId;
	Word             count=0,totalFieldHeight=0,newHeight, lineHeight;
	SWord		 i,j=0;
	char*            textP;
	char             string[3];
	ControlPtr       upArrowButton,downArrowButton;
	FieldAttrType    attri;
	
	
        RctSetRectangle (&eraseRect, 0, 15, 160, 125);
	WinEraseRectangle (&eraseRect, 0);
        upArrowButton = FrmGetObjectPtr(form,FrmGetObjectIndex(form,UpButton1107) ); 
        downArrowButton=FrmGetObjectPtr(form,FrmGetObjectIndex(form,DownButton1108) );
        
	fieldId=event->data.fldHeightChanged.fieldID;
	FrmHideObject (form,FrmGetObjectIndex(form,fieldId));
	newHeight=event->data.fldHeightChanged.newHeight;     //ErrFatalDisplayIf(true,StrIToA(string,newHeight));
	FrmGetObjectBounds(form,FrmGetObjectIndex(form,fieldId),&rect);
	rect.extent.y=newHeight;                
	FrmSetObjectBounds(form,FrmGetObjectIndex(form,fieldId),&rect);
	lineHeight = FntLineHeight();
	fieldCount=fieldId-FNameField1126;   

	if(fieldCount==fieldCountEnd)   {    
           for( i = fieldCountEnd; i >= fieldCountStart; i-- ) {
                field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+i));
                FrmGetObjectBounds(form,FrmGetObjectIndex(form,FNameField1126+i),&rect);
                totalFieldHeight+=rect.extent.y;      
           } 
              if(totalFieldHeight > FieldBottomPosition-FieldTopPosition)  {
                  if ( (rect.extent.y > lineHeight) && (fieldCountEnd != totalFieldNum-1) ) {
                        fieldCountEnd++;
                  }
                  else {  
                        fieldCountStart++;
                  }
                  if(fieldCountStart > fieldCountEnd)
                  fieldCountStart=fieldCountEnd;
              }
              else if(totalFieldHeight < FieldBottomPosition-FieldTopPosition)
              {  
                   if (fieldCountEnd == totalFieldNum-1) {
         	       FrmGetObjectBounds(form,FrmGetObjectIndex(form,FNameField1126+fieldCountStart-1),&rect);
	               if ( rect.extent.y <= FieldBottomPosition-FieldTopPosition-totalFieldHeight )
	               fieldCountStart--;                  
                   }
                   else {
               	     fieldCountEnd++;
               	   }
              }

               if(fieldCountEnd >= totalFieldNum)
                    fieldCountEnd = totalFieldNum-1;
               if(fieldCountEnd==totalFieldNum-1) {
                  CtlSetEnabled(downArrowButton,false);
                  CtlSetLabel(downArrowButton,downArrowOff);	
               } 	  
               if(fieldCountStart < 0)
                  fieldCountStart=0;
	       if(fieldCountStart > 0) {	
                  CtlSetEnabled(upArrowButton,true);
                  CtlSetLabel(upArrowButton,upArrowOn);
               }
           //ErrFatalDisplayIf(true,StrIToA(string,fieldCountStart)); 
           //ErrFatalDisplayIf(true,StrIToA(string,fieldCountEnd));  
        }
        else { 
               i=0;
               while(totalFieldHeight < FieldBottomPosition-FieldTopPosition)  {
                     FrmGetObjectBounds(form,FrmGetObjectIndex(form,FNameField1126+fieldCountStart+(i++)),&rect);
                     totalFieldHeight+=rect.extent.y;  
                     if((fieldCountStart+i >= totalFieldNum)||(totalFieldHeight > FieldBottomPosition-FieldTopPosition))
                     break;
               }
               fieldCountEnd=fieldCountStart+i-1;    //ErrFatalDisplayIf(true,StrIToA(string,i));
               if(fieldCountEnd < totalFieldNum-1) {
                  CtlSetLabel( downArrowButton, downArrowOn );
                  CtlSetEnabled( downArrowButton, true );  
               }	
               else {
                     CtlSetLabel( downArrowButton, downArrowOff );
                     CtlSetEnabled( downArrowButton, false );  
               }	  
        }
           
	EditFormResetObjectPosition(form);
	
}
//---------------------------------------------------------------------------------------
static     void   EditFormResetObjectPosition(FormPtr  form)
{       
     	   RectangleType    fieldRect,eraseRect;
	   FieldPtr         field;
	   char*            textP;
	   Word             offset=0;
	   Word             fieldHeight=0,lineHeight;
	   SWord            i; 
	 

	 lineHeight=FntLineHeight();
	 for(i=fieldCountStart ; i <= fieldCountEnd ;i++)
         { 
             if(i < totalFieldNum)  {
  	         field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+i));
        	 textP=FldGetTextPtr(field);
           	 fieldHeight=FldCalcFieldHeight(textP,FieldWidth)*lineHeight;
	   	 FrmGetObjectBounds(form,FrmGetObjectIndex(form,FNameField1126+i),&fieldRect);	
           	 fieldRect.topLeft.y = TopFieldTopPosition+offset;   

                 if( (fieldRect.topLeft.y+fieldHeight) > FieldBottomPosition )
                      fieldRect.extent.y = FieldBottomPosition-fieldRect.topLeft.y ;   
                 else
	              fieldRect.extent.y = fieldHeight;
	   
           	 FrmSetObjectBounds(form,FrmGetObjectIndex(form,FNameField1126+i),&fieldRect);
                 FrmSetObjectPosition(form,FrmGetObjectIndex(form,FName1110+i),TopLabelLeftPosition,TopLabelTopPosition+offset);
                 offset += fieldRect.extent.y;
	     }   
	 }   
}

//----------------------------------------------------------------------------------------


static  void     EditFormUpdate(FormPtr  form)
{
	 SWord             i=0; 	
 	
  	
   	 for(i=0 ;i < fieldCountStart ;i++)
  	 {  
   	     FrmHideObject(form,FrmGetObjectIndex(form,FName1110+i));
   	     FrmHideObject(form,FrmGetObjectIndex(form,FNameField1126+i));
  	 }
  	 
   	 for(i=fieldCountEnd+1 ;i < totalFieldNum ;i++)
  	 {  
   	     FrmHideObject(form,FrmGetObjectIndex(form,FName1110+i));
   	     FrmHideObject(form,FrmGetObjectIndex(form,FNameField1126+i));
  	 }
     
  	for(i=fieldCountStart ;i <= fieldCountEnd ;i++)
  	   {   
  	   	FrmShowObject(form,FrmGetObjectIndex(form,FName1110+i));
  	   	FrmShowObject(form,FrmGetObjectIndex(form,FNameField1126+i));
	   }
  	 
}

//----------------------------------------------------------------------------------------
 
                      
static  void    EditFormPageModify(Word id)
{
        FormPtr       form=FrmGetActiveForm();
        FieldPtr      field;
        SWord         i=0,j=0;
        Word          totalFieldHeight=0,lineHeight;
        ControlPtr    upArrowButton,downArrowButton;
        RectangleType rect,eraseRect;
  
  	RctSetRectangle (&eraseRect, 0, 15, 160, 125);
	WinEraseRectangle (&eraseRect,0);
        upArrowButton = FrmGetObjectPtr(form,FrmGetObjectIndex(form,UpButton1107) ); 
        downArrowButton=FrmGetObjectPtr(form,FrmGetObjectIndex(form,DownButton1108) );
        lineHeight=FntLineHeight();
        if(id==UpButton1107)  { 
               if(fieldCountStart==fieldCountEnd)     
                  fieldCountEnd--;   	
               else  fieldCountEnd=fieldCountStart;
               while(totalFieldHeight < FieldBottomPosition-FieldTopPosition)  {
               	     field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+fieldCountEnd-i));
                     totalFieldHeight += FldCalcFieldHeight(FldGetTextPtr(field),FieldWidth)*lineHeight;
                     if((fieldCountEnd-(++i) < 0)||(totalFieldHeight > FieldBottomPosition-FieldTopPosition))
                        break;
               }     
               fieldCountStart=fieldCountEnd-(i-1);    
    
               if(totalFieldHeight < FieldBottomPosition-FieldTopPosition)  { 
               	   while(totalFieldHeight <  FieldBottomPosition-FieldTopPosition) {
                       //FrmGetObjectBounds(form,FrmGetObjectIndex(form,FNameField1126+fieldCountStart+(i++)),&rect);
                       //totalFieldHeight+=rect.extent.y;  
                       field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+fieldCountStart+(i++)));
                       totalFieldHeight+=FldCalcFieldHeight(FldGetTextPtr (field), FieldWidth)*lineHeight;
                       if((totalFieldHeight > FieldBottomPosition-FieldTopPosition))
                           break;
                   }
                       fieldCountEnd=fieldCountStart+i-1;    
                       CtlSetEnabled(upArrowButton,false);  
                       CtlSetLabel(upArrowButton,upArrowOff);
               }  
               else if(totalFieldHeight > FieldBottomPosition-FieldTopPosition) {  
                    totalFieldHeight=0;
                    while(totalFieldHeight <  FieldBottomPosition-FieldTopPosition) {
                         field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+fieldCountStart+(j++)));
                         totalFieldHeight+=FldCalcFieldHeight(FldGetTextPtr (field), FieldWidth)*lineHeight;
                         if((totalFieldHeight > FieldBottomPosition-FieldTopPosition))
                             break;
                    }
                    fieldCountEnd=fieldCountStart+j-1;
               } 	 
	       if(fieldCountEnd != totalFieldNum-1) {
                   CtlSetLabel(downArrowButton,downArrowOn);
		   CtlSetEnabled(downArrowButton,true );  
               }
               if(fieldCountStart > 0)  {   	
                    CtlSetEnabled(upArrowButton,true);
                    CtlSetLabel(upArrowButton,upArrowOn); 
               } 
                else{
                     CtlSetEnabled(upArrowButton,false);
                     CtlSetLabel(upArrowButton,upArrowOff);
                }     
        }  
                      
                 
  else  if(id==DownButton1108)  {  
              if(fieldCountEnd==fieldCountStart)     
                 fieldCountStart++;   
              else { 
        	    fieldCountStart=fieldCountEnd;
              }
              while(totalFieldHeight <  FieldBottomPosition-FieldTopPosition)  {  
                      field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+fieldCountStart+i));
                      totalFieldHeight+=FldCalcFieldHeight (FldGetTextPtr (field), FieldWidth)*lineHeight;
                      if((fieldCountStart+(++i) >= totalFieldNum)||(totalFieldHeight > FieldBottomPosition-FieldTopPosition))
                      break;
              }           
              fieldCountEnd=fieldCountStart+i-1;   //ErrFatalDisplayIf(true,StrIToA(String,fieldCountEnd));
              CtlSetEnabled(downArrowButton,true);
              CtlSetLabel(downArrowButton,downArrowOn);

              
              if(totalFieldHeight <  FieldBottomPosition-FieldTopPosition)  { 
                    i=0;         
                    while(totalFieldHeight <  FieldBottomPosition-FieldTopPosition)  {
                          field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+fieldCountStart-1-i));
                          totalFieldHeight+=FldCalcFieldHeight (FldGetTextPtr (field), FieldWidth)*lineHeight;
                          if(totalFieldHeight > FieldBottomPosition-FieldTopPosition)
                             break;
                          i++;
                    }    
                    fieldCountStart -= i;  //ErrFatalDisplayIf(true,StrIToA(string,i));  	   	
                    fieldCountEnd=totalFieldNum-1;
                    CtlSetEnabled(downArrowButton,false);
                    CtlSetLabel(downArrowButton,downArrowOff);
              }
                   
                  if(fieldCountStart > 0)   {
                     CtlSetEnabled(upArrowButton,true);  
                     CtlSetLabel(upArrowButton,upArrowOn);	
                  }
                  if(fieldCountEnd < totalFieldNum-1)  {
                     CtlSetLabel(downArrowButton,downArrowOn);
		     CtlSetEnabled(downArrowButton,true );  
                  }
                  else{
                        field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+totalFieldNum-1));
                        totalFieldHeight=FldCalcFieldHeight(FldGetTextPtr (field), FieldWidth)*lineHeight;
                        FrmGetObjectBounds(form,FrmGetObjectIndex(form,FNameField1126+totalFieldNum-1),&rect); 
                        if(rect.extent.y == totalFieldHeight) {   	
                           CtlSetLabel(downArrowButton,downArrowOff);
		           CtlSetEnabled(downArrowButton,false);  
		        } 
		  } 	
  }
  	
   EditFormResetObjectPosition(form); 
   EditFormUpdate(form);   

}	   
//-----------------------------------------------------
/*
static   void   EditFormDrawLabel(void) 	  
{ 	   
        FormPtr        form=FrmGetActiveForm();
        FieldPtr       field;
        Word           i;
        RectangleType  labelRect,fieldRect,eraseRect;
        
        
         RctSetRectangle (&eraseRect, 0, 15, 160, 128);
	 WinEraseRectangle (&eraseRect, 0);
	 
         for(i=fieldCount ; i <= fieldCountEnd ;i++)
         {    
          field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+i));	   
          FldSetUsable (field, true);	
          FrmGetObjectBounds(form,FrmGetObjectIndex(form,FName1110+i),&labelRect);
	  FrmGetObjectBounds(form,FrmGetObjectIndex(form,FNameField1126+i),&fieldRect);
	  labelRect.topLeft.y += fieldRect.extent.y;
          fieldRect.topLeft.y += fieldRect.extent.y;   	
          FrmSetObjectPosition(form,FrmGetObjectIndex(form,FName1110+i),labelRect.topLeft.x,labelRect.topLeft.y);	
          FrmSetObjectPosition(form,FrmGetObjectIndex(form,FNameField1126+i), fieldRect.topLeft.x,fieldRect.topLeft.y);
         	 
	 }                    	
 	
	

}	
	
*/
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------


static  void     EditFormCategorySelect(FormPtr  form)
{      
       
        Word     index;	
       	Word     attribute,category;
       	Boolean  selected;
	  
	 
	  index=currentRecIndex;
	  DmRecordInfo(AddressDb,index,&attribute,NULL,NULL);
	  category = attribute&dmRecAttrCategoryMask;       
            
          selected=CategorySelect(AddressDb,form,EditCategoryTrigger1101,EditCategoryList1102,false,&category,  
                                    categoryName,1,categoryDefaultEditCategoryString);
          if(selected || (category !=attribute&dmRecAttrCategoryMask))  {
             SetRecordCategory(&category); 
             currentCategory=category; 	
             firstVisibleAddressIndex=0; 
          }
           
}        	                             
        
//*****************************************************************************************

static   Boolean   MenuDoCommand(Word command)	
 { 
 	FormPtr    form = FrmGetActiveForm() ; 
 	FieldPtr   fieldFocusP, field;        
 	Word       fieldIndex,index,i; 
        Word       maxNum;
 	Word       textLength;
 	Boolean    handled=false;
       	
         
        
         fieldIndex = FrmGetFocus(form);                       
         if (fieldIndex != noFocus )
             fieldFocusP = FrmGetObjectPtr(form , fieldIndex);
         maxNum=DmNumRecordsInCategory(AddressDb,currentCategory);  
         
        switch( command )
     {  
         case    NewItem2001:                            // To create a new record
                               SaveAddressRecord(form);
                               if(maxNum > RecordPerPage)
 	      	      		  firstVisibleAddressIndex++; 
                               CreateAddressRecord();
                               for(i=0;i < NumOfItems ;i++)
                               {
                               	field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FNameField1126+i));
                                FldFreeMemory(field);
                                FldDrawField (field);
                               }  
                                FrmSetFocus (form, FrmGetObjectIndex(form,FNameField1126) );      
                                handled=true;
                                break; 
         case    DeleteItem2002:                         // To delete a record
                                   if(MenuBarDeleteRecord(form)) {
                                      firstVisibleAddressIndex--;
                                      if(firstVisibleAddressIndex < 0)
                                         firstVisibleAddressIndex=0;  	
	    			   }	
                                   FrmGotoForm(MainForm1000); 
                                   handled=true;
                                   break;
                        
         case    UndoItem2003:                     
                               FldUndo (fieldFocusP);
                               handled=true;
                               break;
          
         case    CutItem2004 : 
                               FldCut ( fieldFocusP );
                               handled=true;  
         		       break;	 
         
         case    CopyItem2005: 
         			FldCopy (fieldFocusP);
                                handled=true;
                                break;       
         case    PasteItem2006:
                                 FldPaste (fieldFocusP ); 
                                 handled=true;
                                 break;
                                 
         case    SelectAllItem2007:
                                    textLength=FldGetTextLength(fieldFocusP);
   				    FldSetSelection (fieldFocusP, textStartPosition ,textStartPosition + textLength);	   
           		  	    handled=true;			  
                                    break;
          
          
          
        
     	  
         case    KeyboardItem2008:  
                                    SysKeyboardDialog(kbdDefault);
                                    handled=true;
                                    break;
       
         case    Graffiti2009:   
//                                    SysGraffitiReferenceDialog(referenceDefault);
                                    handled=true;
                                    break;   
                                    
         case    DuplicateItem2012:  
                                     SaveAddressRecord(form);
                                     if(maxNum > RecordPerPage)
 	      	      		        firstVisibleAddressIndex++; 
                                     DuplicateAddressRecord(form);
                                     EditFormGetAddressRecord(form);
                                     FrmSetFocus(form,FrmGetObjectIndex(form,FNameField1126));
                                     handled=true;
                                     break;                        
                                    
         case    AboutItem2011:      NewButtonSelected=false;
                                     SaveAddressRecord(form);
                                     FrmGotoForm(AboutForm1300); 
                                     handled=true;                  
             	                     break;                             
         case    CustomField2013:   
                                    FrmPopupForm(CustomFieldForm1400); 
                                    handled=true;
                                    break;      
                                    
         case    SecretItem2014:  
                                    FrmPopupForm(SecretAddressForm1600); 
                                    handled=true;
                                    break;                                              
     }      
          
      return(handled);    
}


//*********************************************************************************************

static    Boolean    MenuBarDeleteRecord(FormPtr  form)
{
    
     Word       hitButton; 
     
     
    
    
                 hitButton= FrmCustomAlert( MenuBarDeleteAlert3000 ,"OK","CANCEL",NULL);
                                                                
                 if ( hitButton == alert_Cancel_Button )
                      return(false);                     
                else  
                     DmRemoveRecord (AddressDb, currentRecIndex);   
                  	     
                	  
        	     return(true);        
      
}              
                          

//*****************************Custom Field Form***********************************************


 
 static  void   CustomFieldFormInit(FormPtr  form)
{
/*
	 FieldPtr   field;
	 Word       i;
	 LocalID    NoteAppInfoID;
	 DWord      offset=0;   
	 
	 NoteAppInfoID= DmGetAppInfoID(NoteDb);
	 NoteAppInfoP = MemLocalIDToLockedPtr( NoteAppInfoID, cardNum);
	
	 for(i=0 ; i < CustomFieldNum ;i++)
	{
	    field = FrmGetObjectPtr(form,FrmGetObjectIndex(form,Custom1Field1401+i));	
	    FldInsert(field,NoteAppInfoP+offset,StrLen(NoteAppInfoP+offset));
	    offset += ItemLength;
	    FldReleaseFocus(field);	 
	}   
*/	
}


//-------------------------------------------------------------------------------------------

static   void    StoreCustomField(FormPtr  form)	
{
/*	 
	 FieldPtr     field;
	 char*        textP;  
	 Word         i;
	 DWord        offset=0;       
	 
	 
	 for(i=0 ; i < CustomFieldNum ; i++)
        {
             field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,Custom1Field1401+i));
             textP=FldGetTextPtr(field);
                  if(textP!=NULL)
                 {   		 
	             DmStrCopy(NoteAppInfoP,offset,textP);
	         }
	         else {
	         	DmSet(NoteAppInfoP,offset,sizeof(char),0);
	              }
	      offset+=ItemLength;    
	 }
*/	
}











//------------------------------------------------------------------------------------------

static   void   UpdateCustomField(FormPtr  form)
{

/*
	 LocalID          NoteAppInfoID;
	 DWord            offset=0; 
	 Word             i;  
	    
	    NoteAppInfoID= DmGetAppInfoID(NoteDb);
	    NoteAppInfoP = MemLocalIDToLockedPtr( NoteAppInfoID, cardNum); 
	   
	    for(i=0;i < CustomFieldNum ;i++) 
	   {  
             //FrmHideObject(form,FrmGetObjectIndex(form,Custom1_1122+i));
             FrmCopyLabel(form,Custom1_1122+i,(CharPtr)NoteAppInfoP+offset);
             offset+=ItemLength;    
             //ErrFatalDisplayIf(true,StrIToA(String,state));
	   }
	    MemPtrUnlock( NoteAppInfoP );
*/	    
}	    





//***********************************SecretAddressForm****************************************

static   void    SecretAddressFormInit(FormPtr form,ControlPtr  checkBox)
{
	 Word    attribute;
	
	
	 DmRecordInfo(AddressDb,currentRecIndex,&attribute,NULL,NULL);
	 attribute &= 0x10;
     	 if(attribute) 
     	    CtlSetValue(checkBox,true);
	
}	
	
	
//---------------------------------------------------------------------------------
static    void   SecretAddressFormSetRecordSecret(FormPtr form,ControlPtr  checkBox)

{       
        Word        attribute; 
   
         
         DmRecordInfo(AddressDb,currentRecIndex,&attribute,NULL,NULL);    
         if(CtlGetValue(checkBox))  
         {
          attribute |= dmRecAttrSecret;             
          DmSetRecordInfo(AddressDb , currentRecIndex , &attribute , NULL);  
         }    
         else
         {
          attribute &= 0xef;          //cancel the secret property of the record     
          DmSetRecordInfo(AddressDb,currentRecIndex , &attribute , NULL);  	    
         }
}             





//********************************************************************************************//

void    AddressNumsDisplay()
{
	Word     recNum=DmNumRecordsInCategory(AddressDb,currentCategory);
	char     totalRecIndex[4];
	Word     totalRecIndexLength=0;
	
	StrIToA(totalRecIndex,recNum);
	while (recNum) {
		recNum /= 10;
		totalRecIndexLength++;
	}
	totalRecIndex[totalRecIndexLength]=0;
	
	if(totalRecIndex[0]!=0) 
	WinDrawChars(totalRecIndex,StrLen(totalRecIndex),Address_Index_Start+60,1);
	else 
	WinDrawChars("0",1,Address_Index_Start+60,1);
	WinDrawChars("Items",5,Address_Index_Start+75,1);

}
   
   
void   RptBtnInit(FormPtr  form)
{
	
	ControlPtr	upArrow;
	ControlPtr	downArrow;
	Word            recNum;

	upArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,UpRepeatButton1005));
	downArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,DownRepeatButton1006));
	recNum = DmNumRecordsInCategory (AddressDb,currentCategory);
        
        if(recNum <=  RecordPerPage)  {
             CtlHideControl(upArrow);
             CtlHideControl(downArrow);
             return;
        }
        else  {
        	 CtlShowControl(upArrow);
                 CtlShowControl(downArrow);
        }     	
	if ( firstVisibleAddressIndex <= 0 ) {
	     CtlSetLabel( upArrow, GRAY_UP_ARROW ); 
	     CtlSetEnabled( upArrow, false );
	} else {
		CtlSetLabel( upArrow, BLACK_UP_ARROW );
		CtlSetEnabled( upArrow, true );
	  }
	if ( recNum > RecordPerPage ) {
	     CtlSetLabel( downArrow, BLACK_DOWN_ARROW );
	     CtlSetEnabled( downArrow, true );
	} else {
		CtlSetLabel( downArrow, GRAY_DOWN_ARROW );
		CtlSetEnabled( downArrow, false );
	}
	if(firstVisibleAddressIndex+RecordPerPage >= recNum) {
		CtlSetLabel( downArrow, GRAY_DOWN_ARROW );
		CtlSetEnabled( downArrow, false );
        }		
	
}	
	


   void  MainFormListAddress(FormPtr  form)       
{   
   
	VoidHand	recordH;
	CharPtr		recordP;	
	Word		indexStart=0,count=0; 
	Char		numBuffer[4];
        CharPtr         firstNameP,lastNameP; 
	Word		bufLength, numLength, tcount;	
	Word            firstNameMaxLength,lastNameMaxLength;
	RectangleType	eraseRect;
	
	
	RctSetRectangle (&eraseRect, 0, 15, 160, 121);
	WinEraseRectangle (&eraseRect, 0);
	
	recNumInCategory=DmNumRecordsInCategory(AddressDb,currentCategory);
	if(recNumInCategory)
	VisibleRecordList=MemPtrNew(recNumInCategory*sizeof(Word)) ;
	while (!DmSeekRecordInCategory (AddressDb, &indexStart, 0, dmSeekForward, currentCategory)) {
		recordH = DmQueryRecord (AddressDb, indexStart+firstVisibleAddressIndex);
		if(VisibleRecordList)
		*(VisibleRecordList+count+firstVisibleAddressIndex)=indexStart+firstVisibleAddressIndex;
		if (recordH) {
			tcount = firstVisibleAddressIndex+count+1;
			StrIToA (numBuffer, tcount);
			numLength = 0;
			while (tcount) {
				tcount = tcount/10;
				numLength++;
			}
			tcount =  firstVisibleAddressIndex+count+1;
			recordP = MemHandleLock(recordH);
			if ( !recordP ) {
				indexStart++;
				MemHandleUnlock (recordH);
				continue;
			}
		        firstNameP=MemPtrNew(StrLen(recordP)+1);
		        if(firstNameP) {    
             		   MemSet(firstNameP,StrLen(recordP)+1,0);
             		   MemMove((void*)firstNameP,recordP,StrLen(recordP)+1);
             		}
			recordP += (StrLen(recordP)+1);
		        lastNameP=MemPtrNew(StrLen(recordP)+1);
		        if(lastNameP) {
             		   MemSet(lastNameP,StrLen(recordP)+1,0);
             		   MemMove((void*)lastNameP,recordP,StrLen(recordP)+1);
             		}
			
			numBuffer[numLength+1] = 0;
			numBuffer[numLength] = '.';
				if ( tcount < 10 ) {
					WinDrawChars (numBuffer, StrLen(numBuffer), FNameX+5, count*RecordHeight+15);
				} else {
					WinDrawChars (numBuffer, StrLen(numBuffer), FNameX, count*RecordHeight+15);
				}
				if(firstNameP)  {
			 	   firstNameMaxLength=Min( FntWordWrap(firstNameP,FirstNameMaxWidth),(Word)(StrChr(firstNameP,linefeedChr)-firstNameP));
			 	   WinDrawChars (firstNameP, firstNameMaxLength, FNameX+15, count*RecordHeight+15);
			 	}   
				if(lastNameP)  {
			 	   lastNameMaxLength=Min( FntWordWrap(lastNameP,FirstNameMaxWidth),(Word)(StrChr(lastNameP,linefeedChr)-lastNameP));
			 	   WinDrawChars (lastNameP, lastNameMaxLength, FNameX+15+FirstNameMaxWidth, count*RecordHeight+15);
			 	}   
			 	if((firstNameP[0]==0) && (lastNameP[0]==0))  { 
			 	   WinDrawChars ("Unknown   People", 16, FNameX+15, count*RecordHeight+15);
			 	}
			 		
				count++;
		        
			MemHandleUnlock(recordH);
			MemPtrFree(firstNameP);
			MemPtrFree(lastNameP);
			if ( count >= RecordPerPage )
			     break;
		}
		indexStart++;
	}

	     	  
  	 
}


/***********************************************************************
 *
 * FUNCTION:    AddressViewHandlePen
 *
 * DESCRIPTION: Handle pen movement in the AddressViewDisplay. 
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
static Boolean AddressViewHandlePen (EventType * event)
{
	Boolean        handled = false;
	RectangleType  r,invertRec;
	Word           x, y;
	Boolean        penDown;
	Word           maxNum = DmNumRecordsInCategory (AddressDb,currentCategory);
   	Word           rows,orderInCategory;
  
   // If the user taps in the MailViewDisplay take them to the Edit View
   	rows=Min(RecordPerPage,maxNum);
	RctSetRectangle (&r, 0,FNameY, 160, rows*RecordHeight);
    
	if (RctPtInRectangle (event->screenX, event->screenY, &r)) {
		invertRec=AddressInvert(event->screenY);
		do {
			PenGetPoint (&x, &y, &penDown);
        } while (penDown);
      
		if (RctPtInRectangle (x, y, &invertRec)) {
			orderInCategory = ((y-15)/RecordHeight)+firstVisibleAddressIndex;
			currentRecIndex=VisibleRecordList[orderInCategory];
			if ( currentRecIndex < DmNumRecords(AddressDb))  {
              		 	prevCategory=currentCategory;
              		        if(prevCategory==dmAllCategories)
              	 		   prevCategory=dmUnfiledCategory;
				FrmGotoForm (EditForm1100);
				return handled;
			}
		}
		else  {
		       	AddressInvert(event->screenY);
         	}
		handled = true;
	}
	return handled;
}
 	
 	
 RectangleType  AddressInvert(SWord  y)
{
       RectangleType   r;
       Word            offset, index;
       

	index = ((y-15)/RecordHeight);
       	  y =	index*RecordHeight+15;
       RctSetRectangle(&r,FNameX,y,160 ,RecordHeight);
       
       WinInvertRectangle(&r,0);	
       return r;
	
}	
 	     