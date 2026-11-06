#include <REGX52.H>
#include "Seg.h"
#include "Time.h"
#include <stdio.h>

unsigned char ucSec,ucLed;
unsigned char pucSeg_Buf[9],pucSeg_Code[8],ucSeg_Pos;
unsigned int ulms;
void main(void)
{
	Cls_Peripheral();
	Timer1Init();
	
	while(1)
	{
		sprintf(pucSeg_Buf,"  %04u",(unsigned int)ucSec);
		Seg_Tran(pucSeg_Buf,pucSeg_Code);
	}
}
void TIme_1(void) interrupt 3
{
	ulms++;
	if(!(ulms % 1000))
	{
		ucSec++;
		ucLed ^=1;
		Led_Disp(ucLed);
	}
	Seg_Disp(pucSeg_Code, ucSeg_Pos);
	if(++ucSeg_Pos==8)
		ucSeg_Pos=0;
}