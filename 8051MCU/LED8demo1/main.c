/*文件名LED8demo1*/
#include <REGX52.H> //包含头文件
//12T单片机演示子程序定义(1ms,@12MHz)
void Delay1ms(sudigned int 1ms)
{
	unsigned char i;
	while(xms--)
		for(i=0;i<123;i++) ;
}
//LED闪烁及流水驱动子程序
void LEDrunning()
{
	unsigned char i;//循环变量定义
	//样式1：闪烁四次
	for(i=0;i<4;i++)
	{
		P1=0x00;       //LED同时亮
		Delay1ms(500); //延时500ms
		P1=0xff;       //LED同时灭
		Delay1ms(500); //延时500ms
	}
	//样式2：向下流水1次
	for(i=0;i<8;i++)
	{
		P1=~(0x01<<i); //向下流水
		Delay1ms(100); //延时100ms
	}
	//样式3：向上流水1次
	for(i=0;i<8;i++)
	{
		P1=~(0x80>>i); //向上流水
		Delay1ms(100); //延时100ms
	}
}
//主函数
void main()
{
	while(1) LEDrunning();//用循环调用LED闪烁及流水驱动子程序
}