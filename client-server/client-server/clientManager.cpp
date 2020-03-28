//
//  clientManager.cpp
//  client-server
//
//  Created by Jaysinh Parmar on 2020-03-17.
//  Copyright © 2020 Jaysinh Parmar. All rights reserved.
//

#include "client.h"
#include <iostream>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <iomanip>

int portnumber;
int transactions = 0;

void printFooter(int transactions){
    std::cout << "Sent " << transactions << " transactions" << std::endl;
}

void printHeader(char *ip_address, char filename[]){
    std::cout << "Using port " << portnumber << std::endl;
    std::cout << "server Address " << ip_address << std::endl;
    std::cout << "Host " << filename << std::endl;
}

void getLine(char *argv[], char filename[]){
    std::string input;
    
    while(true){
        //keep getting input and break when reached the end
        if (std::cin.eof()){
            break;
        }
        std::cin >> input;
        int size_input = (int) input.length();
        char inputC[size_input-1];
        for (int i = 0; i < size_input; i++){
            inputC[i] = input[i+1];
        }
        
        
        if (input[0] == 'S'){
            //prints the time it will sleep for and calls Sleep(int n)
            std::string str2 = input.substr(1,input.length());
            printTime();
            int sleep_count = stoi(str2);
            std::string dummy = " units";
            std::cout << "Sleep ";
            std::cout << sleep_count;
            std::cout << dummy << '\n';
            Sleep(sleep_count);
            
        }else{
            //add transcation count and call the client to send
            //message to server and receive from server
            transactions++;
            clientFun(inputC, argv, filename);
        }
    }
    }
    



int main(int argc, char *argv[]){
    char hostbuffer[256];
    //int hostname;
    char filename[256];
    
    if(argc != 3)
    {
        printf("\n Usage: %s <portnumber> <ip of server> \n",argv[0]);
        return 1;
    }
    //set file name as machinename.pid
    int pid = getpid();
    gethostname(hostbuffer, sizeof(hostbuffer));
    sprintf(filename, "%s.%d", hostbuffer, pid);
    //replace stdout with filename
    freopen(filename, "w", stdout);
    //change the portnumber specified to int
    portnumber = atoi(argv[1]);
    //print the header for output
    printHeader(argv[2], filename);
    //read line and execute the command
    getLine(argv, filename);
    //print summary
    printFooter(transactions);
    //replace STDOUT stream
    fclose(stdout);
    return 0;
}
