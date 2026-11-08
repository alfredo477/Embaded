#ifndef _UART_H
#define _UART_H
#include <REGX52.H>

void UartInit(void);
void Uart_SendString(unsigned char *pucStr);

/* 1 = a byte could not be shifted out (the UART baud clock is not running).
   main.c shows an "E" on the last digit, so the fault is visible even
   without a serial terminal. */
extern bit bUartTxFault;

#endif
