//Run as ./client server-ip server-port PlayerName


#include "wrapper.h"
#include<iostream>
#include <unistd.h>
#include<string.h>
using namespace std;

int main(int argc, char *argv[]){
    if(argc < 4){
        cout<<"Invalid arguments"<<endl;
        return 0;
    }
    cout<<argv[3]<<"\tRunning"<<endl;

    Client myclient(argv[1],argv[2]);

    myclient.forward(argv[3]);
    cout<<"Received:\t"<<myclient.receive()<<endl;
    cout<<"Waiting"<<endl;
    cout<<myclient.receive()<<endl;
    //Game started

    while(true){
        string str = myclient.receive();
        if(str == "play"){
            string temp;
            cout<<"Your turn : Enter choice"<<endl;
            cin>>temp;
            myclient.forward(temp);
        }
        cout<<"\nReceived\t"<<myclient.receive()<<endl;
    }
    return 0;
}
