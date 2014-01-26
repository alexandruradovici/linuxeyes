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

playvumeter:
	sudo LD_LIBRARY_PATH=. VUMETER=1 LEDS=10 ./xmp
