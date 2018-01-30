#include "motors.h"

ZeroMotor::ZeroMotor(String _motorName, uint8_t _speedPin, uint8_t _dirPin1, uint8_t _dirPin2)
    : motorName(_motorName), speedPin(_speedPin), dirPin1(_dirPin1), dirPin2(_dirPin2)
{
    pinMode(speedPin, OUTPUT);
    pinMode(dirPin1, OUTPUT);
    pinMode(dirPin2, OUTPUT);
    
    stop();
}

void ZeroMotor::setSpeed(uint8_t speed)
{
    analogWrite(speedPin, speed);
    currentSpeed = speed;
}

void ZeroMotor::forward()
{
    digitalWrite(dirPin1,HIGH);
    digitalWrite(dirPin2,LOW);
}

void ZeroMotor::backward()
{
    digitalWrite(dirPin1,LOW);
    digitalWrite(dirPin2,HIGH);
}

void ZeroMotor::stop()
{
    DBG("now");
    setSpeed(0);
    digitalWrite(dirPin1,LOW);
    digitalWrite(dirPin2,LOW);
}

ZeroMotors::ZeroMotors(ZeroMotor &_lMotor, ZeroMotor &_rMotor)
    : lMotor(_lMotor), rMotor(_rMotor)
{
}

void ZeroMotors::init()
{
    DBG("initializing motors");
    lMotor.stop();
    rMotor.stop();
}

