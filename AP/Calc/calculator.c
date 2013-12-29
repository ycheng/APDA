 /**********************************************************
 * Company     : Wiscore Inc                               * 
 *                                                         *  
 * Filename    : calculator.c                              *
 *                                                         * 
 * Description : Calculator AP		                   *	
 *		 				      	   *	
 * History     : 2001/10/26  by Vincent Chen	           *	
 *********************************************************/ 
 
 
#include 	<Common.h>
#include 	<System/SysAll.h>
#include 	<UI/UIAll.h>
#include "calculator.h"
#include "calculatorrsc.h" 

//******************Constant*******************************************************//

#define        MaxDigits               32
#define        maxHandleSize           MaxDigits+1
#define        effFracNums	       12 	
//****************  Global Variables ******************************************************//
VoidHand                fieldDisplayH;
char*                   fieldDisplayP;          

char			digitString[MaxDigits+1];
char			destValue[MaxDigits+1]; 
char			firstOperand[MaxDigits+1];
Word			destOpCount=0;
Word			destOpFrac=0;
Word			firstOpCount=0;
Word			firstOpFrac=0;
     
Boolean		        displayNeedUpdate;                    // flag to judge whether to update the display
Boolean		        appendDigitNum; 
Boolean			fraction=false;
Word			operation=operation_none;
Boolean 		DivideZero=false;
char			String[3];                            //  for debug
//********************************************************************************//
int     StartApplication(void);
void    EventLoop(void);
void    StopApplication(void);
Boolean CalculatorForm1000HandleEvent(EventPtr  event);

//********************************************************************************//


DWord  PilotMain (Word cmd, Ptr cmdPBP, Word launchFlags)
{
	int   error;
	
	if (cmd == sysAppLaunchCmdNormalLaunch) {
		error = StartApplication();	
		if (error) return error;
		EventLoop();	
		StopApplication ();	
	}

	return 0;
}



//----------------------------------

int StartApplication(void)
{
	
	
	fieldDisplayH=MemHandleNew(maxHandleSize);
	fieldDisplayP=MemHandleLock(fieldDisplayH);
	MemSet(fieldDisplayP, maxHandleSize,0);
	MemHandleUnlock(fieldDisplayH);
 
	FrmGotoForm(CalculatorForm1000);
  
	return(0); /* No error */
}


//---------------------------------

void EventLoop(void)
{
	short		err;
	Word		formID;
	FormPtr	        form;
	EventType       event;

	do {
		EvtGetEvent(&event, evtWaitForever);

		if (SysHandleEvent(&event)) continue;
		if (MenuHandleEvent((void *)0, &event, &err)) continue;

		if (event.eType == frmLoadEvent) {
			formID = (Word) event.data.frmLoad.formID;
			form = FrmInitForm(formID);

			switch (formID) {  
				case    CalculatorForm1000:
					FrmSetEventHandler(form, (FormEventHandlerPtr) CalculatorForm1000HandleEvent);
					break;  

				
			}

			FrmSetActiveForm( form );
		} 

		FrmDispatchEvent(&event);
	} while(event.eType != appStopEvent);
}


//-----------------------

void StopApplication(void)
{
	
	FrmCloseAllForms ();
	
}



//*****************************************************************************

Boolean CalculatorForm1000HandleEvent(EventPtr  event)
{
	FormPtr    form=FrmGetActiveForm();
	Boolean    handled=false;
               
	if ( event->eType == frmOpenEvent )  {    
		CalcFormInit(form);
		DisplayUpdate (form);
		FrmDrawForm(form);
		handled=true;
	}	
	
	else if   ( event->eType == ctlSelectEvent ) {
		displayNeedUpdate=TapButton(event);
		if(displayNeedUpdate)
			DisplayUpdate(form);
		displayNeedUpdate=false;
		handled=true;	 
	} 
                 
                 
	return (handled);      
}      



//************************************************************************************//

void    CalcFormInit(FormPtr  form)
{
	MemSet(destValue,MaxDigits+1,0);
	destOpCount = 0;
	destOpFrac = 0; 
	fraction = false;  
	MyCharToStr (digitString, destValue, destOpCount, destOpFrac);
}



Boolean   TapButton(EventPtr event)
{
	
	  switch(event->data.ctlSelect.controlID)
	{ 
	   case  One1001 :    AppendDigitalNum(1);  break;
	   case  Two1002 :    AppendDigitalNum(2);  break;
	   case  Three1003:   AppendDigitalNum(3);  break;
	   case  Four1004 :   AppendDigitalNum(4);  break;
	   case  Five1005 :   AppendDigitalNum(5);  break;
	   case  Six1006  :   AppendDigitalNum(6);  break;
	   case  Seven1007 :  AppendDigitalNum(7);  break;
	   case  Eight1008 :  AppendDigitalNum(8);  break;
	   case  Nine1009  :  AppendDigitalNum(9);  break;      
	   case  Zero1010  :  AppendDigitalNum(0);  break;  
	   
	   case  Add1016 :      Add();              break;  
	   case  Sub1015 :      Subtract();         break;     
	   case  Multiply1014 : Multiply();         break; 
	   case  Divide1013 :   Divide();  	    break; 
	   case  Equal1018 :    Equal();            break;
	   
	   case  Dot1011 :      fraction=true;
	                        if(!destOpCount)  
	                            destOpCount++;             
	                                            break;
	   
	   case  Sign1012 :     ChangeSign();       break;
	   case  Clear1017 :    Clear();            break; 
	   case  CE1019 :       CE();               break;
	   case  Percent1020:   Percent();          break; 
	   case  BS1021:        BackSpace();        break;
	   
	                   
	} 
	return   displayNeedUpdate;
}	 

Char *MyCharToStr (Char *Dst, Char *Src, int CountLen, int FracLen)
{
	char    digitBuffer[2];
	int	i;

 
	digitBuffer[1] = 0;
	if ( CountLen==0 ) 
		digitBuffer[0] = '0';
	else  {
		if( CountLen+FracLen < MaxDigits)  
		digitBuffer[0] = Src[(CountLen+FracLen)-1]+'0';  
	}
	
	if ( Src[MaxDigits] )  {  
		MemMove (Dst, &Src[MaxDigits],1);
		MemMove(Dst+1, digitBuffer,2);   
        }		
	else {  
		StrCopy (Dst, digitBuffer);  
	}

	
	for ( i = CountLen-2 ; i >= 0; i-- ){
        	digitBuffer[0] = Src[i+FracLen]+'0';
		StrCat (Dst, digitBuffer);  //ErrDisplay (Dst);
	}
	
	StrCat(Dst, ".");
	
	for ( i = FracLen-1; i >= 0; i-- ){     
        	digitBuffer[0] = Src[i]+'0';
		StrCat (Dst, digitBuffer);
	}
	 
	
	return	Dst;
}

Boolean AppendDigitalNum(char  digit)
{
	if((destOpCount+destOpFrac) >= (MaxDigits-1))
		return false;
	if(DivideZero==true) {
	        return false;
	}        		
	if(((destOpCount+destOpFrac)==1)&&(destValue[destOpCount+destOpFrac-1]==0) && (!fraction) ) {
		if (digit==0)
	   	    	return false;
	   	else
	   	        destOpCount--; 
	}
	  	
	MemMove (&(destValue[1]), &(destValue[0]), (destOpCount+destOpFrac));
        
	destValue[0]=digit;
	if (fraction)      
		destOpFrac++;
	else
		destOpCount++;
	

	destValue[(destOpCount+destOpFrac)] = 0;    
	MyCharToStr (digitString, destValue, destOpCount, destOpFrac);
	displayNeedUpdate = true;
       //ErrDisplay(StrIToA(String,destOpCount)); ErrDisplay(StrIToA(String,destOpFrac)); 
	
	return(displayNeedUpdate);            
}	                           
/*
void CompareOperands(char *Operand1, Word* OpCount1, Word* OpFrac1,char *Operand2, Word* OpCount2, Word* OpFrac2)
{
     char*    temp[MaxDigits+1];
     Word     tCount,tFrac;	
     Word     i;
     SWord    minFrac;
     Boolean  neg=false;
     
        Operand1[MaxDigits]=0;
        Operand2[MaxDigits]=0;
     	if(*OpCount1 < *OpCount2)   {
     	   neg=true;
     	} else  if(*OpCount1 == *OpCount2) {   
     		        minFrac=Min((SWord)*OpFrac1,(SWord)*OpFrac2); 
                        i=1;	    
                        while((i <= *OpCount1+minFrac )&&(Operand1[*OpCount1+*OpFrac1-i] == Operand2[*OpCount2+*OpFrac2-i]))  {
                               i++;  
                        }                    
             	        if(i <= *OpCount1+minFrac)  {
             	            neg=(Operand1[*OpCount1+*OpFrac1-i] > Operand2[*OpCount2+*OpFrac2-i])? false : true ;	 		
     	                }
     	                else if(i <=  *OpCount1+*OpFrac2)
     	                        neg=true;
                }	
	if(!neg)    return;
	else  { 
	          MemSet(temp,MaxDigits+1,0);
	          MemMove(temp,Operand1,MaxDigits+1);
	          MemMove(Operand1,Operand2,MaxDigits+1);
	          MemMove(Operand2,temp,MaxDigits+1);
	          tCount= *OpCount1;
	          *OpCount1=*OpCount2;
	          *OpCount2=tCount;
	          tFrac= *OpFrac1;
	          *OpFrac1=*OpFrac2;
	          *OpFrac2=tFrac;
	 	  Operand1 	
	}
}
*/	
void TruncateFraction (char *Operand1, Word* OpCount1, Word* OpFrac1)
{
	Word  i;
	
	if(*OpFrac1!=0) { 
         	for(i=0 ; (i <=*OpFrac1-1)&&(Operand1[i]==0) ;i++) ;
                *OpFrac1 -=i; 	                     
		MemMove(Operand1,&Operand1[i],*OpCount1+*OpFrac1);
	}
	
	
}	 
void NUMADD (char *Operand1, Word *OpCount1, Word *OpFrac1, char *Operand2, Word OpCount2, Word OpFrac2)
{
	int	i, index, Count;
     	char    copyOperand2[MaxDigits+1];
     	Boolean swap=false;  
     	Word    copyCount2,copyFrac2;
	
	if((*OpCount1+*OpFrac1) >= MaxDigits-1)
	    return;
	if ( OpFrac2 > *OpFrac1 ) {
		MemMove (&(Operand1[OpFrac2-*OpFrac1]),&(Operand1[0]), (*OpCount1+*OpFrac1));
		MemSet (&(Operand1[0]), OpFrac2-*OpFrac1, 0);
		*OpFrac1 = OpFrac2;
	}
        else if ( OpFrac2 < *OpFrac1 ){
              MemMove (&(Operand2[*OpFrac1-OpFrac2]), &(Operand2[0]), (OpCount2+OpFrac2));
	      MemSet (&(Operand2[0]), *OpFrac1-OpFrac2, 0);
	      OpFrac2 = *OpFrac1;    	
         	
        } 
        if(OpCount2 > *OpCount1 || OpFrac2 > *OpFrac1) {
              MemSet(copyOperand2,MaxDigits+1,0);
              MemMove(copyOperand2,Operand2,MaxDigits+1);	
     	      copyCount2=OpCount2;
     	      copyFrac2=OpFrac2;
              
              Swap(Operand1, OpCount1, OpFrac1, Operand2,  &OpCount2,  &OpFrac2); 
              swap=true;
        }
	Count = (*OpCount1+*OpFrac1 < OpCount2+OpFrac2)? (*OpCount1+*OpFrac1) : (OpCount2+OpFrac2);
	Operand1[0] = Operand1[0]+Operand2[0];
	for ( i = 1; i < Count; i++ ) {
		Operand1[i] = Operand1[i]+Operand2[i]+Operand1[i-1]/10;
		Operand1[i-1]%=10;
	}
        
	index = Count;
	Count = (*OpCount1+*OpFrac1 > OpCount2+OpFrac2)? *OpCount1+*OpFrac1 : OpCount2+OpFrac2;
	for ( i = index; i < Count; i++ ) {
		Operand1[i] = Operand1[i]+Operand1[i-1]/10;
		Operand1[i-1]%=10;
	}
	

	if ( Operand1[Count-1] >= 10 ) {
		Operand1[Count] = Operand1[Count-1]/10;
		Operand1[Count-1]%=10;
		Count++;      
	}
	
	*OpFrac1 = (*OpFrac1 > OpFrac2)? *OpFrac1 : OpFrac2;
	*OpCount1 = Count-*OpFrac1;
	TruncateFraction (Operand1, OpCount1, OpFrac1);

        if(swap)
           Swap(Operand2, &OpCount2, &OpFrac2, copyOperand2, &copyCount2,&copyFrac2);      	
}

void NUMSUB (char *Operand1, Word *OpCount1, Word *OpFrac1, char *Operand2, Word OpCount2, Word OpFrac2)
{ 
	char         copyOperand2[MaxDigits+1];
	Boolean      neg=false;
	SWord        Count,i,j;
	int          zero_cut;
	SWord	     minFrac;
	Word	     copyFrac2, copyCount2;
	char         test[33];      MemSet(test,33,0);
     	
     	if(*OpCount1 < OpCount2)   {
     	   neg=true;
     	} else  if(*OpCount1 == OpCount2) {   
	           	//maxFrac=Max((SWord)*OpFrac1,(SWord)OpFrac2);   //ErrDisplay(StrIToA(String,max));
     		        minFrac=Min((SWord)*OpFrac1,(SWord)OpFrac2); 
     		      
                        i=1;	    
                        while((i <= *OpCount1+minFrac )&&(Operand1[*OpCount1+*OpFrac1-i] == Operand2[OpCount2+OpFrac2-i]))  {
                               i++;  
                        }                    
             	        if(i <= *OpCount1+minFrac)  {
             	            neg=((Operand1[*OpCount1+*OpFrac1-i] > Operand2[OpCount2+OpFrac2-i])? false : true);
     	                }
     	                else if(i <=  *OpCount1+OpFrac2)
     	                        neg=true;
                }	
        
     	if(neg)  {                // operand2 > operand1 when operand1-operand2
                  MemSet( copyOperand2,MaxDigits+1,0);
                  MemMove(copyOperand2,Operand2,MaxDigits+1);
     	          copyCount2=OpCount2;
     	          copyFrac2=OpFrac2;
     	          
                  Swap(Operand1, OpCount1, OpFrac1, Operand2, &OpCount2,  &OpFrac2); 
                  if(Operand1[MaxDigits]==Operand2[MaxDigits])  {
                     Operand1[MaxDigits]= (Operand1[MaxDigits])? 0 :'-'; 
                  }
     	} 	       
	if ( OpFrac2 > *OpFrac1 ) {
		MemMove (&(Operand1[OpFrac2-*OpFrac1]), &(Operand1[0]), (*OpCount1+*OpFrac1));
		MemSet (&(Operand1[0]), OpFrac2-*OpFrac1, 0);
		*OpFrac1 = OpFrac2;
	}
        else if ( OpFrac2 < *OpFrac1 ){
                MemMove (&(Operand2[*OpFrac1-OpFrac2]), &(Operand2[0]), (OpCount2+OpFrac2));
	        MemSet (&(Operand2[0]), *OpFrac1-OpFrac2, 0);
	        OpFrac2 = *OpFrac1;    	
         	
        } 
     	
     	     
	Count =  OpCount2+OpFrac2;
	for(i=0 ; i < Count ;i++) {
	   if( Operand1[i] < Operand2[i] ) {
	       Operand1[i]= Operand1[i]+10-Operand2[i];
	       for (j = i+1; j < *OpCount1+*OpFrac1; j++ ) {
	          if ( Operand1[j] != 0 ) {
	          	Operand1[j]--;
	          	break;
		  } else 
		  	Operand1[j] = 9;   		          
	       }
	       
	   }  else {
  	           Operand1[i]= Operand1[i]-Operand2[i];  
              } 
	}
	
	for(i=*OpCount1+*OpFrac1-1,zero_cut=0; (i >= (SWord)*OpFrac1)&&(Operand1[i]== 0) ;i--) {
	zero_cut++;   
	}
        *OpCount1 = *OpCount1-zero_cut;   
        if ( *OpCount1 == 0 )
             *OpCount1 = 1;
	TruncateFraction (Operand1, OpCount1, OpFrac1);
	
	if(neg)
	   Swap(Operand2, &OpCount2, &OpFrac2, copyOperand2, &copyCount2,&copyFrac2);

     //ErrDisplay(MyCharToStr(test,Operand2,OpCount2,OpFrac2));	
}


void  NUMMUL (char *Operand1, Word *OpCount1, Word *OpFrac1, char *Operand2, Word OpCount2, Word OpFrac2)
{
	SWord    i,j,zero_cut;
	Word     totalCount=*OpCount1+*OpFrac1+OpCount2+OpFrac2;
	char     sum[MaxDigits+1];

        if( ((*OpCount1+*OpFrac1)==0) || ((OpCount2+OpFrac2)==0) )
             return;
	if(totalCount < MaxDigits)
	   MemSet (sum, totalCount, 0);
	for(i=0 ; i < OpCount2+OpFrac2 ; i++)   {
	 	
	     for( j=0 ;j < *OpCount1+*OpFrac1 ;  j++) {
	           sum[i+j+1] += (Operand2[i]*Operand1[j]+sum[i+j])/10;
	      	   sum[i+j] = (Operand2[i]*Operand1[j]+sum[i+j])%10;
	     }
	}
	MemMove(Operand1,sum,totalCount);
	*OpFrac1+=OpFrac2;
	*OpCount1=(sum[totalCount-1]==0)?(totalCount-*OpFrac1-1) : (totalCount-*OpFrac1);
	totalCount=*OpFrac1+*OpCount1;   
	for(i=totalCount-1,zero_cut=0;(i>=*OpFrac1)&&(Operand1[i]== 0) ;i--){
            zero_cut++;     
	}
        *OpCount1 = *OpCount1-zero_cut; 
        if ( *OpCount1 == 0 )
             *OpCount1 = 1;
	TruncateFraction (Operand1, OpCount1, OpFrac1);
   	
   	if(Operand1[MaxDigits]==(Operand2[MaxDigits]))
   	      Operand1[MaxDigits]=0; 
   	else  Operand1[MaxDigits]='-';   
}	


void  NUMDIV (char *Operand1, Word *OpCount1, Word *OpFrac1, char *Operand2, Word OpCount2, Word OpFrac2)
{
	char    quotient[MaxDigits+1];
	char    temp[MaxDigits+1];
	Word    tCount, tFrac;
	SWord   i,zero_cut;
	char    test[33];        MemSet(test,33,0);
              
        
        if( ((*OpCount1+*OpFrac1)==0) || ((OpCount2+OpFrac2)==0) )
            return;
        if(OpFrac2)  {
                if(*OpFrac1 < OpFrac2) { 
                    MemMove(Operand1+OpFrac2-*OpFrac1,Operand1,*OpCount1+*OpFrac1);
                    MemSet(Operand1,OpFrac2-*OpFrac1,0);
                    *OpCount1 += OpFrac2;
                    *OpFrac1=0;
                }    
                else {	    
 		          *OpCount1+= OpFrac2  ;
		          *OpFrac1 -= OpFrac2  ;
		}
		    OpCount2+= OpFrac2  ;   
		    OpFrac2= 0 ;
		    for(i=OpCount2-1,zero_cut=0; (Operand2[i]== 0) ;i--) {
			zero_cut++;   
		    }
        	    OpCount2 = OpCount2-zero_cut;   
	            
	}
      	    MemMove (&(Operand1[effFracNums]), &(Operand1[0]), *OpCount1+*OpFrac1);
            MemSet(Operand1,effFracNums,0);
            *OpCount1 += (effFracNums+*OpFrac1);
          
        
	MemSet( quotient,MaxDigits+1,0);
	MemSet( temp,MaxDigits+1,0);
	if(Operand2[OpCount2+OpFrac2-1]==0)   {
		StrCopy(digitString,"error division"); 
		DivideZero=true; 
		return;
	}
              
	//if(Operand1[*OpCount1+*OpCount1-1]==0)  
   	if(Operand1[MaxDigits]==(Operand2[MaxDigits]))
   	      quotient[MaxDigits]=0; 
   	else  quotient[MaxDigits]='-';   
	quotient[0]=0;     
	for ( i =(*OpCount1-OpCount2)+1; i > 0; i-- ) {
		quotient[i-1] = Operand1[OpCount2-2+i]/Operand2[OpCount2-1];
		if(quotient[i-1] > 9)
			quotient[i-1]=9;   
		MemSet(temp,MaxDigits+1,0);  
		tCount=1; 
		tFrac=0;
		temp[0] = quotient[i-1];   
		do { 
			NUMMUL (temp, &tCount, &tFrac, Operand2, OpCount2,OpFrac2);  
			if(tCount > OpCount2) {
				temp[tCount-2] = temp[tCount-1]*10+temp[tCount-2];
				tCount--;
			}     
			NUMSUB (temp, &tCount, &tFrac, Operand1+OpCount2-2+i-tCount+1, tCount,tFrac);  
			if(((tCount+tFrac)==1) && (temp[tCount+tFrac-1]==0))  
				break;
			if (!temp[MaxDigits])  {        
				quotient[i-1]--;      
				temp[0]= quotient[i-1];
				tCount=1;                     
				if(temp[0]==0)    
				break;
			} 
		} while (!temp[MaxDigits]); 
		if(quotient[i-1]!=0)   {
			if(tCount!=OpCount2 || tFrac != OpFrac2) {
				tCount=OpCount2 ;
				tFrac= OpFrac2  ;
			}  
			temp[MaxDigits]=0;
			MemMove(Operand1+OpCount2-2+i-tCount+1,temp,tCount+tFrac);
		} 
 	 
		if ( i-1 > 0 )  {  
			Operand1[OpCount2-2+i-1] = Operand1[OpCount2-2+i]*10+Operand1[OpCount2-2+i-1];
		}    
	}
              
	*OpCount1=(quotient[*OpCount1-OpCount2+1])?(*OpCount1-OpCount2):(*OpCount1-OpCount2+1);
	if ( *OpCount1 > effFracNums+*OpFrac1 ) {
		*OpCount1 -= (effFracNums+*OpFrac1);
		*OpFrac1 +=   effFracNums;
	} else {
		*OpFrac1 += effFracNums;
		*OpCount1 = 1;
	}
	MemMove(Operand1,quotient,MaxDigits+1);
	for(i=*OpCount1+*OpFrac1-1,zero_cut=0; (i >= (SWord)*OpFrac1)&&(Operand1[i]== 0) ;i--) {
	zero_cut++;   
	}
        *OpCount1 = *OpCount1-zero_cut;   
        if ( *OpCount1 == 0 )
             *OpCount1 = 1;
	TruncateFraction (Operand1, OpCount1, OpFrac1);
  
	
}

void   Swap(char *Operand1, Word *OpCount1, Word *OpFrac1, char *Operand2, Word* OpCount2, Word* OpFrac2)
{
	
       Char	temp[MaxDigits+1];
       int	itemp;
     		
     		  itemp = *OpCount2;
     		  *OpCount2 = *OpCount1;
     		  *OpCount1 = itemp;
     		  itemp = *OpFrac2;
     		  *OpFrac2 = *OpFrac1;
     		  *OpFrac1 = itemp;
    		 
     		  MemMove (temp, Operand1, MaxDigits+1);
     		  MemMove (Operand1, Operand2, MaxDigits+1);
     		  MemMove (Operand2, temp, MaxDigits+1);

	
}	

Boolean    Add()
{
	
	
	Equal();
	operation=operation_add;
	MemSet(destValue,MaxDigits+1,0);
	destOpCount = 0;
	destOpFrac = 0;
	fraction=false;
	displayNeedUpdate=false;	 
	return(displayNeedUpdate);     
}

Boolean    Subtract()
{
       
	
	Equal();
	operation=operation_subtract;
	MemSet(destValue,MaxDigits+1,0);
	destOpCount = 0;
	destOpFrac = 0;
	fraction=false;

	displayNeedUpdate=false;	
	return(displayNeedUpdate);
}

Boolean   Multiply()
{
        
	
	Equal();
	operation=operation_multiply;
	MemSet(destValue,MaxDigits+1,0);
	destOpCount = 0;
	destOpFrac = 0;
	fraction=false;

	displayNeedUpdate=false;	
	return(displayNeedUpdate);
}	

Boolean    Divide()
{
	
	Equal();   
	operation=operation_divide;
	MemSet(destValue,MaxDigits+1,0);
	destOpCount = 0;
	destOpFrac = 0;
	fraction=false;
       	displayNeedUpdate=false;	
       	return(displayNeedUpdate);      
}

	

 
Boolean   Equal(void)
{
	Word         count=0;	
        Boolean      operated=false;       
        char          temp[33]; MemSet(temp,33,0);          
	switch(operation) {   
		  
		case  operation_add :   
				     if(firstOperand[MaxDigits]==destValue[MaxDigits])	    
				        NUMADD (firstOperand, &firstOpCount, &firstOpFrac, destValue, destOpCount, destOpFrac);
				     else {  //do something...
				        NUMSUB (firstOperand, &firstOpCount, &firstOpFrac, destValue, destOpCount, destOpFrac);  	
				     }	   
				     operated=true;
			             break;
	       	                             
		case  operation_subtract :  
			             if(firstOperand[MaxDigits]==destValue[MaxDigits]) {
			             	// do something...
				        NUMSUB (firstOperand, &firstOpCount, &firstOpFrac, destValue, destOpCount, destOpFrac);
				     }   
				     else {
				        NUMADD (firstOperand, &firstOpCount, &firstOpFrac, destValue, destOpCount, destOpFrac);
				     }   	
				     operated=true;
			             break;  
	       	 
		case  operation_multiply :  
                       	             NUMMUL (firstOperand, &firstOpCount, &firstOpFrac, destValue, destOpCount, destOpFrac);
                       	             operated=true;
			             break;      
	       	 
		case  operation_divide :    
                       	             NUMDIV (firstOperand, &firstOpCount, &firstOpFrac, destValue, destOpCount, destOpFrac);
                       	             operated=true;
			             break;                                                                    
	       	                             
		default:                    
			             MemMove(firstOperand, destValue,destOpCount+destOpFrac);
			             MemMove(&firstOperand[MaxDigits],&destValue[MaxDigits],1);
			             firstOpCount = destOpCount;
			             firstOpFrac = destOpFrac;
			             break;                         
	} //ErrDisplay(MyCharToStr (temp, firstOperand, 33, 0));
	if(DivideZero==false)        
	MyCharToStr (digitString, firstOperand, firstOpCount, firstOpFrac);
	operation=operation_none;
	if(operated)  {   //ErrDisplay(MyCharToStr (temp, firstOperand, 33, 0));
	       MemMove(destValue,firstOperand,firstOpCount+firstOpFrac);
	       MemMove(&destValue[MaxDigits],&firstOperand[MaxDigits],1);       
               destOpCount=firstOpCount;
               destOpFrac=firstOpFrac;
        }       
	displayNeedUpdate=true;	
	return(displayNeedUpdate);
}	

static   Boolean    Clear(void) 
{
	FormPtr   form=FrmGetActiveForm(); 
	
        CalcFormInit(form); 
	MemSet(firstOperand ,MaxDigits+1,0);   
	firstOpCount=0;
	firstOpFrac=0;
       	operation=operation_none;
        displayNeedUpdate=true;
        DivideZero=false;
        return(displayNeedUpdate);	
}
	 

static   Boolean    CE(void)
{
	FormPtr   form=FrmGetActiveForm(); 
	Word      count=0;
	
	
	if(operation==operation_none) {
	   Clear();   
	} else {  
                 CalcFormInit(form); 
	         MemSet(destValue,MaxDigits,0);
	         destOpCount = 0;
	         destOpFrac = 0;
               }	       		 
        displayNeedUpdate=true;
        DivideZero=false;
        return(displayNeedUpdate);	
	
}

static   Boolean   Percent()
{   

        if((destOpCount+destOpFrac)==0)         
            return   false;
	if(DivideZero==true) {
	   return false;
	}
            
	if(destOpCount <= 2) {
	   destOpCount=1;
	}   
	else  destOpCount-=2;
        destOpFrac +=2;
	TruncateFraction (destValue, &destOpCount, &destOpFrac);
        
	MyCharToStr (digitString, destValue, destOpCount, destOpFrac);
	
        displayNeedUpdate=true;	
        
        return(displayNeedUpdate);
     	
}	

static   Boolean    BackSpace(void)
{
        
        if((destOpCount+destOpFrac)==0 )  {
             return false;
        }
	if(DivideZero==true) {
	   return false;
	}
	    
        if(destOpFrac)  {  
              MemMove(&destValue[0],&destValue[1],destOpCount+destOpFrac-1);
              destOpFrac--;
        }
        else{ 
		if(fraction)  {
		      	fraction=false;
		      	return   false;
		}      	                
                if(destOpCount)   {
                    MemMove(&destValue[0],&destValue[1],destOpCount+destOpFrac-1);
                    MemSet(&destValue[destOpCount+destOpFrac-1],1,0);
                    destOpCount--;
                }
        }        	       
	MyCharToStr (digitString, destValue, destOpCount, destOpFrac);
	displayNeedUpdate=true;	
        return(displayNeedUpdate);
	
}


static   Boolean    ChangeSign(void)
{   
	if((destOpCount+destOpFrac)==0)
	    return   false;
	if(DivideZero==true) {
	   return false; 
	}
	   
	if(destValue[MaxDigits])  
	     destValue[MaxDigits]=0;
	else destValue[MaxDigits]='-';    	
	 
	MyCharToStr (digitString, destValue, destOpCount, destOpFrac);
	
    	displayNeedUpdate=true;	
        return(displayNeedUpdate);
	
}	 


	
//---------------------------------------------
                         
void    DisplayUpdate(FormPtr  form)
{      
       FieldPtr   fieldP=FrmGetObjectPtr(form,FrmGetObjectIndex(form,DisplayField1098));
      	
       fieldDisplayP=MemHandleLock(fieldDisplayH);	
       StrCopy(fieldDisplayP,digitString);
       MemHandleUnlock(fieldDisplayH);
       FldSetTextHandle(fieldP,(Handle)fieldDisplayH);
       FldDrawField(fieldP);
       	
}	



//********************************************************************************************//

