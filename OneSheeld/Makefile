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
	src/ColorShield.cpp \
	src/DataLoggerShield.cpp \
	src/EmailShield.cpp \
	src/FacebookShield.cpp \
	src/FoursquareShield.cpp \
	src/GamePadShield.cpp \
	src/GLCDAnalogGauge.cpp \
	src/GLCDButton.cpp \
	src/GLCDCheckBox.cpp \
	src/GLCDEllipse.cpp \
	src/GLCDLine.cpp \
	src/GLCDPoint.cpp \
	src/GLCDProgressBar.cpp \
	src/GLCDRadioButton.cpp \
	src/GLCDRectangle.cpp \
	src/GLCDShield.cpp \
	src/GLCDSlider.cpp \
	src/GLCDTextBox.cpp \
	src/GPSShield.cpp \
	src/GravitySensorShield.cpp \
	src/GyroscopeSensorShield.cpp \
	src/HttpRequest.cpp \
	src/HttpResponse.cpp \
	src/InternetShield.cpp \
	src/JsonKey.cpp \
	src/JsonKeyChain.cpp \
	src/KeyboardShield.cpp \
    src/KeypadShield.cpp \
	src/LCDShield.cpp \
	src/LedShield.cpp \
	src/LightSensorShield.cpp \
	src/MagnetometerSensorShield.cpp \
	src/MicShield.cpp \
	src/MusicPlayerShield.cpp \
	src/NFCRecord.cpp \
	src/NFCShield.cpp \
	src/NFCTag.cpp \
	src/NotificationShield.cpp \
	src/OneSheeld.cpp \
	src/OneSheeldPrint.cpp \
	src/OneSheeldPrintln.cpp \
	src/OrientationSensorShield.cpp \
	src/PatternShield.cpp \
	src/PhoneShield.cpp \
	src/PressureSensorShield.cpp \
	src/ProximitySensorShield.cpp \
	src/PushButtonShield.cpp \
	src/SevenSegmentShield.cpp \
	src/ShapeClass.cpp \
	src/ShieldParent.cpp \
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
TARGET = ./bin

%.o: %.cpp
	@rm -f $@ 
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@ -Wno-deprecated-declarations -Wno-conversion-null

%.o: %.c
	@rm -f $@ 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -Wno-deprecated-declarations

LIB_STATIC = $(TARGET)/OneSheeld.a
LIB_SHARE = $(TARGET)/OneSheeld.so
LIB = $(LIB_STATIC) $(LIB_SHARE)

all: $(LIB)
	make -C sample/

$(LIB): $(OBJS)
	mkdir -p $(TARGET)
	$(AR) cq $(LIB_STATIC) $(OBJS)
	$(CXX) -shared -Wl,-soname,$(LIB_SHARE) -o $(LIB_SHARE) $(OBJS)

clean:
	rm -f $(LIB_STATIC) $(LIB_SHARE) $(OBJS)


