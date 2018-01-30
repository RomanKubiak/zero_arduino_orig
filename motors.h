#ifndef _MOTORS_H_
#define _MOTORS_H_
#include "zero.h"

class ZeroMotor
{
    public:
        ZeroMotor(String _motorName, uint8_t _speedPin, uint8_t _dirPin1, uint8_t _dirPin2);
        void setSpeed(uint8_t speed);
        void forward();
        void backward();
        void stop();
        
    private:
        String motorName;
        uint8_t speedPin;
        uint8_t dirPin1;
        uint8_t dirPin2;
        uint8_t currentSpeed;
};

class ZeroMotors
{
    public:
        ZeroMotors(ZeroMotor &_lMotor, ZeroMotor &_rMotor);
        void init();

        ZeroMotor &lMotor;
        ZeroMotor &rMotor;
};

#endif