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
#include <iomanip>
#include <sys/time.h>
#include "TandS.cpp"
#include <vector>

int id = 0;

std::vector<std::pair<std::string, int>> client_count;


void printFooter(){
    for (auto i : client_count){
        std::cout << i.second << " transactions from " << i.first << std::endl;
    }
}

void printTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long double secondsEpoch =
        (long double)(tv.tv_sec) +
        (long double)(tv.tv_usec) / 10000;
    //time_t epoch = time(NULL);
    std::cout << std::setprecision(2) << std::fixed << secondsEpoch << ": ";
}

void add_transaction(char *client_name){
    std::string client_name_string(client_name);
    bool foundIt = false;
    for (int i = 0; i < (int) client_count.size(); i++){
        if(client_count[i].first.compare(client_name_string) == 0){
            int count = client_count[i].second;
            count++;
            client_count[i].second = count;
            foundIt = true;
            break;
        }
    }
    if (!foundIt){
        std::pair<std::string, int> toPut;
        toPut.first = client_name_string;
        toPut.second = 1;
        client_count.push_back(toPut);
    }
    
}

void printHeader(int portnumber){
    std::cout << "Using port: " << portnumber << std::endl;
}

void doWork(char recvBuff[], char sendBuff[]){
    char *client_name, *pch;
    sprintf(recvBuff, "%s-%d", recvBuff, 20);
    //int message_size = (int) strlen(recvBuff);
    client_name = strtok(recvBuff,"-");
    pch = strtok(NULL, "-");
    int work = atoi(pch);
    add_transaction(client_name);
    printTime();
    std::cout << "# " << ++id << " " << "(T" << std::setfill (' ') << std::setw (3) << work << ") ";
    std::cout << "from " << client_name << std::endl;
    Trans(work);
    printTime();
    std::cout << "# " << id << " " << "(DONE) ";
    std::cout << "from " << client_name << std::endl;
}

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    struct pollfd fds[200];
    int    nfds = 1;
    int    timeout;
    int rc;
    

    char sendBuff[256];
    char recvBuff[256];
    

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    unsigned short vOut = (unsigned short)strtol(argv[1],NULL,10);
    serv_addr.sin_port = htons(vOut);
    printHeader(vOut);
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10);
    
    memset(fds, 0, sizeof(fds));
    fds[0].fd = listenfd;
    fds[0].events = POLLIN;
    
    timeout = (30 * 1000);
    //printf("37");
    
    
    while(1)
    {
        //printf("Waiting on poll()...\n");
        rc = poll(fds, nfds, timeout);
        if (rc < 0){
            perror("  poll() failed");
            break;
        }if (rc == 0){
            //printf("  poll() timed out.  End program.\n");
            break;
        }
            connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
//            printf("42");
            read(connfd, recvBuff, sizeof(recvBuff)-1);
            doWork(recvBuff, sendBuff);
            //std::cout << recvBuff << std::endl;
           // ticks = time(NULL);
            sprintf(sendBuff, "%s %d","D", id);
            //snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
            write(connfd, sendBuff, strlen(sendBuff));

            close(connfd);
    //        break;
            sleep(1);
     }
    printFooter();
    close(listenfd);
}
