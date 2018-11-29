#include "tcp.h"
#include<iostream>
#include <unistd.h>
#include<string.h>
using namespace std;

int main(){
    char data[1024] = {0};

    int socket_fd = setUpClientSocket();


    recv(socket_fd, data, sizeof(data)-1,0);
    cout<<"received : "<<data<<endl;
    strcpy(data,""  );

    int i=1;
    while(1){
        strcpy(data,"From client"  ) ;
        send(socket_fd,data,strlen(data),0);
        sleep(2);
    }

    return 0;
}
