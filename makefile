CFLAGS = -g

all: qSim

qSim: qSim.o Event.o EventQueue.o CustomerEvent.o TellerEvent.o TellerQueue.o
	g++ $(CFLAGS) -Wall qSim.o Event.o EventQueue.o CustomerEvent.o TellerEvent.o TellerQueue.o -o qSim

qSim.o: qSim.cpp
	g++ $(CFLAGS) -Wall -c qSim.cpp

Event.o: Event.cpp Event.h EventQueue.h
	g++ $(CFLAGS) -Wall -c Event.cpp

EventQueue.o: EventQueue.cpp EventQueue.h Event.h
	g++ $(CFLAGS) -Wall -c EventQueue.cpp

CustomerEvent.o: CustomerEvent.cpp CustomerEvent.h Event.h
	g++ $(CFLAGS) -Wall -c CustomerEvent.cpp

TellerEvent.o: TellerEvent.cpp TellerEvent.h Event.h
	g++ $(CFLAGS) -Wall -c TellerEvent.cpp

TellerQueue.o: TellerQueue.cpp TellerQueue.h Event.h EventQueue.h  TellerEvent.h
	g++ $(CFLAGS) -Wall -c TellerQueue.cpp

docs:
	doxygen

clean:
	rm -f qSim.o Event.o EventQueue.o TellerEvent.o CustomerEvent.o TellerQueue.o qSim
