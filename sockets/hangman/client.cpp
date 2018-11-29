#include "tcp.h"
#include<iostream>
#include <unistd.h>
#include<string.h>
using namespace std;

int main(int argc, char *argv[]){

    cout<<argv[1]<<" Running  "<<endl;

    Client myclient;
    myclient.forward(argv[1]);
    cout<<"Received:\t"<<myclient.receive()<<endl;
    myclient.forward("begin");

    cout<<"Received:\t"<<myclient.receive()<<endl;
    while(1);

    return 0;
}
