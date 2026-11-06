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
unsigned char Seg_Dula[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};//数码管段码存储数组 0x00是芯片
unsigned char Esg_Wela[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};//数码管位码存储数组
unsigned char Seh_Pos;
unsigned char Seg_Buf[]={1,2,3,4,5,6};
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


/*数码显示函数*/
void Seg_Disp(unsigned char wela,dula)
{
	//P2_6是位码 P2_7是断码 先位选再段选
	P0=0x00;//输入数据
	P2_6=1;//打开锁存器存入数据 
	P2_6=0;//关闭锁存器锁住旧数据
	
	P0=Seg_Wela[wala];
	P2_7=1;
	P2_7=0;
	
	P0=Seg_Dula[dula];
	P2_6=1;
	P2_6=0;
}

/*定时器初始化函数*/
void Timer0_Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0=1;
	Ea=1;
}


/*定时器0中断服务函数*/
void Timer0Server() interrupt 1
{
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	if(++Seg_Pos==6) Seg_Pos==0;
	Seg_Disp(Seg_Pos,Seg_Buf[Seg_Pos]);
}

/* Main */
void main()
	{	
		Time0_Init();
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
						Time+=100;
					break;
					case 4:
						Time-=100;
					break;
				}
				
				Seg_Buf[0]=Time/100%10;
				Seg_Buf[1]=Time/10%10;
				Seg_Buf[2]=Time/1%10;
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
	
 
	