/*头文件声明区域*/
#include <REGX52.H>
#include "Key.h"
#include "Seg.h"

/* 变量声明区域 */
//按键减速专用变量10ms 来消抖 振动会对单片机产生十几次信号 需要延迟来确认信号
unsigned char Key_Slow_Down;
unsigned char Seg_Slow_Down;
unsigned char Key_Val,Key_Down,Key_Old;


/* 按键处理函数 */
//Key_Read返回数值之后需要对应的反应 此处为进入不同模式
void Key_Proc()
{
	//Key_Slow_Down作为全局变量默认初值为0 
	//在定时器中断服务函数里面会有if(++Key_Slow_Down==10) Key_Slow_Down=0; return是跳出此函数并不带出额外值 实现10ms来检查一次此函数
	if(Key_Slow_Down) return;
	Key_Slow_Down=1;
	
	Key_Val=Key_Read();
	//Key_Down表示下降沿(只有在按下才会显示) 只有当前值为1 并且历史值为0时 才是下降
	Key_Down=Key_Val&(Key_Val^Key_Old);//捕捉下降沿
	Key_Old=Key_Val;
	
	switch(Key_Down)
	{
		case 1:
			if()
	}
}