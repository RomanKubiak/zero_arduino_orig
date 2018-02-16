#include "zero.h"
#include "commands.h"
#include <EEPROM.h>

VL53L0X lox1 = VL53L0X();
VL53L0X lox2 = VL53L0X();
Servo radar_servo;
struct radar_reading_t radar_reading;
static unsigned long distance1_acc, distance2_acc;
static byte distance1_div, distance2_div;

void radar_init()
{
    pinMode(RADAR_XSHUT1, OUTPUT);
    pinMode(RADAR_XSHUT2, OUTPUT);
    
    DBG("shutting down both sensors");
    digitalWrite(RADAR_XSHUT1, LOW);
    digitalWrite(RADAR_XSHUT2, LOW);
    delay(30);
    
    DBG("booting sensor 1");
    digitalWrite(RADAR_XSHUT1, HIGH);
    delay(30);
    
    DBG("initialize sensor 1 with address 0x32");
    lox1.setAddress(0x32);
    if (!lox1.init())
        ERROR("failed to initialize 2nd radar sensor");
    lox1.setTimeout(10);
    lox1.startContinuous();
    
    DBG("boot up sensor 2");
    digitalWrite(RADAR_XSHUT2, HIGH);
    delay(100);
    lox2.init();
    lox2.setTimeout(10);
    lox2.startContinuous();
    
    radar_servo.attach(RADAR_SERVO);
    radar_set_angle(RADAR_CENTRE);
}

void radar_set_angle(byte angle)
{
    radar_servo.write(angle);
    radar_reading.angle = angle;
}

void radar_get_single(const byte with_angle)
{
    if (with_angle)
	radar_set_angle(with_angle);

    distance1_acc = distance2_acc = 0;
    distance1_div = distance2_div = 0;
    for (int reading=0; reading<RADAR_READ_COUNT; reading++)
    {
        uint16_t distance1 = lox1.readRangeContinuousMillimeters();
        uint16_t distance2 = lox2.readRangeContinuousMillimeters();
    
        if (!lox1.timeoutOccurred())
        {
            distance1_acc += distance1;
            distance1_div++;
        }
                                
        if (!lox2.timeoutOccurred())
        {
            distance2_acc += distance2;
            distance2_div++;
        }
    }
    if (distance1_div)
    {
        radar_reading.distance1 = distance1_acc / distance1_div;
    }
    else
        ERROR("distance sensor 1 no valid readings");
        
    if (distance2_div)
        radar_reading.distance2 = distance2_acc / distance2_div;
    else
	ERROR("distance sensor 2 no valid readings");
    
    radar_reading.heading = compass_get_single();
}

void radar_sweep()
{
    DBG("start");
    int addr = 3;
    char prefix[4] = "swp";
    EEPROM.put(0, prefix);
    for (byte angle=0; angle<15; angle++)
    {
        radar_get_single(angle);
        EEPROM.put(addr, radar_reading);
        addr += sizeof(radar_reading);
    }
    DBG("done");
    radar_get_sweep();
}

void radar_get_sweep()
{
    int addr = 3;
    char prefix[4] = "swp";
    EEPROM.get(0, prefix);
    
    printf(":0:(");
    for (byte angle=0; angle<15; angle++)
    {
        radar_reading_t r;
        EEPROM.get(addr, r);
        printf("a=%d d1=%d d2=%d h=%d, ",r.angle,r.distance1,r.distance2,r.heading);
        addr += sizeof(r);
    }
    printf(")\n");
}