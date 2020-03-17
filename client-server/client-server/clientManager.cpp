//
//  clientManager.cpp
//  client-server
//
//  Created by Jaysinh Parmar on 2020-03-17.
//  Copyright © 2020 Jaysinh Parmar. All rights reserved.
//

#include "clientManager.hpp"
#include "client.cpp"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[]){
    
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }
    
    
    char input[100];
   
    bool cFlag = true;
    
    while(cFlag){
        //memset(input, '0', sizeof(input));
        std::cin >> input;
        if (strcmp(input, "exit") == 0){
            break;
        }
        clientFun(input, argv);
    }
    
    return 0;
}
