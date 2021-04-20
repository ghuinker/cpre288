/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include "button.h"
#include <string.h>


int main (void) {
    button_init();
	timer_init();
	lcd_init();

	servo_init();

	timer_waitMillis(2000);

	servo_move(90);
	timer_waitMillis(500);

	servo_move(30);
	timer_waitMillis(500);

	servo_move(150);
	timer_waitMillis(500);

	servo_move(90);
	timer_waitMillis(500);


}
