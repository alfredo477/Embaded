#ifndef _KEY_H
#define _KEY_H
#include "REGX52.H"

/* STC89C52RC: P4 is at 0xC0; AT89C52/REGX52.H does not declare P4 */
sfr  P4  = 0xC0;
sbit P44 = P4^4;
sbit P42 = P4^2;
sbit P34 = P3^4;
sbit P35 = P3^5;

unsigned char Key_Read(void);
#endif