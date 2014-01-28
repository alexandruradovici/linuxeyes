SDK_LIB=library
SDK_INC=include

CC 		= g++ -g -Wno-deprecated -w
LIBRARIES	= -L$(SDK_LIB) -lcurses -lpthread -ldl -lz -lbass -lwiringPi
INCLUDES	= -I$(SDK_INC)

xmp: xmp.cpp inc/*.cpp inc/help/*.cpp generators/*.pas generators/help.le generators/le_data.build
	./generators/le_ver
	./generators/le_help
	$(CC) $< $(INCLUDES) $(LIBRARIES) -o $@

play:
	LD_LIBRARY_PATH=. ./xmp

playvumeterleds:
	sudo LD_LIBRARY_PATH=. VUMETER=LEDS LEDS=10 ./xmp

playvumeterrgb:
	sudo LD_LIBRARY_PATH=. VUMETER=LED_RGB LED_RGB=10 ./xmp

playvumeters:
	sudo LD_LIBRARY_PATH=. VUMETER=LEDS_LED_RGB LEDS=10 LED_RGB=10 ./xmp

