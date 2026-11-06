#include "Time.h"
#include "Seg.h"
#include "Key.h"

unsigned char ucSec,ucLed;
unsigned char ucKey_Dly,ucKey_Old;
unsigned char pucSeg_Buf[8],pucSeg_Code[8],ucSeg_Pos;
unsigned long ulms,ulKey_Time;

void Key_Proc(void);
void SEG_Proc(unsigned char ucSeg_Val);

void main(void)
{
	Cls_Peripheral();
	Timeer1Init();
	
	while(1)
	{
		Key_Proc();
		Seg_Tran(pucSeg_Buf,pucSeg_Code);
	}
}

void Time_1(void) interrupt 3
{
	ulms++;
	if(++ucKey_Dly == 10)
		ucKey_Dly=0;
	if(!(ulms%1000))
	{
		ucSec++;
		ucLed ^=1;
		Led_Disp(ucLed);
	}
	Seg_Disp(pucSeg_Code,ucSeg_Pos);
	if(++ucSeg_Pos==8) 
		ucSeg_Pos=0;
}


void()