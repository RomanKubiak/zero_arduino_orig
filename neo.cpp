#include "zero.h"

Adafruit_NeoPixel neo = Adafruit_NeoPixel(8, NEOPIN, NEO_GRB + NEO_KHZ800);

void neo_init()
{
	DBG("starting neo");
	neo.begin();
	neo.setPixelColor(0, neo.Color(16,16,16));
	neo.setPixelColor(1, neo.Color(64,64,64));
	neo.setPixelColor(2, neo.Color(64,64,64));
	neo.setPixelColor(3, neo.Color(64,64,64));
	neo.setPixelColor(4, neo.Color(16,16,16));
	neo.show();
}

void neo_set_one(byte index, byte r, byte g, byte b)
{
	DBG("index=%d r=%d g=%d b=%d", index, r, g, b);
	neo.setPixelColor(index, neo.Color(r,g,b));
	neo.show();
}