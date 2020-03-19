

CXXFLAGS =	-O0 -g -Wall -fmessage-length=0 -std=c++11


serverpdf:	server.1
	man -t ./server.1 > server.1.ps
	
clientpdf:	client.1
	man -t ./client.1 > client.1.ps
	
pdf:	serverpdf clientpdf

server:	server.cpp
	g++ $(CXXFLAGS) server.cpp -o server

client:	clientManager.cpp
	g++ $(CXXFLAGS) clientManager.cpp -o client

all:	server client pdf

clean:
	rm -f server client server.1.ps client.1.ps

kill:
	pkill -u jaysinh

