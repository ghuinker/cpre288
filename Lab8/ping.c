/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "ping.h"
#include "Timer.h"

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse

#include "driverlib/interrupt.h"

void ping_init (void){

  // YOUR CODE HERE
    SYSCTL_RCGCGPIO_R |= 0x02;
    SYSCTL_RCGCTIMER_R |= 0x08;

    while ((SYSCTL_RCGCGPIO_R & 0x02) == 0)
    {
    };
    while ((SYSCTL_RCGCTIMER_R & 0x08) == 0)
    {
    };

    GPIO_PORTB_DIR_R |= 0x08;
    GPIO_PORTB_DEN_R |= 0x08;
    GPIO_PORTB_AFSEL_R |= 0x08;
    GPIO_PORTB_PCTL_R |= 0x7000;

    TIMER3_CTL_R &= 0xFEFF;
    TIMER3_CFG_R = 0x04;
    TIMER3_TBMR_R |= 0x0017;
    TIMER3_CTL_R |= 0xC00;
    TIMER3_TBPR_R = 0x00FF;
    TIMER3_TBILR_R = 0x0FFF;
    TIMER3_IMR_R |= 0x400;

    NVIC_EN1_R |= 0x10;

    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    IntMasterEnable();

    // Configure and enable the timer
    TIMER3_CTL_R |= 0x0100;
}

void ping_trigger (void){
    STATE = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= 0xFEFF;
    TIMER3_IMR_R &= ~0x400;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= ~0x08;

    // YOUR CODE HERE FOR PING TRIGGER/START PULSE

    // SOmething with GPIO_PORTB_DATA_R

    timer_waitMicros(5);

    // SOMETHING with GPIO_PORTB_DATA_R

    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0x0400;
    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x08;
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;
}

void TIMER3B_Handler(void){

}

float ping_getDistance (void){

}


