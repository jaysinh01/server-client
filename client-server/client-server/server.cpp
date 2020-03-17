// From: www.thegeekstuff.com/2011/12/c-socket-programming
// Note that port# 5000 is hard-coded into this implementation

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <iostream>
#include <sys/poll.h>

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    struct pollfd fds[200];
    int    nfds = 1;
    int    timeout;
    int rc;
    //int n = 0;

    char sendBuff[1025];
    char recvBuff[256];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(12000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10);
    
    memset(fds, 0, sizeof(fds));
    fds[0].fd = listenfd;
    fds[0].events = POLLIN;
    
    timeout = (60 * 1000);
    printf("37");
    
    
    while(1)
    {
        printf("Waiting on poll()...\n");
        rc = poll(fds, nfds, timeout);
        if (rc < 0){
            perror("  poll() failed");
            break;
        }if (rc == 0){
            printf("  poll() timed out.  End program.\n");
            break;
        }
            connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
            printf("42");
            read(connfd, recvBuff, sizeof(recvBuff)-1);
            std::cout << recvBuff << std::endl;
            ticks = time(NULL);
            snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
            write(connfd, sendBuff, strlen(sendBuff));

            close(connfd);
    //        break;
            sleep(1);
     }
    close(listenfd);
}
