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

OBJS = Simple/Accelerometer Simple/BarcodeScanner Simple/Buzzer Simple/Camera Simple/Color 
OBJS += Simple/DataLogger Simple/Facebook Simple/Foursquare Simple/GamePad Simple/GLCD 
OBJS += Simple/Gravity Simple/Gyroscope Simple/Internet Simple/Keyboard Simple/Keypad 
OBJS += Simple/Led Simple/Light Simple/Magnetometer Simple/Mic Simple/MusicPlayer 
OBJS += Simple/NFC Simple/Notification Simple/Orientation Simple/Pattern
OBJS += Simple/Phone Simple/Proximity Simple/PushButton Simple/Slider
OBJS += Simple/Temperature Simple/Terminal Simple/Twitter Simple/Vibration Simple/VoiceRecognition
OBJS += Advanced/Accelerometer Advanced/BarcodeScanner Advanced/Buzzer Advanced/Camera 
OBJS += Advanced/Clock Advanced/Color Advanced/Email Advanced/Facebook Advanced/Foursquare 
OBJS += Advanced/GamePad Advanced/GLCD Advanced/GPS Advanced/Gravity Advanced/Internet 
OBJS += Advanced/Keypad Advanced/LCD Advanced/Light Advanced/Magnetometer Advanced/Mic 
OBJS += Advanced/MusicPlayer Advanced/NFC Advanced/Notification
OBJS += Advanced/Orientation Advanced/Phone Advanced/Pressure Advanced/Proximity 
OBJS += Advanced/SevenSegment Advanced/Skype Advanced/SMS Advanced/TextToSpeech
OBJS += Advanced/ToggleButton Advanced/Twitter Advanced/Vibration Advanced/VoiceRecognition

all: 
	@mkdir -p $(TARGET)
	@mkdir -p $(TARGET)/Simple
	@mkdir -p $(TARGET)/Advanced
	@for i in $(OBJS); do echo "$(CXX) $(INCS) $$i.c -DPCDUINO=1 -DINCLUDE_INTERNET_SHIELD=1 -Wno-write-strings -o $(TARGET)/$$i $(LIBS)" && $(CXX) $(INCS) $$i.c -DPCDUINO=1 -DINCLUDE_INTERNET_SHIELD -Wno-write-strings -o $(TARGET)/$$i $(LIBS); done

clean:
	@for i in $(OBJS); do rm -f $(TARGET)/$$i; done
