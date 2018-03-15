#ifndef _ZERO_H_
#define _ZERO_H_
#include <Adafruit_NeoPixel.h>
#include <VL53L0X.h>
#include <SparkFunBQ27441.h>

#include "stdinout.h"

// heartbeat
#define HEARTBEAT_LED_PIN	A3
#define HEARTBEAT_INTERVAL	240

// radar
#define RADAR_XSHUT1		4
#define	RADAR_XSHUT2		7
#define RADAR_SERVO		6
#define RADAR_CENTRE		10
#define RADAR_READ_COUNT	2
#define RADAR_EEPROM_START	0
#define RADAR_SWEEP_ANGLE	120
 
// neopixel
#define NEOPIN			2
#define NEOCOUNT		10

// motors
#define MOTOR_DIR_FORWARD 	0
#define MOTOR_DIR_BACK		1
#define MOTOR_LEFT		1
#define MOTOR_RIGHT		0
#define MOTOR_RIGHT_SPEED_PIN	3
#define MOTOR_RIGHT_DIR1_PIN	A1
#define MOTOR_RIGHT_DIR2_PIN	A0
#define MOTOR_LEFT_SPEED_PIN	11
#define MOTOR_LEFT_DIR1_PIN	12
#define MOTOR_LEFT_DIR2_PIN	13

// camera servo1 pin
// camera servo2 pin
#define CAMERA_SERVO_TILT	5
#define CAMERA_SERVO_PAN	10
#define CAMERA_INITIAL_PAN	150
#define CAMERA_INITIAL_TILT	80 

//#undef DEBUG
#define DEBUG
#ifdef DEBUG
#define DBG(fmt, ...)		printf("# %s(): " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define DBG(fmt, ...)
#endif

#define OK(fmt, ...)		printf(":0 " fmt "\n", ##__VA_ARGS__)
#define ERROR(fmt, ...)		printf(":1 " fmt "\n", ##__VA_ARGS__)

#define BATTERY_CAPACITY	6000
#define SERIAL_BUFFER_SIZE	32
#define SERVO_FRAME_MILLIS	20

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
void radar_sweep(uint8_t start=4, uint8_t end=172, uint8_t delay_per_sample=1, uint8_t samples_per_angle=2);

// camera general functions
void camera_init();
void camera_set(int pan_deg, int tilt_deg);

// motor functions
void motors_init();
void motor_set_speed(bool motor, byte speed);
void motor_set_direction(bool motor, bool direction);
void motor_stop(bool motor);
 
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