/*头文件声明区域*/
#include <REGX52.H>
#include <Key.h>

/*变量声明区域*/
unsigned char Key_Slow_Down;//按键减速专用变量 10ms
unsigned int Seg_Slow_Down;//数码管减速专用变量 500ms
unsigned char Key_Val,Key_Down,Key_Old;//按键扫描专用变量
unsigned char Seg_Pos;//数码管扫描变量
unsigned char Seg_Buf[6]={10，10，10，10，10，10};//数码管显示数据存放数组 初始化全部是10表示全灭
unsigned char Seg_Mode;//数码管显示界面 0-显示 1-设置
unsigned int Timer_1000ms;//1000ms标志位
unsigned char Time_Count;//系统计时变量
bit System_Flag;//系统标志位 0-暂停 1-开始
unsigned char Set_Dat[3]={15,30,60};//设置参数存储数组
unsigned char  Set_Dat_Index=1;//参数存储数组里面的变量
unsigned int Timer_500ms;//500ms为标志位 1s作为周期
bit Seg_Flag;//数码管标志位

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
		case 1://启动倒计时
			if(Seg_Mode==0)
				System_Flag=1;
		break;
		case 3://切换到设置界面
			if(Seg_Mode==1)//已经在设置界面之后再点击则保存值
				Time_Count=Set_Dat[Set_Dat_Index];
			Seg_Mode ^=1;
		break;
		case 4:
			if(Seg_Mode==1)
			{
				if(++ Set_Dat_Index==3)//在参数存储值里面进行选择
				 Set_Dat_Index=0;
			}
		break;
		case 2:
			if(Seg_Mode==0)	
				Time_Count=Set_Dat[Set_Dat_Index];//不在设置界面则复位
		break;
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
		Seg_Buf[4]=Time_Count / 10 % 10; //
		Seg_Buf[5]=Time_Count % 10;
	}
	else//在系统处于设置界面
	{
		if(Seg_Flag==1)
		{
			Seg_Buf[4]=Set_Dat[Set_Dat_Index] / 10 % 10; //显示十位
			Seg_Buf[5]=Set_Dat[Set_Dat_Index] % 10;//显示个位
		}
		else
		{
			Seg_Buf[4]=10;//Seg_Buf为数码管显示一共有六个 第五个熄灭
			Seg_Buf[5]=10;//第六个熄灭
		}
	}
}

/*其他显示函数*/
void Led_Proc()
{
	if(Time_Count==0)
	{
		P1=0x00;//LEDP1口全亮
		P2_3=0;//蜂鸣器为0
	}
	else
	{
		P1=0xff;
		P2_3=1;
	}
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
	if(System_Flag==1)
	{
		if (++TImer_1000ms==1000)//作为计时器记到1000ms 为1s
		{
			Timer_1000ms=0;//重新计时
			Time_Count--;
			//Time_Count类型是unsigned cahr在0-255之间 原本的Time_Count减到0之后会回到255
			if(Time_Count==255)//这样就可以一直卡在0
				Time_Count=0;
		}
	}
	if(++Timer_500ms==500)
	{
		TImer_500ms=0;
		Seg_Flag ^=1
	}
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