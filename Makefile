# Project: GoPiGo

OBJ_OS = OS/linux.o
OBJ_COMMON = Common/board.o Common/pindevs.o
OBJ_DEVICES = Devices/encoders.o Devices/led.o Devices/servo.o Devices/trimcontrol.o Devices/ultrasonic.o Devices/wheels.o

OBJ = $(OBJ_OS) $(OBJ_COMMON) $(OBJ_DEVICES)
LINKOBJ = $(OBJ)
LIBS = 
BIN  = libGoPiGo.a
CXXINCS = 
CXXFLAGS = $(CXXINCS) -std=c++11 -fexceptions -O2
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean:
	${RM} $(LINKOBJ) $(BIN)

$(BIN): $(LINKOBJ)
	ar r $(BIN) $(LINKOBJ)
	ranlib $(BIN)

OS/linux.o: OS/linux.cpp
	$(CXX) -c OS/linux.cpp -o OS/linux.o $(CXXFLAGS)

Common/board.o: Common/board.cpp
	$(CXX) -c Common/board.cpp -o Common/board.o $(CXXFLAGS)

Common/pindevs.o: Common/pindevs.cpp
	$(CXX) -c Common/pindevs.cpp -o Common/pindevs.o $(CXXFLAGS)

Devices/encoders.o: Devices/encoders.cpp
	$(CXX) -c Devices/encoders.cpp -o Devices/encoders.o $(CXXFLAGS)

Devices/led.o: Devices/led.cpp
	$(CXX) -c Devices/led.cpp -o Devices/led.o $(CXXFLAGS)

Devices/servo.o: Devices/servo.cpp
	$(CXX) -c Devices/servo.cpp -o Devices/servo.o $(CXXFLAGS)

Devices/trimcontrol.o: Devices/trimcontrol.cpp
	$(CXX) -c Devices/trimcontrol.cpp -o Devices/trimcontrol.o $(CXXFLAGS)

Devices/ultrasonic.o: Devices/ultrasonic.cpp
	$(CXX) -c Devices/ultrasonic.cpp -o Devices/ultrasonic.o $(CXXFLAGS)

Devices/wheels.o: Devices/wheels.cpp
	$(CXX) -c Devices/wheels.cpp -o Devices/wheels.o $(CXXFLAGS)
