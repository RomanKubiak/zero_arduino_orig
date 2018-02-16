#ifndef _COMMANDS_H_
#define _COMMANDS_H_
#include "zero.h"

void command_servo_move(const char *args);
void command_motor_set(const char *args);
void command_radar_set_angle(const char *args);
void command_radar_get_one(const char *args);
void command_radar_sweep(const char *args);
void command_battery_get_status(const char *args);
void command_scan_iic(const char *args);
void command_neo(const char *args);
void command_head(const char *args);
void command_process(char *command_token);

const struct cmd_t commands[] = 
{ 
    {
    	n 			: "batt",
    	callback 	: command_battery_get_status 
    },
    {
    	n 			: "rdr",
    	callback 	: command_radar_get_one
    },
    {
    	n		    : "rdra",   
    	callback	: command_radar_set_angle
    },
    {
    	n 			: "iic",
    	callback 	: command_scan_iic
    }
    ,
    {
    	n 			: "neo",
    	callback	: command_neo
    },
    {
    	n 			: "head",
    	callback	: command_head
    },
    {
    	n		: "swep",
    	callback	: command_radar_sweep
    },
    { 
    	NULL 
    }
};

#endif