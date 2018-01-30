ARDMK_DIR     		= /usr/share/arduino
MONITOR_PORT  		= /dev/ttyUSB0
BOARD_TAG     		= nano328
CXXFLAGS        	= -Os
CFLAGS			= -Os
ARDUINO_LIBS		= Servo Adafruit_NeoPixel VL53L0X Wire SparkFunBQ27441
ARDUINO_SKETCHBOOK	= .
include /usr/share/arduino/Arduino.mk
