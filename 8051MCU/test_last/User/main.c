/*头文件声明区域*/
#include <REGX52.H>
#include <Key.h>

/*变量声明区域*/
unsigned char Key_Slow_Down;//按键减速专用变量 10ms
unsigned int Seg_Slow_Down;//数码管减速专用变量 500ms
unsigned char Key_Val,Key_Down,Key_Old;//按键扫描专用变量
unsigned char Seg_Pos;//数码管扫描变量
unsigned char Seg_Buf[6]={10，10，10，10，10，10};//数码管显示数据存放数组
unsigned char Seg_Mode;//数码管显示界面 0-显示 1-设置
unsigned int Timer_1000ms;//1000ms标志位
unsigned char Time_Count;//系统计时变量

/* 按键处理函数 */
void Key_Proc()
{
	if(Key_Slow_Down) return;
	Key_Slow_Down=1;//按键减速程序
	
	Key_Val=Key_Read();//读取按下的键码值
	Key_Down=Key_Val&(Key_Val^Key_Old);//捕捉下降沿
	Key_Old=Key_Val;//辅助扫描
	
	switch(Key_Down)
	{
		
	}
}

/*信息处理函数*/
void Seg_Proc()
{
	if(Seg_Slow_Down) return;
	Seg_Slow_Down=1;//数码管减速程序
	
	Seg_Buf[0]=Seg_Mode+1;
	if(Seg_Mode==0)//系统处于显示界面
	{
		
	}
}

/*其他显示函数*/
void Led_Proc()
{
	
}


/*定时器0初始化函数*/
void Timer0_Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0=1;
	EA=1;
}
/* 定时器0中断服务函数 */
void TImer0Server() interrupt 1
{
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	if(++Key_Slow_Down==10) Key_Slow_Down=0;
	if(++Seg_Slow_Down==500) Seg_Slow_Down=0;
	if(++Seg_Pos==6) Seg_Pos=0;
	Seg_Disp(Seg_Pos,Seg_Buf[Seg_Pos]);
}



/* Main */
void main()
{
	Timer0_Init();
	while(1)
	{
		Key_Proc();
		Seg_Proc();
		Led_Proc();
	}
}