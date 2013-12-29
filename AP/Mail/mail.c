 /**********************************************************
 * Company     : Wiscore Inc                              * 
 *                                                        *  
 * Filename    : mail.c                                  *
 *                                                        * 
 * Description : a mail test AP for palm		  *	
 *		 					  *	
 * History     : 2001/11/20  by Vincent Chen	          *	
 *********************************************************/ 

#include <Pilot.h>
#include <System/SysAll.h>
#include <UI/UIAll.h>
#include "mail.h"
#include "mailRsc.h"

#define	MemoDBType						'DATA'
#define	MEMOCREATORID					'CATS'


/*************Constants***********************************/
#define      NoRecordID                     -1
#define      startPosition                   0
#define	     newMemSize			      1		
#define      FromTextString 		   "From :"
#define      SubjTextString 		   "Subj :"
#define	     FromTextStringSize		    10
#define	     SubjTextStringSize		    10
#define      FNameX			    0	
#define      FNameY			    15	
#define      RecordHeight		    11	
#define      RecordPerPage  		    11	

#define	     BLACK_UP_ARROW			   "\x01"
#define	     BLACK_DOWN_ARROW		   "\x02"
#define	     GRAY_UP_ARROW			   "\x03"
#define	     GRAY_DOWN_ARROW			   "\x04"
	    
#define      Mail_Index_Start			65 
#define      FirstMailIndex                   0	    
#define      SubjectMaxWidth                  80
#define	     FromMaxWidth                     40
	
/*************Global Variables****************************/
static   SystemPreferencesType    prefs;
static   DmOpenRef                MailDbP;                  // the reference to the open database  
static	 Word			  cardNum=0;
static   SWord                    currentMailIndex=0; 
static   SWord                    firstVisibleMailIndex=0;     
static   Word   		  totalMailNum; 
static   Word   		  mailSelect; 
static   Word                     currentCategory=dmAllCategories;
static   char                     String[5];  
//************Function Prototype Declaration ***********************************************

static  Err  StartApplication(void);
static  void EventLoop(void);
static  void StopApplication(void);

static Boolean  ApplicationHandleEvent(EventPtr event);
static Boolean  MainForm1000EventHandler(EventPtr  event);
static Boolean  ViewForm1100EventHandler(EventPtr  event);
static Boolean  AboutForm1200EventHandler(EventPtr  event);

//**********Main Function of program**********************************************************

DWord  PilotMain (Word cmd, Ptr cmdPBP, Word launchFlags)
{    
     Err    err;	  
      

  if  (cmd == sysAppLaunchCmdNormalLaunch)
     {
      err=StartApplication();            // Application start code
      if(err != 0)
         return   err; 
      EventLoop();                   // Event loop
      StopApplication ();            // Application stop code
    }
    return 0;
}

//----------------------------------------------------------------------------


static Err StartApplication(void)
{  
   
   Err     err;  	 
                                    // when starting,
                                 
   err=OpenDatabase();                               // Open database or create a new one  if necessary  
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
   
   FrmSaveAllForms ();
   FrmCloseAllForms();
   DmCloseDatabase (MailDbP);
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

      case ViewForm1100 :
                         FrmSetEventHandler(form,ViewForm1100EventHandler);
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
     
     
static Boolean  MainForm1000EventHandler(EventPtr  event)
{
   FormPtr       form=FrmGetActiveForm();	
   Word          maxNum;
   Boolean       handled=false; 
   ControlPtr	 upArrow,downArrow; 
 
           
            if ( event->eType ==  ctlRepeatEvent )  
                   {    
			upArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,UpRepeatButton1003));
			downArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,DownRepeatButton1004));
			maxNum = DmNumRecords (MailDbP);
			switch (event->data.ctlRepeat.controlID) {
				
				case UpRepeatButton1003:
					{
					  currentMailIndex-=RecordPerPage;
					  if ( currentMailIndex <= 0 ) {
						CtlSetLabel( upArrow, GRAY_UP_ARROW );
						CtlSetEnabled( upArrow, false );
						currentMailIndex = 0;
					  }

					  if ( maxNum > RecordPerPage ) {
						CtlSetLabel( downArrow, BLACK_DOWN_ARROW );
						CtlSetEnabled( downArrow, true );
					  }
					  firstVisibleMailIndex=currentMailIndex;
                        		  MainFormListMail(form);             

               				  break;
					 }

            			case DownRepeatButton1004:
					{
					  currentMailIndex+=RecordPerPage;
					  if ( (currentMailIndex+RecordPerPage) > maxNum ) {
						CtlSetLabel ( downArrow, GRAY_DOWN_ARROW );
						CtlSetEnabled( downArrow, false );
						currentMailIndex = maxNum-RecordPerPage;
					  }

					  if ( currentMailIndex > 0 ) {
						CtlSetLabel( upArrow, BLACK_UP_ARROW );
						CtlSetEnabled( upArrow, true );
					  }
					  firstVisibleMailIndex=currentMailIndex;
                       			  MainFormListMail(form);             
					  break;
					 }
             			 default:
 					  break;
                        } 
                   }
                 
      
       else  if ( event->eType == ctlSelectEvent )
                   {   
                   	 switch (event->data.ctlSelect.controlID)
		       { 
                   	case ExitButton1002:             
                   			     event->eType=appStopEvent;	
					     EvtAddEventToQueue(event);
                   	                     handled=true;
                   	                     break;    
                       }	
                   	
                   }	 
       else  if  ( event->eType == frmOpenEvent )
       
                   {    
                	FrmDrawForm(form);
                	
                	maxNum = DmNumRecords (MailDbP);
	                if ((firstVisibleMailIndex+RecordPerPage) > maxNum ) {
	                    currentMailIndex = maxNum-RecordPerPage;
	                    if(currentMailIndex < 0)
	                       currentMailIndex=0;
	                }  
	                else     		
                            currentMailIndex=firstVisibleMailIndex;
                        MailNumsDisplay();             
                	RptBtnInit(form);
                        MainFormListMail(form);
                     	handled=true;
                     
                   }	
           
       else  if  ( event->eType ==  penDownEvent )
       		   {	
         		handled = MailViewHandlePen(event);
         	   }		
            
        return    handled;
         	 
}


//-------------------------------------------------------------------------  
    	 
 
    
 static Boolean  ViewForm1100EventHandler(EventPtr  event)   	 
{
	
    FormPtr       form=FrmGetActiveForm();	
    FieldPtr      field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,Field1101) );
    Word          command; 
    Boolean       handled=false;   
    
               
            if  (event->eType==frmOpenEvent)       
           
                  { 
                   FrmDrawForm(form);	
		   ViewFormInit(form,currentMailIndex);	
		   
                   handled=true;    			  
                  }         
                         
                    
               
   else  if  ( event->eType ==  ctlSelectEvent )
                    {     
 	                      switch(event->data.ctlSelect.controlID)
 	                  { 
 	      			case  DoneButton1102:                   
 	      	      		                     FrmGotoForm(MainForm1000);
   						     handled=true;
 	      	    		                     break;		
 	      	    		               
 	      	
 	      			case  DeleteButton1103 :   
 	      						DeleteMail(form,currentMailIndex);               
			                                FrmGotoForm(MainForm1000);  	     
 	             		                        handled=true;
                                                        break;  
                                
 	  		   }
 	      
 	    	    } 
 	     
    else  if  ( event->eType == menuEvent )      // if one item in the menu is chosen
                        {
                          command = event-> data.menu.itemID; 	
                          if( MenuDoCommand(command) )	
	                      handled = true;   	
                        	
                         }	    
    else  if  (event->eType == fldChangedEvent)
	{
		ViewFormUpdateScrollBar (form,field);
		handled = true;
	}             
  	        
    else  if  ( event->eType == sclRepeatEvent )
        {       
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
       	                                            
       	                                            FrmReturnToForm(ViewForm1100);
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

//----------------------------------------------------------------------------


//********************************************************************************************
  //  This function opens the database(or create a new one if necessary)
             
   static Err OpenDatabase(void) 
{ 
    Err       error=0;
    Word      mode;
    //LocalID	dbID;
          
                   
  	   mode = dmModeReadWrite;// dmModeReadOnly; 	
           PrefGetPreferences(&prefs);
           if(!prefs.hideSecretRecords)
              mode |= dmModeShowSecret;	  
	  
	error = DmCreateDatabase (cardNum, dBName, MEMOCREATORID, MemoDBType, false);

	if ((error == 0)||(error == dmErrAlreadyExists)) {
		mode = dmModeReadWrite;
      MailDbP = DmOpenDatabaseByTypeCreator(MemoDBType,MEMOCREATORID,mode);
		if (!MailDbP)
			return (1);
	}
	
/*
	   dbID=DmFindDatabase(cardNum,dBName);	
	   if(dbID)   {	
   	          MailDbP=DmOpenDatabase(cardNum,dbID,mode);
   	   }
   	   else   ErrDisplay("Database NOT exist!"); 			  
*/
      	   return 0;
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
    
    DmOpenDatabaseInfo(MailDbP,&id,NULL,NULL,&cardNum,NULL);
    
    DmDatabaseInfo(cardNum,id,NULL,&attribute,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
     attribute &= ~mask  ; //clear field
     attribute |=  flag  ; //set   attributes
     DmSetDatabaseInfo(cardNum,id,NULL,&attribute,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); 
     
     
    return 0;	   	   
   } 

//------------------------------------------------------------------------------- 


//******************************************************************************************
 

//--------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------

  static  Boolean   DeleteMail(FormPtr form,Word index)
{
     Boolean    result; 
     Word       hitButton; 
     
       
               hitButton= FrmAlert(DeleteAlert3100);              // which is tapped.
//               hitButton= FrmCustomAlert( DeleteAlert3100 ,"OK","CANCEL",NULL);
               if (hitButton==alert_Cancel_Button) {
          	   result = false;
          	   return(result);                     
               }
               else  {	      
                      DmRemoveRecord (MailDbP, index);   
                      firstVisibleMailIndex--;
                      if(firstVisibleMailIndex < 0)
                         firstVisibleMailIndex=0;
               }       
               result=true;   
               return(result);             
}          
                  

//--------------------------------------------------------------------------------
void    MailIndexDisplay(Word   index)
{
	Word     maxNum=DmNumRecords(MailDbP);
	char     mailIndex[4],totalMailIndex[4];
	Word     mailIndexLength=0,totalMailIndexLength=0;
	
	StrIToA(mailIndex,index);
	while (index) {
		index /= 10;
		mailIndexLength++;
	}
	mailIndex[mailIndexLength]=0;
	StrIToA(totalMailIndex,maxNum);
	while (maxNum) {
		maxNum /= 10;
		totalMailIndexLength++;
	}
	totalMailIndex[totalMailIndexLength]=0;
	WinDrawChars(mailIndex,StrLen(mailIndex),Mail_Index_Start,1);
	WinDrawChars("OF",2,Mail_Index_Start+15,1);
	WinDrawChars(totalMailIndex,StrLen(totalMailIndex),Mail_Index_Start+30,1);
	WinDrawChars("Mails",5,Mail_Index_Start+45,1);
	
	
	
}


void	SetFieldUneditable(FieldPtr	field)
{
	FieldAttrType   attri;
	
	FldGetAttributes(field,&attri);
	attri.editable=false;
	FldSetAttributes(field,&attri);
	
}	

static  void   ViewFormInit(FormPtr  form,Word mailIndex)
{
	FieldPtr     	fromField=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FieldFrom1105)),
			subjField=FrmGetObjectPtr(form,FrmGetObjectIndex(form,FieldSubject1106)),
			bodyField=FrmGetObjectPtr(form,FrmGetObjectIndex(form,Field1101));
	char*  		mailP;
	DWord           offset=0;
	
	
	MailIndexDisplay(mailIndex+1);
	mailP=ViewFormGetRecord(form,mailIndex);
	if(mailP)  {
	   FldInsert(fromField,mailP,StrLen(mailP));
	   mailP +=(StrLen(mailP)+1);
	   FldInsert(subjField,mailP,StrLen(mailP));
	   mailP +=(StrLen(mailP)+1);
	   SetFieldUneditable(bodyField);	
           FldSetTextPtr(bodyField,mailP);
	}
	FldRecalculateField(bodyField,true);
	FldDrawField(bodyField);
	SetFieldUneditable(fromField);	
	SetFieldUneditable(subjField);	
	
}	

//--------------------------------------------------------------------------------
static  void*   ViewFormGetRecord(FormPtr form,Word mailIndex)

{
     
     VoidHand     recordH;
     VoidPtr      recordP,mailP;
     DWord        recordSize;


        recordH = DmQueryRecord(MailDbP,mailIndex);         //get the record
        if(!recordH)   ;
        recordP = MemHandleLock(recordH);
        if(recordP)  {
           recordSize=MemPtrSize(recordP);
    	   mailP=MemPtrNew(recordSize);
	   MemSet(mailP,recordSize,0);
	   MemMove( (void*)mailP,recordP,recordSize);
        }
        MemHandleUnlock(recordH);
        DmReleaseRecord(MailDbP,mailIndex,true);
        return   mailP;
		     	   
}     	            




//**********************************************************************************************
void    MailNumsDisplay()
{
	Word     maxNum=DmNumRecords(MailDbP);
	char     totalMailIndex[4];
	Word     totalMailIndexLength=0;
	
	StrIToA(totalMailIndex,maxNum);
	while (maxNum) {
		maxNum /= 10;
		totalMailIndexLength++;
	}
	totalMailIndex[totalMailIndexLength]=0;
	
	if(totalMailIndex[0]!=0) 
	WinDrawChars(totalMailIndex,StrLen(totalMailIndex),Mail_Index_Start+55,1);
	else 
	WinDrawChars("0",1,Mail_Index_Start+55,1);
	WinDrawChars("Mails",5,Mail_Index_Start+70,1);

}
//--------------------------------------------------------------------------------------
  
 static  void  MainFormListMail(FormPtr  form)       
{   
   
	VoidHand	recordH;
	char*		recordP;	
	Word		indexStart=0,count=0; 
	Char		numBuffer[4];
        CharPtr         fromP,subjP; 
	Word		bufLength, numLength, tcount;	
	Word            fromMaxLength,subjMaxLength;
	RectangleType	eraseRect;
	
	
	RctSetRectangle (&eraseRect, 0, 15, 160, 121);
	WinEraseRectangle (&eraseRect, 0);
	while (!DmSeekRecordInCategory (MailDbP, &indexStart, 0, dmSeekForward, currentCategory)) {
		recordH = DmQueryRecord (MailDbP, indexStart+currentMailIndex);
		if (recordH) {
			tcount = count+currentMailIndex+1;
			StrIToA (numBuffer, tcount);
			numLength = 0;
			while (tcount) {
				tcount = tcount/10;
				numLength++;
			}
			tcount =  count+currentMailIndex+1;
			recordP = MemHandleLock(recordH);
		        fromP=MemPtrNew(StrLen(recordP)+1);
		        if(fromP) {
             		   MemSet(fromP,StrLen(recordP)+1,0);
             		   MemMove((void*)fromP,recordP,StrLen(recordP)+1);
             		}
             		recordP+=(StrLen(recordP)+1);
             		subjP=MemPtrNew(StrLen(recordP)+1);
             		if(subjP) {
             		   MemSet(subjP,StrLen(recordP)+1,0);
             		   MemMove(subjP,recordP,StrLen(recordP)+1);
			}
			numBuffer[numLength+1] = 0;
				numBuffer[numLength] = '.';
				if ( tcount < 10 ) {
					WinDrawChars (numBuffer, StrLen(numBuffer), FNameX+5, count*RecordHeight+15);
				} else {
					WinDrawChars (numBuffer, StrLen(numBuffer), FNameX, count*RecordHeight+15);
				}
				if(subjP)  {
			 	   subjMaxLength=FntWordWrap(subjP,SubjectMaxWidth);
			 	   WinDrawChars (subjP, subjMaxLength, FNameX+15, count*RecordHeight+15);
			 	}   
				WinDrawChars ("By",  2,  FNameX+100, count*RecordHeight+15);
				if(fromP)  {
				   fromMaxLength=FntWordWrap(fromP,FromMaxWidth);	
				   WinDrawChars (fromP, fromMaxLength,  FNameX+120, count*RecordHeight+15);
				}
				count++;
		        
			MemHandleUnlock(recordH);
			MemPtrFree(fromP);
			MemPtrFree(subjP);
			
			if ( count >= RecordPerPage )
			     break;
		}
		indexStart++;
	}

	     	  
  	 
}







//------------------------------------------------------------------------------
void   RptBtnInit(FormPtr  form)
{
	
	ControlPtr	upArrow;
	ControlPtr	downArrow;
	Word            maxNum;

	upArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,UpRepeatButton1003));
	downArrow = FrmGetObjectPtr(form,FrmGetObjectIndex(form,DownRepeatButton1004));
	maxNum = DmNumRecords (MailDbP);
        
        if(maxNum <=  RecordPerPage)  {
             CtlHideControl(upArrow);
             CtlHideControl(downArrow);
             return;
        }
             	
	if ( currentMailIndex <= 0 ) {
	     CtlSetLabel( upArrow, GRAY_UP_ARROW ); 
	     CtlSetEnabled( upArrow, false );
	} else {
		CtlSetLabel( upArrow, BLACK_UP_ARROW );
		CtlSetEnabled( upArrow, true );
	  }
	if ( maxNum > RecordPerPage ) {
	     CtlSetLabel( downArrow, BLACK_DOWN_ARROW );
	     CtlSetEnabled( downArrow, true );
	} else {
		CtlSetLabel( downArrow, GRAY_DOWN_ARROW );
		CtlSetEnabled( downArrow, false );
	}
	if(firstVisibleMailIndex+RecordPerPage >= maxNum) {
		CtlSetLabel( downArrow, GRAY_DOWN_ARROW );
		CtlSetEnabled( downArrow, false );
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
static Boolean MailViewHandlePen (EventType * event)
{
	Boolean        handled = false;
	RectangleType  r,invertRec;
	Word           x, y;
	Boolean        penDown;
	Word           maxNum = DmNumRecords (MailDbP);
   	Word           rows;
  
   // If the user taps in the MailViewDisplay take them to the Edit View
   	rows=Min(RecordPerPage,maxNum);
	RctSetRectangle (&r, 0,FNameY, 160,rows*RecordHeight);
    
	if (RctPtInRectangle (event->screenX, event->screenY, &r)) {
		invertRec=MailInvert(event->screenY);
		do {
			PenGetPoint (&x, &y, &penDown);
        } while (penDown);
      
		if (RctPtInRectangle (x, y, &invertRec)) {
			currentMailIndex = ((y-15)/RecordHeight)+firstVisibleMailIndex;
			if ( currentMailIndex < maxNum )  {
				FrmGotoForm (ViewForm1100);
				return handled;
			}
		}
		else  {
		       	MailInvert(event->screenY);
         	}
		handled = true;
	}
      
	return handled;
}


//***************************************************************************************
 RectangleType  MailInvert(SWord  y)
{
       RectangleType   r;
       Word            offset, index;
       

	index = ((y-15)/RecordHeight);
       	  y =	index*RecordHeight+15;
       RctSetRectangle(&r,FNameX,y,160 ,RecordHeight);
       
       WinInvertRectangle(&r,0);	
       return r;
	
}	

//--------------------------------------------------------------------------------------


//******************************************************************************************

static void 	ViewFormUpdateScrollBar(FormPtr form,FieldPtr  field)
{  
  
   ScrollBarPtr   scrollP;
   Word           scrollPosition;
   Word           textHeight;
   Word           fieldHeight;
   SWord          maxValue; 	
	     
	 
	scrollP=FrmGetObjectPtr(form,FrmGetObjectIndex(form,Scrollbar1104));
	FldGetScrollValues(field ,&scrollPosition,&textHeight,&fieldHeight);
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
    ScrollBarPtr     scrollP;
    Word             currentPosition,max,min,pagesize;
    Boolean          direction;
    Word             scrollPosition;
    Word             textHeight;
    Word             fieldHeight;
   
  
   
    	   linesToScroll=(newValue > value)?(newValue-value):(value-newValue);
    	   direction=(newValue < value)? up : down;
    	   FldScrollField(field,linesToScroll,direction);
    	   //if( FldGetNumberOfBlankLines (field) ) 
    	   ViewFormUpdateScrollBar(form,field);
       
         
}  






 static   Boolean   MenuDoCommand(Word command)	
 { 
 	FormPtr    formform = FrmGetActiveForm(); 
 	//FieldPtr   field;        
	Boolean    handled=false;
       	
         
         //field =  FrmGetObjectPtr(form,FrmGetObjectIndex(form,Field1101) );
            
         
        switch( command )
     {
          
         case    AboutItem2108:  
                                   FrmPopupForm(AboutForm1200);                   
             	                   break; 
     	  

         case    FontItem2111:     
                                    FrmPopupForm(FontDialogForm1300);                          
                                    handled=true;
                                    break;   
            
      }    
          
      return(handled);    
}
           