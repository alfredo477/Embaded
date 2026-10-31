#include <Seg.h>
//段码 决定数码管内部 体现数字 一个数码管内部有七根 右下角一点 对应八个码 从最顶部顺时针依次为abcdef 中间为g 右下角为dp 
//若要显示6 则0111 1101 对应显示亮部为 acdefg 从左往右 对应数码管亮的
unsigned char Seg_Dula[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
unsigned char Seg_Wela[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};//位码：决定哪个数码管亮 0xfe表示1111 1110 在P0.0索引处 需要与实际电路板相关 

/* 数码显示函数*/
void Seg_Disp{unsigned char wela,dula}
{
	P0=0x00;//消影 让段码和位码清零 全灭
	P2_6=1;//段码锁存器一直打开 P0是啥 存储就是啥
	P2_6=0;//只有在P2_6从1->0的时候 锁住此刻的P0
	
	P0=Seg_Wela[wela];//先选位码 不然先选段码会出现重影
	P2_7=1;//位码锁存器
	P2_7=0;
	
	P0=Seg_Dula[dula];
	P2_6=1;
	P2_6=0;
}