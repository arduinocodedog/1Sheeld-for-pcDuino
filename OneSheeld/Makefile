#
# Assume standlone toolchain
#
#CC  = arm-linux-gnueabihf-gcc
#CXX = arm-linux-gnueabihf-g++
#AR  = arm-linux-gnueabihf-ar

DIR=$(shell pwd)/../

INCLUDES = \
	-I$(DIR) \
	-I$(DIR)/hardware \
	-I$(DIR)/hardware/arduino \
	-I$(DIR)/hardware/arduino/cores \
	-I$(DIR)/hardware/arduino/cores/arduino \
	-I$(DIR)/hardware/arduino/variants \
	-I$(DIR)/hardware/arduino/variants/sunxi \
	-I$(DIR)/libraries \
	-I$(DIR)/OneSheeld/inc

CFLAGS = -fPIC -DPCDUINO=1 -DARDUINO_LINUX=1
#CFLAGS = $(INCLUDES)
#CFLAGS += -march=armv7-a -mfpu=neon

SRCS = \
	src/AccelerometerSensorShield.cpp \
	src/BuzzerShield.cpp \
	src/CameraShield.cpp \
	src/ClockShield.cpp \
	src/DataLoggerShield.cpp \
	src/EmailShield.cpp \
	src/FacebookShield.cpp \
	src/FoursquareShield.cpp \
	src/GamePadShield.cpp \
	src/GPSShield.cpp \
	src/GravitySensorShield.cpp \
	src/GyroscopeSensorShield.cpp \
	src/KeyboardShield.cpp \
    src/KeypadShield.cpp \
	src/LCDShield.cpp \
	src/LedShield.cpp \
	src/LightSensorShield.cpp \
	src/MagnetometerSensorShield.cpp \
	src/MicShield.cpp \
	src/MusicPlayerShield.cpp \
	src/NotificationShield.cpp \
	src/OneSheeld.cpp \
	src/OneSheeldPrint.cpp \
	src/OneSheeldPrintln.cpp \
	src/OrientationSensorShield.cpp \
	src/PhoneShield.cpp \
	src/PressureSensorShield.cpp \
	src/ProximitySensorShield.cpp \
	src/PushButtonShield.cpp \
	src/RemoteOneSheeld.cpp \
	src/SevenSegmentShield.cpp \
	src/SkypeShield.cpp \
	src/SliderShield.cpp \
	src/SMSShield.cpp \
	src/TemperatureSensorShield.cpp \
	src/TerminalShield.cpp \
	src/ToggleButtonShield.cpp \
	src/TTSShield.cpp \
	src/TwitterShield.cpp \
	src/VoiceRecognitionShield.cpp \
	src/dtostrf.c \

#OBJS = $(SRCS:%.c=%.o)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))

%.o: %.cpp
	@rm -f $@ 
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@ -Wno-deprecated-declarations

%.o: %.c
	@rm -f $@ 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -Wno-deprecated-declarations

LIB_STATIC = bin/OneSheeld.a
LIB_SHARE = bin/OneSheeld.so
LIB = $(LIB_STATIC) $(LIB_SHARE)

all: $(LIB) 
	make -C sample/


$(LIB): $(OBJS)
	$(AR) cq $(LIB_STATIC) $(OBJS)
	$(CXX) -shared -Wl,-soname,$(LIB_SHARE) -o $(LIB_SHARE) $(OBJS)

clean:
	rm -f $(LIB_STATIC) $(LIB_SHARE) $(OBJS)


