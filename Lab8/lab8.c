/**
 * @file lab8_template.c
 * @author
 * Template file for CprE 288 Lab 8
 */

#include "lcd.h"
#include "Timer.h"
#include "ping.h"
#include "resetSimulation.h"

void main()
{
    // Initialize the lcd
    lcd_init();

    // Initialize the ping)))
    ping_init();

    lcd_printf("Something");
    lcd_printf("Test: %f", ping_getDistance());
}
