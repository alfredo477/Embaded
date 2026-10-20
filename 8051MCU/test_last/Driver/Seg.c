#include <Seg.h>

unsigned char Seg_Dula[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};//数码管段码存储数组 0x00是芯片
unsigned char Seg_Wela[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};//数码管位码存储数组

/*数码显示函数*/
void Seg_Disp(unsigned char wela,dula)
{
	//P2_6是位码 P2_7是断码 先位选再段选
	P0=0x00;//输入数据
	P2_6=1;//打开锁存器存入数据 
	P2_6=0;//关闭锁存器锁住旧数据
	
	P0=Seg_Wela[wela];
	P2_7=1;
	P2_7=0;
	
	P0=Seg_Dula[dula];
	P2_6=1;
	P2_6=0;
}