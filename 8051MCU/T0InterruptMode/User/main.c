#include <REGX52.H>
void Timer0Init()
{
	TMOD &=0xf0;
	TH0 &=0xf0;
	TH0=(65536 - 50000)/256;
	TL0=(65536 - 50000)%256;
	ET0=1;
	EA=1;
	TR0=1;
}
void Timer0isr () interrupt 1
{
	static unsigned char times=0;
	static unsigned char led =0xff;
	tiems++;
	if((times%10)==0)
	{
		led^=0x01;
		LED_dry(led);
	}
	if(times==100)
	{
		led^=0x80;
		LED_dry(led);
		times=0;
	}
}
void main()
{
	BEEP_off();
		AllDT_off();
		LED_dry(0xff);
		Timer0Init();
		LED_en;
		while(1);
}