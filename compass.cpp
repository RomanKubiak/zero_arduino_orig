#include "zero.h"
#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

void compass_init()
{
	DBG("start compass");
	compass.init();
 	compass.enableDefault();
 	compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
 	compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
}

uint16_t compass_get_single()
{
	compass.read();
	uint16_t heading = compass.heading();
	return (heading);
}
