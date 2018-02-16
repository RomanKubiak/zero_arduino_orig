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
#define RADAR_READ_COUNT	3

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

// radar servo pin
#define RADAR_SERVO		3
// radar center angle for servo
#define RADAR_CENTRE	90

// camera servo1 pin
// camera servo2 pin
#define CAMERA_SERVO1	0
#define CAMERA_SERVO2	0

//#undef DEBUG
#define DEBUG
#ifdef DEBUG
#define DBG(fmt, ...)		printf("DEBUG: %s(): " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define DBG(fmt, ...)
#endif

#define OK(fmt, ...)		printf(":0 " fmt "\n", ##__VA_ARGS__)
#define ERROR(fmt, ...)		printf(":1 " fmt "\n", ##__VA_ARGS__)

#define MOTOR_FORWARD 	1	
#define MOTOR_BACK		0
#define MOTOR_LEFT		1
#define MOTOR_RIGHT		0

#define BATTERY_CAPACITY	6000
#define SERIAL_BUFFER_SIZE	32

// serial port processing functions
void serial_process();
void serial_process_text();
void serial_process_binary();
void serial_rcv(const char end);

// battery mon functions
void battery_init();
void battery_get_stats();

// radar functions
void radar_init();
void radar_get_sweep();
void radar_set_angle(byte angle);
void radar_get_single(const byte with_angle=0);
void radar_sweep();

// servo general functions
void servos_init();

// motor functions
void motors_init();

// neo leds functions
void neo_init();
void neo_set_one(byte index, byte r, byte g, byte b);

// compass functions
void compass_init();
uint16_t compass_get_single();

// binary encode/decode
int encodeTo7(byte* srcBytes, byte* dstBytes, int srcCount);
void decodeFrom7(byte* srcBytes, byte* dstBytes, int dstCount);

// type definitions
struct battery_stats_t
{
	unsigned int soc;
	unsigned int volts;
	int current;
	unsigned int fullCapacity;
	unsigned int capacity;
	int power;
	int health;
	int temperature;
};

struct radar_reading_t
{
	uint16_t distance1;
	uint16_t distance2;
	uint16_t heading;
	byte angle;
};

typedef void (*cmd_callback_t) (const char *args);
struct cmd_t
{
    const char *n PROGMEM;
    cmd_callback_t callback;
};
#endif