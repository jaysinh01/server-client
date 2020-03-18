

CXXFLAGS =	-O0 -g -Wall -fmessage-length=0 -std=c++11

server:	server.cpp
	g++ $(CXXFLAGS) server.cpp -o server

client:	clientManager.cpp
	g++ $(CXXFLAGS) clientManager.cpp -o client

all:	server client

clean:
	rm -f server client

kill:
	pkill -u jaysinh

