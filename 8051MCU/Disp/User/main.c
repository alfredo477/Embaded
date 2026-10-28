/*文件名Disp.c*/
#include <REGX52.H>
sbit LED_B0 =P1^0;
sbit LED_B1 =P1^1;
sbit LED_B2 =P1^2;
sbit LED_B3 =P1^3;
unsigned char LOOpcnt=0;
/*12T单片机延时子程序定义（1ms,@12MHz）*/
void Delay1ms(unsigned int xms)
{
	unsigned char i;
	while(xms--)
		for(i=0;i<123;i++);
}
/*主函数*/
void main()
{
	while(1)
	{	
		LOOPcnt++;
		Delay1ms(500);
		LED_B0=~LED_B0;
		if((LOOPcnt%2)==0) LED_B1=~LED_B1;
		if((LOOPcnt%4)==0) LED_B2=~LED_B2;
		if((LOOPcnt%8)==0)
			{
				LED_B3=~LED_B3;
				LOOPcnt=0;
			}
	}
}