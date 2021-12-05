CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude 
LDFLAGS:=-lboost_system -lboost_thread -pthread
# All Targets
all: bin/BGRSclient

bin/BGRSclient: bin/BGRSclient.o bin/Protocol.o bin/MessageEncoderDecoder.o bin/connectionHandler.o 
	@echo 'Building target: BGRSclient'
	@echo 'Invoking: C++ Linker'
	g++ -Wall -Weffc++ -o bin/BGRSclient bin/BGRSclient.o bin/Protocol.o bin/MessageEncoderDecoder.o bin/connectionHandler.o  $(LDFLAGS)
	@echo 'Finished building target: BGRSclient'
	@echo ' '


bin/BGRSclient.o: src/BGRSclient.cpp
	g++ $(CFLAGS) $(LDFLAGS) -o bin/BGRSclient.o src/BGRSclient.cpp

bin/Protocol.o: src/Protocol.cpp
	g++ $(CFLAGS) -o bin/Protocol.o src/Protocol.cpp

bin/MessageEncoderDecoder.o: src/MessageEncoderDecoder.cpp
	g++ $(CFLAGS) -o bin/MessageEncoderDecoder.o src/MessageEncoderDecoder.cpp
	
bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) $(LDFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp
	
clean:
	rm -f bin/*
