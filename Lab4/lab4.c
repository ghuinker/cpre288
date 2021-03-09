/**
 * lab3_template.c
 *
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"
#include "cyBot_FindObjects.h" // Functions for communicating between CyBot and Putty (via UART)
// PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity,  COM1
#include <string.h>
#include "movement.h"
#include "resetSimulation.h"

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

int findObjects(oi_t *sensor_data, cyBot_Object_t objects[], int size_of_input)
{
    int SIZE = 10;
    int found1, found2, i = 0;
    cyBot_Object_t temp[SIZE];
    cyBot_Object_t temp2[SIZE];
    found1 = cyBot_FindObjects(temp, SIZE);
    turn_right(sensor_data, 180);
    found2 = cyBot_FindObjects(temp2, SIZE);

    for (i = 0; i < found2; i++)
    {
        temp2[i].angle += 180;
    }

    for (i = 0; i < found1; i++)
    {
        objects[i] = temp[i];
    }
    for (i = 0; i < found2; i++)
    {
        objects[i + found1] = temp2[i];
    }

    turn_left(sensor_data, 180);
    return found1 + found2;
}

void sendObjectList(cyBot_Object_t objects[], int object_count)
{
    char output[100];
    char *format_string = "%d\t%d\t%f\t%f";

    sendLine("Object#\tAngle\tDistance\tWidth");

    int i = 0;

    for (i = 0; i < object_count; i++)
    {
        sprintf(output, format_string, i, objects[i].angle, objects[i].distance,
                objects[i].width);
        sendLine(output);
    }
}

void turn_to(oi_t *sensor_data, int degrees)
{
    if (degrees < 90)
    {
        return turn_left(sensor_data, 90 - degrees);
    }
    else
    {
        return turn_right(sensor_data, degrees - 90);
    }
}

void move_to(oi_t *sensor_data, int mm)
{
    double dist = 0;
    int MOVE_BACKWARD = 150;
    bool is_left;

    while (dist < mm)
    {
        lcd_printf("Moving forward");
        if ((dist += move_forward(sensor_data, (mm - dist)))
                < mm)
        {
            lcd_printf("Moved: %.2f", dist / 10);
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
}

int main(void)
{
    int OBJECTS_SIZE = 50;
    cyBot_Object_t objects[OBJECTS_SIZE];
    int object_count;

    resetSimulationBoard();

    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    cyBot_uart_init(); // Don't forget to initialize the cyBot UART before trying to use it

    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()

    oi_init(sensor_data); // do this only once at start of main()

    // Get Objects
    object_count = findObjects(sensor_data, objects, OBJECTS_SIZE);

    if (object_count == 0)
    {
        sendLine("No Objects detected");
        return 0;
    }

    // Print object list
    sendObjectList(objects, object_count);

    // Find smallest object
    cyBot_Object_t *target = &objects[0];

    int i;
    for (i = 1; i < object_count; i++)
    {
        if (objects[i].width < target->width)
            target = &objects[i];
    }

    lcd_printf("%f, %d", sensor_data->angle, target->angle);

    turn_to(sensor_data, target->angle);

    move_to(sensor_data, (int) (target->distance * 10));

}
