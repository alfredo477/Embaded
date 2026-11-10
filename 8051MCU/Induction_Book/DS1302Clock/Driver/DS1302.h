void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte(unsigned char addr,unsigned char dat);
unsigned char Read_Ds1302_Byte(unsigned char addr);

void Set_RTC(unsigned char* pucRtc);
void Read_RTC(unsigned char* pucRtc);