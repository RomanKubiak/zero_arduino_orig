#include "zero.h"

void motor_set_speed(uint8_t motor, uint8_t speed)
{
    if (motor)
        analogWrite(ENA, speed);
    else
	analogWrite(ENB, speed);
}

void motor_set_direction(uint8_t motor, uint8_t direction)
{
    if (motor)
    {
        digitalWrite(IN1, direction);
        digitalWrite(IN2, !direction);
    }
    else
    {
        digitalWrite(IN3, direction);
        digitalWrite(IN4, !direction);
    }
    
}

void motor_stop(uint8_t motor)
{
    motor_set_speed(motor,0);
    if (motor)
    {
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,LOW);
    }
    else
    {
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,LOW);
    }
}

void motors_init()
{
    DBG("initializing motors");
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}
