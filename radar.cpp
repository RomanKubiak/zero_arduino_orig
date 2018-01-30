#include "radar.h"

VL53L0X lox1 = VL53L0X();
VL53L0X lox2 = VL53L0X();

void Radar::init()
{
    DBG("enter");
    pinMode(RADAR_XSHUT1, OUTPUT);
    pinMode(RADAR_XSHUT2, OUTPUT);
    
    DBG("shutting down both sensors");
    digitalWrite(RADAR_XSHUT1, LOW);
    digitalWrite(RADAR_XSHUT2, LOW);
    delay(10);
    
    DBG("booting up all sensors");
    digitalWrite(RADAR_XSHUT1, HIGH);
    digitalWrite(RADAR_XSHUT2, HIGH);
    delay(10);
    
    DBG("shutting down 1st sensor");
    digitalWrite(RADAR_XSHUT1, LOW);
    delay(2);
    
    DBG("initialize sensor 2 with address 0x32");
    lox2.setAddress(0x32);
    if (!lox2.init())
        ERROR("failed to initialize 2nd radar sensor");
    else
    {
        DBG("sensor 2 initialized");
        lox2.setTimeout(500);
        lox2.setSignalRateLimit(0.1);
        lox2.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
        lox2.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
        lox2.setMeasurementTimingBudget(20000);
    }
    delay(2);
    
    DBG("bring up sensor 1");
    digitalWrite(RADAR_XSHUT1, HIGH);
    delay(2);
    
    DBG("initialize sensor 1 with address 0x31");
    lox1.setAddress(0x31);
    if (!lox1.init())
        ERROR("failed to initialize 1st radar sensor");
    else
    {
        DBG("sensor 1 initialized");
        lox1.setTimeout(500);
        lox1.setSignalRateLimit(0.1);
        lox1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
        lox1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
        lox1.setMeasurementTimingBudget(20000);
    }
}

void Radar::getSingle()
{
    int lox1Read = lox1.readRangeSingleMillimeters();
    int lox2Read = lox2.readRangeSingleMillimeters();
    
    if (lox1.timeoutOccurred())
        DBG("timeout occured for radar sensor 1");
    if (lox2.timeoutOccurred())
        DBG("timeout occured for radar sensor 2");
        
    OK("sens1=%d,sens2=%d", lox1Read, lox2Read);
}