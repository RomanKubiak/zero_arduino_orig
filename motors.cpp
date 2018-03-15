#include "zero.h"

void motor_set_speed(bool motor, byte speed)
{
    DBG("%s speed: %d", (motor == MOTOR_LEFT) ? "left " : "right", speed);
    if (motor == MOTOR_LEFT)
        analogWrite(MOTOR_LEFT_SPEED_PIN, speed);
    else
	analogWrite(MOTOR_RIGHT_SPEED_PIN, speed);
}

void motor_set_direction(bool motor, bool direction)
{
    DBG("%s direction: %s", (motor == MOTOR_LEFT) ? "left " : "right", (direction == MOTOR_DIR_FORWARD) ? "forward" : "backward");
    if (motor == MOTOR_LEFT)
    {
        digitalWrite(MOTOR_LEFT_DIR1_PIN, direction);
        digitalWrite(MOTOR_LEFT_DIR2_PIN, !direction);
    }
    else
    {
        digitalWrite(MOTOR_RIGHT_DIR1_PIN, direction);
        digitalWrite(MOTOR_RIGHT_DIR2_PIN, !direction);
    }
    
}

void motor_stop(bool motor)
{
    DBG("%s stop", (motor == MOTOR_LEFT) ? "left " : "right");
    motor_set_speed(motor,0);
    if (motor == MOTOR_LEFT)
    {
        digitalWrite(MOTOR_LEFT_DIR1_PIN, LOW);
        digitalWrite(MOTOR_LEFT_DIR2_PIN, LOW);
    }
    else
    {
        digitalWrite(MOTOR_RIGHT_DIR1_PIN, LOW);
        digitalWrite(MOTOR_RIGHT_DIR2_PIN, LOW);
    }
}

void motors_init()
{
    DBG("initializing motors");
    pinMode(MOTOR_LEFT_SPEED_PIN, OUTPUT);
    pinMode(MOTOR_RIGHT_SPEED_PIN, OUTPUT);
    pinMode(MOTOR_LEFT_DIR1_PIN, OUTPUT);
    pinMode(MOTOR_LEFT_DIR2_PIN, OUTPUT);
    pinMode(MOTOR_RIGHT_DIR1_PIN, OUTPUT);
    pinMode(MOTOR_RIGHT_DIR2_PIN, OUTPUT);
    
    motor_stop(MOTOR_LEFT);
    motor_stop(MOTOR_RIGHT);
}
