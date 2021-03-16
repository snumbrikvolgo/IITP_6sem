CXX=g++
INCLUDES=./
CXXFLAGS=-Wall -O3 -g -std=c++11

scenario : scenario.o server.o queue.o simulator.o packet.o
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -o scenario scenario.o server.o queue.o simulator.o packet.o

server.o: server.cpp server.h
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -c server.cpp

queue.o: queue.cpp queue.h packet.h simulator.h traced-callback.h
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -c queue.cpp
simulator.o: simulator.cpp simulator.h
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -c simulator.cpp
packet.o: packet.cpp packet.h
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -c packet.cpp
clean:
	rm -rf *.o scenario
