/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity,  COM1

#define REPLACEME 0


int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	cyBot_uart_init();          // Don't forget to initialize the cyBot UART before trying to use it

	// YOUR CODE HERE

	char c = cyBot_getByte();
	lcd_printf("Received: %c", c);

	uint8_t button;
	while(1)
	{

      // YOUR CODE HERE
  
	    button = button_getButton();
//	    lcd_printf("Button %d", button);
	    if(button){
	        cyBot_sendByte((char) button + 48);
	    }

	
	}
	
}
