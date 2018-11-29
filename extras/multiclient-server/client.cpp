#include "tcp.h"
#include<iostream>
#include <unistd.h>
#include<string.h>
using namespace std;

int main(int argc, char *argv[]){
    char data[1024] = {0};
    cout<< argv[1]<<endl;
    int socket_fd = setUpClientSocket();
    strcpy(data, argv[1]);

    send(socket_fd,data,strlen(data),0);

    cout<<"Sent : "<<data<<endl;
    cout<<"sending again "<<endl;
    strcpy(data,"ALOHA BITCHES!");
    send(socket_fd,data,strlen(data),0);

    while(1);

    return 0;
}
