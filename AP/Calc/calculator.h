#ifndef  _CALCULATOR_H_
#define  _CALCULATOR_H_ 

//**************************************************************//

void       CalcFormInit(FormPtr  form);
Boolean    TapButton(EventPtr event);

void       DisplayUpdate(FormPtr  form);

Char *MyCharToStr (Char *Dst, Char *Src, int CountLen, int FracLen);
static   Boolean    AppendDigitalNum(char  digit);
static   Boolean    Add(void);
static   Boolean    Subtract(void);
static   Boolean    Multiply(void);
static   Boolean    Divide(void);

static   Boolean    Clear(void); 
static   Boolean    DotPoint(void);
static   Boolean    CE(void);
static   Boolean    Percent(void);
static   Boolean    BackSpace(void);
static   Boolean    ChangeSign(void); 

Boolean    Equal(void);
void       Swap(char *Operand1, Word *OpCount1, Word *OpFrac1, char *Operand2, Word* OpCount2, Word* OpFrac2);
//void       CompareOperands(char *Operand1, Word* OpCount1, Word* OpFrac1,char *Operand2, Word* OpCount2, Word* OpFrac2);

//***************************************************************//
enum {
	operation_none=0,
	operation_add,
	operation_subtract,
	operation_multiply,
	operation_divide
     };	 


#define      Max(x,y)    ((x) > (y)) ? x : y
#define      Min(x,y)    ((x) < (y)) ? x : y 

#endif