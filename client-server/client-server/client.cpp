// From: www.thegeekstuff.com/2011/12/c-socket-programming
// Note that port# 5000 is hard-coded into this implementation

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>
#include <sys/time.h>
#include <iomanip>

extern int portnummber;

//prints current epoch time with two decimals
void printTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long double secondsEpoch =
        (long double)(tv.tv_sec) +
        (long double)(tv.tv_usec) / 10000;
    
    std::cout << std::setprecision(2) << std::fixed << secondsEpoch << ": ";
}


int clientFun(char work[], char *ip[], char filename[])
{
    
    int sockfd = 0, n = 0;
    char recvBuff[1024], sendBuff[256];
    struct sockaddr_in serv_addr; 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    //converting char* IP to unsined short IP
    unsigned short vOut = (unsigned short)strtol(ip[1],NULL,10);
    serv_addr.sin_port = htons(vOut);

    if(inet_pton(AF_INET, ip[2], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }
    
    memset(sendBuff, '0', sizeof(sendBuff));
   //fomatting a message "machinename.pid-transaction"
    sprintf(sendBuff, "%s-%s", filename, work);
    //Print the transaction to be sent
    printTime();
    std::cout << "Send " << "(T" <<  std::setfill (' ') << std::setw (3) << work << ")" << std::endl;
    send(sockfd, sendBuff, sizeof(sendBuff), 0);
    
        //print the completion message recieved
        while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
        {
            recvBuff[n] = 0;
            if (recvBuff[0] == 'D'){
                printTime();
                std::cout << "Recv " << "(" << std::setfill (' ') << std::setw (3) <<recvBuff << ")" << std::endl;
            }

        }

    return 0;
}
