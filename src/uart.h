#ifndef UART_H_
#define UART_H_

#include <msp430g2452.h>
//#include "main.h"

//public function declarations
void uart_init();
void uart_send_char(char data);

#endif /* UART_H_ */
