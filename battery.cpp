#include "zero.h"

const unsigned int BATTERY_CAPACITY = 6000; // e.g. 850mAh battery
static bool battery_ok = false;

void setup_battery_mon(void)
{
  if (!lipo.begin()) // begin() will return true if communication is successful
  {
    ERROR("Failed to initialize battery monitor");
    battery_ok = false;
  }
  else
  {
    DBG("Battery mon initialized");  
    lipo.setCapacity(BATTERY_CAPACITY);
    battery_ok = true;
  }
}

void get_battery_stats(void)
{
  if (!battery_ok)
  {
    ERROR("battery mon not initialized");
    return;
  }
  // Read battery stats from the BQ27441-G1A
  unsigned int soc = lipo.soc();  // Read state-of-charge (%)
  unsigned int volts = lipo.voltage(); // Read battery voltage (mV)
  int current = lipo.current(AVG); // Read average current (mA)
  unsigned int fullCapacity = lipo.capacity(FULL); // Read full capacity (mAh)
  unsigned int capacity = lipo.capacity(REMAIN); // Read remaining capacity (mAh)
  int power = lipo.power(); // Read average power draw (mW)
  int health = lipo.soh(); // Read state-of-health (%)
  int temperature = lipo.temperature();
  
  OK("soc=%d,volts=%d,current=%d,fullcap=%d,cap=%d,power=%d,health=%d,temp=%d",
      soc, volts, current, fullCapacity, capacity, power, health, temperature);
}
