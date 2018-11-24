#include <unistd.h> //contains various constants
#include<string.h>
#include<iostream>
#include "tcp.h"
using namespace std;


int main(){
    char data[1025]; // Actually this is called packet in Network Communication, which contain data and send through.

    int socket_fd = setUpServerSocket();
    while(1) {
        cout<<"Server runnin on Port "<<2017<<endl;
        int client_fd = accept(socket_fd, (sockaddr*)NULL, NULL);
        cout<<"Client connected"<<endl;
        strcpy(data,"hello bitch");
        write(client_fd, data, strlen(data));

        close(client_fd);
        sleep(1);
     }

     return 0;
}
