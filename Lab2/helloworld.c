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
#include "movement.h"
#include "open_interface.h"
#include "resetSimulation.h"
#include <string.h>

int main(void)
{
    resetSimulationBoard();

    timer_init(); // Initialize Timer, needed before any LCD screen functions can be called
                  // and enables time functions (e.g. timer_waitMillis)

    lcd_init();   // Initialize the LCD screen.  This also clears the screen.

    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()

    oi_init(sensor_data); // do this only once at start of main()

//	move_forward(sensor_data, 500);
//	turn_left(sensor_data, 90);
//	move_forward(sensor_data, 500);
//	turn_left(sensor_data, 90);
//	move_forward(sensor_data, 500);
//	turn_left(sensor_data, 90);
//	move_forward(sensor_data, 500);
    double dist=0;
    int GOAL_DISTANCE = 2000;
    int MOVE_BACKWARD = 150;
    bool is_left;

    while (dist < GOAL_DISTANCE)
    {
        lcd_printf("Moving forward");
        if ((dist += move_forward(sensor_data, (GOAL_DISTANCE - dist))) < GOAL_DISTANCE)
        {
            lcd_printf("Moved: %.2f", dist/10);
            is_left = !!sensor_data->bumpLeft;
            move_backward(sensor_data, MOVE_BACKWARD);
            dist -= MOVE_BACKWARD;
            if (is_left)
            {
                turn_right(sensor_data, 90);
                move_forward(sensor_data, 250);
                turn_left(sensor_data, 90);
            }
            else
            {
                turn_left(sensor_data, 90);
                move_forward(sensor_data, 250);
                turn_right(sensor_data, 90);
            }
        }
    }
    lcd_printf("Finished: %.2f", dist/10);
    oi_free(sensor_data); // do this once at end of main()

    return 0;
}
