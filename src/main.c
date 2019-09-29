#include <msp430g2553.h>
#include "uart.h"

#define LED_R BIT3
#define LED_G BIT4
#define LED_B BIT5
#define LED_R_ON()  P1OUT |=  LED_R
#define LED_G_ON()  P1OUT |=  LED_G
#define LED_B_ON()  P1OUT |=  LED_B
#define LED_R_OFF() P1OUT &= ~LED_R
#define LED_G_OFF() P1OUT &= ~LED_G
#define LED_B_OFF() P1OUT &= ~LED_B
#define LED_OFF() P1OUT &= ~(LED_R | LED_G | LED_B)
#define LED_ON()  P1OUT |=  (LED_R | LED_G | LED_B)

unsigned char ucPWM_Counter;
unsigned char ucPWM_R;
unsigned char ucPWM_G;
unsigned char ucPWM_B;

void timer_init()
{
	TA0CCR0 = 0x0800;
	TA0CTL= TASSEL_2 | ID_0 | MC_1 | TACLR | TAIE;
}

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	P1DIR = (LED_R | LED_G | LED_B);// Set P1.0 to output direction
	P1OUT = 0;
	P1DIR |= BIT0;					// Set P1.0 to output direction
	uart_init();
	timer_init();
	
	ucPWM_R = 5;
	ucPWM_G = 5;
	ucPWM_B = 5;
	ucPWM_Counter = 0;

	_BIS_SR(GIE);
	LPM0;

	volatile int i = 0;
	while(1)
		i++;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void PWM2(void)
{
	TACTL &= ~TAIFG;
	P1OUT |= BIT0;
	ucPWM_Counter++;
	if (ucPWM_Counter == ucPWM_R)
		LED_R_OFF();
	if (ucPWM_Counter == ucPWM_G)
		LED_G_OFF();
	if (ucPWM_Counter == ucPWM_B)
		LED_B_OFF();
		
	if (ucPWM_R == 0)
		LED_R_OFF();
	if (ucPWM_G == 0)
		LED_G_OFF();
	if (ucPWM_B == 0)
		LED_B_OFF();

	if (ucPWM_Counter == 10)
	{
		if (ucPWM_R != 0)
			LED_R_ON();
		if (ucPWM_G != 0)
			LED_G_ON();
		if (ucPWM_B != 0)
			LED_B_ON();
		ucPWM_Counter = 0;
	}
	P1OUT &= ~BIT0;
}
