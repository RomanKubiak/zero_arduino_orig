ARDMK_DIR     		= /usr/share/arduino
ARDUINO_DIR		= /usr/share/arduino-PR-beta1.9-BUILD-34
MONITOR_PORT  		= /dev/ttyUSB0
BOARD_TAG     		= nano
BOARD_SUB		= atmega328
CXXFLAGS        	= -Os
CFLAGS			= -Os -w
ARDUINO_LIBS		= Servo Adafruit_NeoPixel VL53L0X Wire SparkFunBQ27441 lsm303-arduino EEPROM
ARDUINO_SKETCHBOOK	= .
include /usr/share/arduino/Arduino.mk
