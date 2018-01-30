#ifndef _ZERO_H_
#define _ZERO_H_
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <VL53L0X.h>
#include <SparkFunBQ27441.h>
#include "stdinout.h"

// radar
#define RADAR_XSHUT1		4
#define	RADAR_XSHUT2		7

// neopixel
#define NEOPIN			2

// left motor
#define ENB			10 // 13
#define IN3	 		A1  // 20
#define IN4			A0  // 19

// right motor
#define ENA			11 // 14
#define IN1			12 // 15
#define IN2			13 // 16


#define DBG(fmt, ...)		printf("%s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define OK(fmt, ...)		printf(":0 " fmt "\n", ##__VA_ARGS__)
#define ERROR(fmt, ...)		printf(":1 " fmt "\n", ##__VA_ARGS__)

void setup_battery_mon(void);
void setup_motors(void);
void setup_radar(void);
#endif