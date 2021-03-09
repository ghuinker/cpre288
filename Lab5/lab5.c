/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 * @author Diane Rover, updated 2/25/2021
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"
#include "uart.h"

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
// PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

//#include "cyBot_FindObjects.h"  // Scan the CyBot sensors to find objects


#define REPLACEME 0

void sendLine(char *str)
{
    int i;
    int len = strlen(str);

    for (i = 0; i < len; i++)
    {
        cyBot_sendByte(str[i]);
    }
    cyBot_sendByte('\r');
    cyBot_sendByte('\n');
}

int main(void)
{
    button_init();
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();


    // initialize the cyBot UART1 before trying to use it

    // (Uncomment ME for UART init part of lab)
    //cyBot_uart_init_clean(); // Clean UART initialization, before running your UART GPIO init code

    // Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART GPIO init code)
    //SYSCTL_RCGCGPIO_R |= 0x01;
    //while ((SYSCTL_PRGPIO_R & 0x10) == 0)
    //{
    //};
    //GPIO_PORTB_DEN_R |= 0x03;
    //GPIO_PORTB_AFSEL_R |= 0x03;
    //GPIO_PORTB_PCTL_R &= 0x00000011;     // Force 0's in the desired locations
    //GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
    // Or see the notes for a coding alternative to assign a value to the PCTL field

    // (Uncomment ME for UART init part of lab)
    //cyBot_uart_init_last_half();  // Complete the UART device configuration
    uart_init();

    // YOUR CODE HERE
    sendLine("Let's get it started");
    while (1)
    {

        uart_sendStr("Waiting for input");
        char buffer[21];
        int i = 0;
        char c = 0;
        buffer[20] = '\0';
        for (i = 0; i < 20; i++)
        {
            c = uart_receive();
            uart_sendChar(c);
            if (c == '\r')
            {
                uart_sendChar('\n');
                buffer[i] = '\0';
                break;
            }
            buffer[i] = c;
        }
        if(c != '\r'){
            uart_sendStr("\r\n");
        }
        lcd_printf(buffer);
    }

}
