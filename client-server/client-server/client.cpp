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



int clientFun(char work[], char *ip[])
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
    serv_addr.sin_port = htons(12000);

    if(inet_pton(AF_INET, ip[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }
    
    int pid = getppid();
    memset(sendBuff, '0', sizeof(sendBuff));
   
    sprintf(sendBuff, "%d.%s", pid, work);
    
        
        //sockfd = socket(AF_INET, SOCK_STREAM, 0);
        //connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        send(sockfd, sendBuff, sizeof(sendBuff), 0);
//        printf("58");
        while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
        {
            recvBuff[n] = 0;
            if(fputs(recvBuff, stdout) == EOF)
            {
                printf("\n Error : Fputs error\n");
            }
        }

        if(n < 0)
        {
            printf("\n Read error \n");
        }
        //close(sockfd);
    

    return 0;
}
