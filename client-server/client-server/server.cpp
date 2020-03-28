// From: www.thegeekstuff.com/2011/12/c-socket-programming
//

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
#include <chrono>

int id = 0;
//timeout for server
int timeout = (60 * 1000);

std::vector<std::pair<std::string, int>> client_count;
std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

//prints the footer
void printFooter(){
    for (auto i : client_count){
        std::cout << i.second << " transactions from " << i.first << std::endl;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    //time diff from start and subtracting the timeout value
    std::chrono::seconds sec(timeout/1000);
    std::chrono::duration<double> elapsed = t2 - start_time - sec;
    std::cout << std::setprecision(1) << std::fixed << id/elapsed.count();
    //print the footer
    std::cout << " transactions/sec  (" << id << "/";
    std::cout << std::setprecision(2) << std::fixed << elapsed.count() << ")" << std::endl;
    
}

//print the current epoch time
void printTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long double secondsEpoch =
        (long double)(tv.tv_sec) +
        (long double)(tv.tv_usec) / 10000;
    std::cout << std::setprecision(2) << std::fixed << secondsEpoch << ": ";
}

//increase a transcation count for the client
void add_transaction(char *client_name){
    std::string client_name_string(client_name);
    bool foundIt = false;
    //find if the client alredy sent mesasge in the past
    for (int i = 0; i < (int) client_count.size(); i++){
        if(client_count[i].first.compare(client_name_string) == 0){
            int count = client_count[i].second;
            count++;
            client_count[i].second = count;
            foundIt = true;
            break;
        }
    }
    //if not add it
    if (!foundIt){
        std::pair<std::string, int> toPut;
        toPut.first = client_name_string;
        toPut.second = 1;
        client_count.push_back(toPut);
    }
    
}

//print the header
void printHeader(int portnumber){
    std::cout << "Using port: " << portnumber << std::endl;
}

//do transaction specified by the client and print its sumamry
void doWork(char recvBuff[], char sendBuff[]){
    char *client_name, *pch;
    sprintf(recvBuff, "%s-%d", recvBuff, 20);
    //get the clientname i.e. hostname.pid
    client_name = strtok(recvBuff,"-");
    //get the work
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
    
    int rc;
    //start the program timer
    start_time = std::chrono::high_resolution_clock::now();
    

    char sendBuff[256];
    char recvBuff[256];
    

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //convert char* IP to unsigned int IP
    unsigned short vOut = (unsigned short)strtol(argv[1],NULL,10);
    serv_addr.sin_port = htons(vOut);
    printHeader(vOut);
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10);
    
    memset(fds, 0, sizeof(fds));
    fds[0].fd = listenfd;
    fds[0].events = POLLIN;
    

    
    
    while(1)
    {
        //select the next client in queue and if no response within "timeout" quit
        //https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_71/rzab6/poll.htm
        rc = poll(fds, nfds, timeout);
        if (rc < 0){
            perror("  poll() failed");
            break;
        }if (rc == 0){
            //printf("  poll() timed out.  End program.\n");
            break;
        }
            connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
            read(connfd, recvBuff, sizeof(recvBuff)-1);
            doWork(recvBuff, sendBuff);
            sprintf(sendBuff, "%s %d","D", id);
            //snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
            write(connfd, sendBuff, strlen(sendBuff));

            close(connfd);
            sleep(1);
     }
    //print the footer and close the socket
    printFooter();
    close(listenfd);
}
