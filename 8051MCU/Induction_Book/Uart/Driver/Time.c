#include "Time.h"
#include "Config.h"
void Cls_Peripheral(void)
{
	P0=0xFF;
	P2=P2 & 0x1F | 0x80;
	P2&=0x1F;
	P0=0;
	P2=P2 & 0x1F | 0xA0;
	P2&= 0x1F;
}
void Led_Disp(unsigned char ucLed)
{
	
	P0=~ucLed;
	P2=P2 & 0x1F | 0x80;
	P2&=0x1F;
}

void Timer1Init(void)
{
	/* STC15F2K60S2: timer1 mode 0 = 16-bit auto reload; 12T -> 1ms tick */
	AUXR &= 0xBF;			/* T1x12 = 0: timer1 runs in 12T mode */
	TMOD &= 0x0F;			/* timer1 mode 0: 16-bit auto reload */
	TH1 = (unsigned char)(TICK_RELOAD >> 8);
	TL1 = (unsigned char)(TICK_RELOAD);
	TF1 = 0;
	TR1 = 1;
	ET1 = 1;
	EA = 1;
}