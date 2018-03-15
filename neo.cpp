#include "zero.h"

Adafruit_NeoPixel neo = Adafruit_NeoPixel(NEOCOUNT, NEOPIN, NEO_GRB + NEO_KHZ800);

void neo_init()
{
	DBG("starting neo");
	neo.begin();
	for (int i=0; i<NEOCOUNT; i++) 
		neo.setPixelColor(i+1, neo.Color(31,31,23));
	
	neo.show();
}

void neo_set_one(byte index, byte r, byte g, byte b)
{
	neo.setPixelColor(index, neo.Color(r,g,b));
	neo.show();
}