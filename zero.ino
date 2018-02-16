#include "zero.h"

void setup()
{	
	Serial.begin(115200);
	DBG("booting...");		
	neo_init();
	battery_init();
	compass_init();
	motors_init();
	radar_init();
	servos_init();

	DBG("done\n");
}

void loop()
{
	serial_process();
}