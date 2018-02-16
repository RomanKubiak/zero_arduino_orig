#include "zero.h"

static bool battery_ok = false;
struct battery_stats_t battery_stats;

void battery_init(void)
{
  DBG("battery");
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

void battery_stats_read(void)
{
  battery_stats.soc = lipo.soc();  // Read state-of-charge (%)
  battery_stats.volts = lipo.voltage(); // Read battery voltage (mV)
  battery_stats.current = lipo.current(AVG); // Read average current (mA)
  battery_stats.fullCapacity = lipo.capacity(FULL); // Read full capacity (mAh)
  battery_stats.capacity = lipo.capacity(REMAIN); // Read remaining capacity (mAh)
  battery_stats.power = lipo.power(); // Read average power draw (mW)
  battery_stats.health = lipo.soh(); // Read state-of-health (%)
  battery_stats.temperature = lipo.temperature();
}

void battery_get_stats(void)
{
  if (!battery_ok)
  {
    ERROR("battery mon not initialized");
    return;
  }
  else
  {
    battery_stats_read();
    DBG("soc=%d,volts=%d,current=%d,fullcap=%d,cap=%d,power=%d,health=%d,temp=%d",
      battery_stats.soc, 
      battery_stats.volts, 
      battery_stats.current, 
      battery_stats.fullCapacity, 
      battery_stats.capacity, 
      battery_stats.power, 
      battery_stats.health, 
      battery_stats.temperature);
  }
}
