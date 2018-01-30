#include "zero.h"
#include "motors.h"
#include "radar.h"

Servo servo[4];
Adafruit_NeoPixel neo = Adafruit_NeoPixel(8, NEOPIN, NEO_GRB + NEO_KHZ800);
ZeroMotor lMotor = ZeroMotor("left",  ENA, IN1, IN2);
ZeroMotor rMotor = ZeroMotor("right", ENB, IN3, IN4);
Radar zeroRadar;
ZeroMotors zeroMotors(lMotor,rMotor);

void setup()
{	
	Serial.begin(115200);
	DBG("booting...");	
	neo.begin();
	setup_battery_mon();
	zeroMotors.init();
	zeroRadar.init();

	DBG("done\n");
}

void loop()
{  
}

