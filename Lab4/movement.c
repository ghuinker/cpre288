/*
 * movement.c
 *
 *  Created on: Feb 9, 2021
 *      Author: ghuinker
 */
#include "open_interface.h"



double  move_forward (oi_t  *sensor_data,   double distance_mm)
{
    double sum = 0;
    oi_setWheels(250,250); //move forward at full speed
    while (sum < distance_mm) {
        oi_update(sensor_data);
        sum += sensor_data -> distance; // use -> notation since pointer
        if(sensor_data->bumpLeft || sensor_data->bumpRight){
            return sum;
        }
    }
    oi_setWheels(0,0); //stop
    return sum;
}

double move_backward (oi_t  *sensor_data,   double distance_mm)
{
    double sum = 0;
    oi_setWheels(-500,-500); //move forward at full speed
    while (sum > distance_mm * -1) {
        oi_update(sensor_data);
        sum += sensor_data -> distance; // use -> notation since pointer
    }
    oi_setWheels(0,0); //stop
    return sum;
}

void turn_right(oi_t  *sensor, double degrees)
{
    double sum = 0;

    oi_setWheels(150, -150);
    while (sum < degrees){
        oi_update(sensor);
        sum += sensor->angle;
        // TODO: Slow down if close
    }
    oi_setWheels(0,0);
    return;
}

void turn_left(oi_t  *sensor, double degrees)
{
    double sum = 0;
    oi_setWheels(-150, 150);
    while (sum < degrees){
        oi_update(sensor);
        sum -= sensor->angle;
        // TODO: Slow down if close
    }
    oi_setWheels(0,0);
    return;
}

