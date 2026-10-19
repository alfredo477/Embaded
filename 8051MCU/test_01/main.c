/* 头文件区域 */
#include <REGX52.H>
#include <intrins.h>
/* 延时函数 */
 void Delay(unsigned char xms)	//@12.000MHz
{
	unsigned char data i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
  }
}
/* 变量申明区域 */
unsigned char ucLed=0xfe;
unsigend char Key_Val,Key_Down,Key_Up,Key_Old;
bit System_Flag;
unsigned int time;

/*按键读取函数 */
unsigned char Key_Read()
{
	unsigned char temp=0;
	P3_0=0;P3_1=1;P3_2=1;P3_3=1;
	if(P3_4==0) temp=1;
	if(P3_5==0) temp=2;
	if(P3_6==0) temp=3;
	if(P3_7==0) temp=4;
	P3_0=1;P3_1=0 ;P3_2=1;P3_3=1;
	if(P3_4==0) temp=5;
	if(P3_5==0) temp=6;
	if(P3_6==0) temp=7;
	if(P3_7==0) temp=8;
	P3_0=1;P3_1=1;P3_2=0;P3_3=1;
	if(P3_4==0) temp=9;
	if(P3_5==0) temp=10;
	if(P3_6==0) temp=11;
	if(P3_7==0) temp=12;
	P3_0=1;P3_1=1;P3_2=1;P3_3=0;
	if(P3_4==0) temp=13;
	if(P3_5==0) temp=14;
	if(P3_6==0) temp=15;
	if(P3_7==0) temp=16;
	return temp;
}

/* Main */
void main()
	{	
		while(1)
		{
			Key_Val=Key_Read();//读取键码值
			Key_Down=Key_Val & (Key_Val ^ Key_Old);//检测下降沿
			Key_Up=Key_Val & (Key_Val ^ Key_Old);//检测上升沿
			Key_Old=Key_VAL;//扫描辅助变量
			
			if(System_Flag==1)
				{
					ucLed=_crol_(ucLed,1);
					P1=ucLed;
					Delay(100);
				}
			switch(Key_Down)
				{
					case 1:
						System_Flag=1;
					break;
					case 2:
						System_Flag=0;
					break;
					case 3:
						Time-=100;
					break;
				}
			/*if(Key_Down==1)
				P1_0=0;
			if(Key_Ip==2)
				P1_0=1;
			if(Key_Old==3)
				P1_1=0;
			else
				P1_1=1;*/
		}
	}
	
 
	