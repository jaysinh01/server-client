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
    //bool cFlag = true;
    while(true){
        //memset(input, '0', sizeof(input));
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
            std::string str2 = input.substr(1,input.length());
            //printTime();
            int sleep_count = stoi(str2);
            std::cout << "Sleep " << sleep_count << " units" << std::endl;
        }else{
            //printTime();
            //std::cout << input << std::endl;
            clientFun(inputC, argv, filename);
        }
    }
    }
    



int main(int argc, char *argv[]){
    char hostbuffer[256];
    //int hostname;
    char filename[256];
    int transactions = 0;
    if(argc != 3)
    {
        printf("\n Usage: %s <portnumber> <ip of server> \n",argv[0]);
        return 1;
    }
    
    int pid = getppid();
    gethostname(hostbuffer, sizeof(hostbuffer));
//    std::cout << "PID: " << pid << std::endl;
    sprintf(filename, "%s.%d", hostbuffer, pid);
//    std::cout << "Filename " << filename << std::endl;
    portnumber = atoi(argv[1]);
//    std::cout << portnumber << std::endl;
//    std::cout << argv[2] << std::endl;
    //freopen(filename,"w",stdout);
    printHeader(argv[2], hostbuffer);
    std::string input;
    //bool cFlag = true;
    while(true){
        //memset(input, '0', sizeof(input));
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
            std::string str2 = input.substr(1,input.length());
            printTime();
            int sleep_count = stoi(str2);
            std::cout << "Sleep " << sleep_count << " units" << std::endl;
        }else{
            //printTime();
            //std::cout << input << std::endl;
            transactions++;
            clientFun(inputC, argv, filename);
        }
    }
    
    printFooter(transactions);
   // fclose(stdout);
    
    return 0;
}
