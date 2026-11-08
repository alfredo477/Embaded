#include "Time.h"
#include "Seg.h"
#include "Uart.h"
#include <stdio.h>
#include <REGX52.H>

/* Variables shared with the interrupt routines must be volatile,
   otherwise the optimiser may cache them in registers. */
volatile unsigned char ucSec, ucSecL, ucLed;
unsigned char pucSeg_Buf[11], pucSeg_Code[8];
volatile unsigned char ucSeg_Pos;
volatile unsigned char pucUart_Buf[2];
volatile unsigned char ucUart_Num;
volatile unsigned long ulms;

void main(void)
{
	Cls_Peripheral();
	Timer1Init();
	UartInit();

	/* first frame, so the display is never left blank */
	sprintf(pucSeg_Buf, "%08u\r\n", (unsigned int)0);
	Seg_Tran(pucSeg_Buf, pucSeg_Code);

	while(1)
	{
		if(ucSecL != ucSec)			/* once per second */
		{
			ucSecL = ucSec;
			sprintf(pucSeg_Buf, "%08u\r\n", (unsigned int)ucSec);
			Seg_Tran(pucSeg_Buf, pucSeg_Code);
			if(bUartTxFault) pucSeg_Code[7] = 0x86;	/* 'E' = UART not clocking */
			Uart_SendString(pucSeg_Buf);
		}
		if(ucUart_Num == 2)			/* two digits received from the PC */
		{
			ucSec = ((pucUart_Buf[0] - '0') * 10) + pucUart_Buf[1] - '0';
			ucUart_Num = 0;
		}
	}
}

void Time_1(void) interrupt 3
{
	ulms++;
	if(!(ulms % 1000))
	{
		ulms = 0;
		ucSec++;
		ucLed ^= 1;
		Led_Disp(ucLed);
	}
	Seg_Disp(pucSeg_Code, ucSeg_Pos);
	if(++ucSeg_Pos == 8) ucSeg_Pos = 0;
}

void Uart_Routine(void) interrupt 4
{
	if(RI)
	{
		if(ucUart_Num < 2) pucUart_Buf[ucUart_Num++] = SBUF;
		RI = 0;
	}
}
