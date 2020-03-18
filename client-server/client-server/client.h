//
//  client.h
//  client-server
//
//  Created by Jaysinh Parmar on 2020-03-18.
//  Copyright © 2020 Jaysinh Parmar. All rights reserved.
//

#ifndef client_h
#define client_h
#include "client.cpp"
#include "TandS.cpp"

//prints the current epoch time
void printTime();

//takes in work to send, the ip to send at, and the hostname & pid aka filename
//send the work to server and recieves the completion message
int clientFun(char work[], char *ip[], char filename[]);

//CLIENTMANAGER

//prints header in the output file
void printHeader(char *ip_address, char filename[]);

//reads the input and calls sleep if sleep command or
//client if TXXX
void getLine();



#endif /* client_h */
