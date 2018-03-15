#include "commands.h"
#include <Wire.h>

extern struct radar_reading_t radar_reading;
void command_process(char *command_string)
{
	const char *command_token = strtok(command_string, ":");
	if (command_token == NULL)
	{
		ERROR("can't tokenize command string");
		return;
	}
	const struct cmd_t *ptr = commands;
	const struct cmd_t *end = &commands[sizeof(commands) / sizeof(commands[0]) - 1];

	do
	{
		if (!strcmp(ptr->n, command_token))
		{
			ptr->callback(command_token);
			break;
		}

	} while(ptr++ < end);	
}

void command_battery_get_status(const char *args)
{
}

void command_radar_get_one(const char *args)
{
	radar_get_single();
	OK("angle=%d distance1=%d distance2=%d",
		radar_reading.angle,
		radar_reading.distance1,
		radar_reading.distance2);
}

void command_camera_set(const char *args)
{
	const int pan 	= atoi(strtok(NULL,":"));
	const int tilt 	= atoi(strtok(NULL,":"));
	camera_set(pan, tilt);
}


void command_motor_set(const char *args)
{
	const bool idx = atoi(strtok(NULL,":")) ? MOTOR_LEFT : MOTOR_RIGHT;
	const bool dir = atoi(strtok(NULL,":")) ? MOTOR_DIR_FORWARD : MOTOR_DIR_BACK;
	const byte spd = atoi(strtok(NULL,":"));
	
	motor_set_direction(idx, dir);
	motor_set_speed(idx,spd);
}

void command_radar_set_angle(const char *args)
{
	radar_set_angle(atoi(strtok(NULL, ":")));
}

void command_radar_sweep(const char *args)
{
	const uint8_t start 	= atoi(strtok(NULL,":"));
	const uint8_t end	= atoi(strtok(NULL,":"));
	const int d		= atoi(strtok(NULL,":"));
	const uint8_t samples	= atoi(strtok(NULL,":"));
	radar_sweep(start,end,d,samples);
}

void command_scan_iic(const char *args)
{
	byte error, address;
	
	for(address = 1; address < 127; address++ )
  	{
    	Wire.beginTransmission(address);
    	error = Wire.endTransmission();
 
    	if (error == 0)
    	{
    		DBG("[OK:0x%x]", address);
    	}
    	if (error == 4)
    	{
    		DBG("[ERR:0x%x]", address);
    	}
    }
}

void command_neo(const char *args)
{
	const byte idx = atoi(strtok(NULL,":"));
	const byte r = atoi(strtok(NULL,":"));
	const byte g = atoi(strtok(NULL,":"));
	const byte b = atoi(strtok(NULL,":"));
	neo_set_one(idx,r,g,b);
}

void command_head(const char *args)
{
	OK("%du", compass_get_single());
}

void command_analog_write(const char *args)
{
	const int pin = atoi(strtok(NULL, ":"));
	const int val = atoi(strtok(NULL, ":"));
	DBG("pin=%d val=%d", pin, val);
	analogWrite(pin, val);
}

void command_digital_write(const char *args)
{
	const int pin = atoi(strtok(NULL, ":"));
	const int val = atoi(strtok(NULL, ":"));
	DBG("pin=%d val=%d", pin, val);
	digitalWrite(pin, val);
}