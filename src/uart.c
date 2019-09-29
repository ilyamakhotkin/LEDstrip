#include <msp430g2553.h>
#include "uart.h"

extern unsigned char ucPWM_R;
extern unsigned char ucPWM_G;
extern unsigned char ucPWM_B;

void uart_init()
{
	// connect pins to perifiral
	P1SEL  |= P1SEL | 0x06;
	P1SEL2 |= P1SEL | 0x06;
	// set baud rate
	UCA0BR0 = 104;
	UCA0BR1 = 0;
	UCA0MCTL = 0x02;
	// configure perifiral & activate
	UCA0CTL0 = 0;
	UCA0CTL1 = UCSSEL_3;

	IE2 |= UCA0RXIE;
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void UART_RX_ISR(void)
{
	char data = UCA0RXBUF;
	if('0' <= data && data <= '9'){
		// Modify RED LED
		ucPWM_R = data - '0';
	}
	else if ('A' <= data && data <= 'J'){
		// Modify GREEN LED
		ucPWM_G = data - 'A';
	}
	else if ('a' <= data && data <= 'j'){
		// Modify BLUE LED
		ucPWM_B = data - 'a';
	}
	else{
		// Respond that received data didn't match
		data = '?';
	}
	UCA0TXBUF = data; // Send what we received back on UART
}
