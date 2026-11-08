#ifndef _CONFIG_H
#define _CONFIG_H

/* ------------------------------------------------------------------------
   This board is a CT107D+ with the green "STC15F2K60S2 -> DIP40" module
   plugged into the MCU socket, so the real chip is an STC15F2K60S2
   (1T 8051 family), NOT an AT89C52.  The Keil "Device" setting only picks
   the register header, it does not tell you what is soldered on the board.

   REGX52.H does not describe the STC15 SFRs, so the few extras are
   declared here.  If you install the official STC15F2K60S2.H and include
   it instead, delete the three "sfr" lines below to avoid a redefinition.
   ------------------------------------------------------------------------ */
sfr AUXR = 0x8E;	/* b0 S1ST2, b2 T2x12, b4 T2R, b6 T1x12 */
sfr T2H  = 0xD6;	/* Timer2 high byte (also the reload value) */
sfr T2L  = 0xD7;	/* Timer2 low byte  (also the reload value) */

/* IRC frequency that STC-ISP uses when downloading the program.
   The original UART code (T2H/T2L = 0xFD8F for 9600) was generated for
   24 MHz, so that is the default here.
   If the seconds counter runs twice as fast as a real clock, the chip is
   actually at 12 MHz: change this to 12000000UL (both the UART baud rate
   and the 1 ms tick are derived from it). */
#define FOSC 24000000UL

/* Timer1 tick = 1 ms with Timer1 in 12T mode:
   1 count takes 12/FOSC seconds, so 1 ms needs FOSC/12000 counts. */
#define TICK_RELOAD (65536UL - (FOSC / 12000UL))

#endif
