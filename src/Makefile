SDK_LIB=library
SDK_INC=include

CC 		= g++ -g -Wall -Wno-deprecated
LIBRARIES	= -L$(SDK_LIB) -lcurses -lxaudio -ldl
INCLUDES	= -I$(SDK_INC)

xmp: xmp.cpp inc/*.cpp inc/help/*.cpp $(SDK_LIB)/libxaudio.a generators/*.pas generators/help.le generators/le_data.build
	./generators/le_ver
	./generators/le_help
	$(CC) $< $(INCLUDES) $(LIBRARIES) -o $@
