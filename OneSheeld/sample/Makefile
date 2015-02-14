DIR=$(shell pwd)/../../

INCS = -I.\
    -I$(DIR) \
    -I$(DIR)/hardware \
    -I$(DIR)/hardware/arduino \
    -I$(DIR)/hardware/arduino/cores \
    -I$(DIR)/hardware/arduino/cores/arduino \
    -I$(DIR)/hardware/arduino/variants \
    -I$(DIR)/hardware/arduino/variants/sunxi \
    -I$(DIR)/libraries \
    -I$(DIR)/libraries/Serial \
    -I$(DIR)/libraries/SPI \
	-I$(DIR)/libraries/Wire \
	-I$(DIR)/libraries/LiquidCrystal \
	-I$(DIR)/libraries/PN532_SPI \
	-I$(DIR)/OneSheeld/inc \

LIBS=../bin/OneSheeld.a ../../libarduino.a 
TARGET=./bin

OBJS = Simple/Accelerometer Simple/Buzzer Simple/Camera Simple/DataLogger
OBJS += Simple/Facebook Simple/Foursquare Simple/GamePad Simple/Gravity
OBJS += Simple/Gyroscope Simple/Keypad Simple/Led Simple/Light Simple/Magnetometer
OBJS += Simple/Mic Simple/MusicPlayer Simple/Notification Simple/Orientation
OBJS += Simple/Phone Simple/Proximity Simple/PushButton Simple/Slider
OBJS += Simple/Temperature Simple/Terminal Simple/Twitter Simple/VoiceRecognition
OBJS += Advanced/Accelerometer Advanced/Buzzer Advanced/Camera Advanced/Clock
OBJS += Advanced/Email Advanced/Facebook Advanced/Foursquare Advanced/GamePad
OBJS += Advanced/GPS Advanced/Gravity Advanced/Keypad Advanced/LCD Advanced/Light
OBJS += Advanced/Magnetometer Advanced/Mic Advanced/MusicPlayer Advanced/Notification
OBJS += Advanced/Orientation Advanced/Phone Advanced/Pressure Advanced/Proximity 
OBJS += Advanced/RemoteOneSheeld1 Advanced/RemoteOneSheeld2
OBJS += Advanced/SevenSegment Advanced/Skype Advanced/SMS Advanced/TextToSpeech
OBJS += Advanced/ToggleButton Advanced/VoiceRecognition

all: 
	@mkdir -p $(TARGET)
	@mkdir -p $(TARGET)/Simple
	@mkdir -p $(TARGET)/Advanced
	@for i in $(OBJS); do echo "$(CXX) $(INCS) $$i.c -Wno-write-strings -o $(TARGET)/$$i $(LIBS)" && $(CXX) $(INCS) $$i.c -Wno-write-strings -o $(TARGET)/$$i $(LIBS); done

clean:
	@for i in $(OBJS); do rm -f $(TARGET)/$$i; done
