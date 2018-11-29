#include <unistd.h> //contains various constants
#include<string.h>
#include<iostream>
#include "tcp.h"
using namespace std;


int main(){
    char data[1025]; // Actually this is called packet in Network Communication, which contain data and send through.

        int socket_fd = setUpServerSocket();

        cout<<"Server runnin on Port "<<2017<<endl;

        int client_fd = accept(socket_fd, (sockaddr*)NULL, NULL);
        cout<<"Client connected"<<endl;
        strcpy(data,"Welcome to the server");
        send(client_fd, data, strlen(data), 0);

        while(1){
              sleep(1);
              strcpy(data,"");
              recv(client_fd, data, sizeof(data)-1,0);
              cout<<data<<endl;

        }

     return 0;
}
