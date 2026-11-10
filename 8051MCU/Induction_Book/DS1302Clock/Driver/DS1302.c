#include "DS1302.h"
/*设置时钟*/
void Set_RTC(unsigned char* pucRtc)
{
	unsigned char temp;
	
	Write_Ds1302_Byte(0x8E,0);
	temp=((pucRtc[0]/10)<<4)+pucRtc[0]%10;
	Write_Ds1302_Byte(0x84,0);
	temp=((pucRtc[1]/10)<<4)+pucRtc[0]%10;
	Write_Ds1302_Byte(0x82,0);
	temp=((pucRtc[2]/10)<<4)+pucRtc[0]%10;
	Write_Ds1302_Byte(0x80,temp);
	Write_Ds1302_Byte(0x8E,0x80);
}

/*读取时钟*/
void Read_RTC(unsigned char* pucRtc)
{
	unsigned char temp;
	
	temp=Read_Ds1302_Byte(0x85);
	pucRtc[0]=(temp>>4)*10+(temp&0xf);
	temp=Read_Ds1302_Byte(0x83);
	pucRtc[1]=(temp>>4)*10+(temp&0xf);
	temp=Read_Ds1302_Byte(0x81);
	pucRtc[2]=(temp>>4)*10+(temp&0xf);
}