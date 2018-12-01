//Run as ./client server-ip server-port PlayerName


#include "wrapper.h"
#include<iostream>
#include <unistd.h>
#include<string.h>
#include "GameData.h"

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


    string  res = myclient.receive();
    GameData game(1);
    game.deserialize(res);
    game.render();
    //Game started

    while(true){
        //Play or wait
        cout<<"Waiting for server command"<<endl;
        string str = myclient.receive();
        if(str == "play"){
            string req;
            cout<<"Your turn : Enter choice"<<endl;
            cin>>req;
            //Send guess
            myclient.forward(req);
        }
        else{
            cout<<"Nor my turn\t Received\t"<<str<<endl;
        }
        std::cout << "Receiving Game data" << '\n';
        string res;
        res=myclient.receive();
        game.deserialize(res);
        game.render();
        std::cout << "end loop" << '\n';
    }
    return 0;
}
