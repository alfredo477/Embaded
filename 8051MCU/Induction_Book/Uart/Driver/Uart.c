#include "Uart.h"
#include "Config.h"

/* MCU: STC15F2K60S2 (green "STC15F2K60S2 -> DIP40" module on the CT107D+).

   UART1 is clocked by Timer2 (AUXR.S1ST2 = 1).  With AUXR.T2x12 = 1 (1T):
       baud rate = FOSC / (4 * (65536 - [T2H,T2L]))
   24 MHz / 9600 bps  ->  reload 64911 = 0xFD8F  (the original value).   */
#define BAUD      9600
#define T2_RELOAD (65536UL - (FOSC / 4UL / BAUD))

/* ~20 ms at 24 MHz: long enough for one byte at 9600 bps, short enough that
   a dead UART can never freeze the main loop (and therefore the display). */
#define TX_TIMEOUT 8000U

bit bUartTxFault = 0;

void UartInit(void)
{
	SCON = 0x50;			/* mode 1, 8-bit UART, REN = 1 */
	AUXR |= 0x01;			/* S1ST2 = 1: UART1 uses Timer2 as baud clock */
	AUXR |= 0x04;			/* T2x12 = 1: Timer2 runs at FOSC (1T mode) */
	T2H = (unsigned char)(T2_RELOAD >> 8);
	T2L = (unsigned char)(T2_RELOAD);
	AUXR |= 0x10;			/* T2R = 1: start Timer2 */
	ES = 1;				/* enable serial port interrupt */
}

void Uart_SendString(unsigned char *pucStr)
{
	unsigned int uiWait;

	while(*pucStr != '\0')
	{
		SBUF = *pucStr;
		uiWait = 0;
		while(TI == 0)
		{
			if(++uiWait > TX_TIMEOUT)
			{
				bUartTxFault = 1;	/* no baud clock: give up, do not hang */
				break;
			}
		}
		TI = 0;
		pucStr++;
	}
}
