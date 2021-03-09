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
#include <string.h>

void lcd_rotatingBanner()
{
    int index = 0;
    int SCREEN_SIZE = 20;
    int size;
    char *val = "Microcontrollers fun!";

    size = strlen(val);

    while(true)
    {
        for(index = SCREEN_SIZE - 1; index > size * -1; index--){
                if(index <= 0){
                    lcd_printf("%.*s", SCREEN_SIZE, val - index);
                }
                else{
                    lcd_printf("%*c%.*s", index, ' ', SCREEN_SIZE - index, val);
                }
                timer_waitMillis(300);
            }
    }

}


int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 

	// Print "Hello, world" on the LCD
	//lcd_printf("Hello, world");

	lcd_rotatingBanner();

	//lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	return 0;
}
