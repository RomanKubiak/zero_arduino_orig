#include "zero.h"

Servo servo[4];
Adafruit_NeoPixel neo = Adafruit_NeoPixel(8, NEOPIN, NEO_GRB + NEO_KHZ800);

void setup()
{	
	Serial.begin(115200);
	DBG("booting...");	

	neo.begin();
	battery_init();
	motors_init();
	radar_init();
	servos_init();

	DBG("done\n");
}

void loop()
{
	serial_process();
}