#include "zero.h"
#include <Servo.h>

Servo pan,tilt;

void camera_set_pan(int deg)
{
    pan.attach(CAMERA_SERVO_PAN);
    delay(50);
    pan.write(deg);
    delay(150);
    pan.detach();
}

void camera_set_tilt(int deg)
{
    tilt.attach(CAMERA_SERVO_TILT);
    delay(50);
    tilt.write(deg);
    delay(150);
    tilt.detach();
}

void camera_init()
{
    DBG("camera attach servos");
    pan.attach(CAMERA_SERVO_PAN);
    delay(100);
    tilt.attach(CAMERA_SERVO_TILT);
    delay(100);
    camera_set_pan(CAMERA_INITIAL_PAN);
    camera_set_tilt(CAMERA_INITIAL_TILT);
    delay(500);
    pan.detach();
    tilt.detach();
}

void camera_set(int pan_deg, int tilt_deg)
{
    camera_set_pan(pan_deg);
    camera_set_tilt(tilt_deg);
}
