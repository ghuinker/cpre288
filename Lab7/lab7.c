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
#include "button.h"
#include <math.h>

int main(void) {
    button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	adc_init();

	lcd_printf("Hello World");

	int value;
	int i;
	int total;
	int distance;


    while(1){
        value = adc_read();
        distance = 276 - (34.1 * log(value));
        lcd_printf("Raw: %d Dist: %d", value, distance);

        for(i =0; i< 1000000; i++){};
    }

//	while(1){
//	    for(i = 0; i < 1000; i++){
//	        total += adc_read();
//	    }
//	    lcd_printf("Average: %d", total/1000);
//
//	    while(!button_getButton()){};
//	    for(i =0; i < 1000000; i++){};
//	    total = 0;
//	}

}
