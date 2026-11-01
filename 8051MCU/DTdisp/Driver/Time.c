#include "Time.h"
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
	/* AT89C52 无 AUXR 寄存器，定时器固定 12T 模式，与 AUXR&=0xBF 效果相同 */
	/* AUXR &= 0xBF; */
	TMOD &=0x0F;
	TL1 =0x18;
	TH1 =0xFC;
	TF1 =0;
	TR1 =1;
	ET1 =1;
	EA =1;
}