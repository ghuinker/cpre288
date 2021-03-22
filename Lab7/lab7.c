/**
 * lab6-interrupt_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "adc.h"


int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	adc_init();

	lcd_printf("Hello World");

	int value;
	int i;

	while(1){
	    value = adc_read();
	    lcd_printf("%d", value);

	    for(i =0; i< 100000; i++){};
	}

}
