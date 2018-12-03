//Run as ./client server-ip server-port PlayerName

#include "hangman/GameData.h"
#include "network/wrapper.h"
#include<iostream>
#include <unistd.h>
#include<string.h>

using namespace std;
static int i;

int main(int argc, char *argv[]){
    if(argc < 4){
        cout<<"Invalid arguments"<<endl;
        return 0;
    }

    cout<<argv[3]<<"\tRunning"<<endl;
    Client myclient(argv[1],argv[2]);
    myclient.forward(argv[3]);
    cout<<"Received:\t"<<myclient.receive()<<endl;
    cout<<"Waiting for other players......"<<endl;
    string  res = myclient.receive();
    GameData game(1);
    game.deserialize(res);
    game.render();
    //Game started
    while(true){
        //Play or wait
        // cout<<"Waiting for server command"<<endl;
        string str = myclient.receive();

        if(str == "play"){
            string req="";
            cout<<"Your turn : Enter choice"<<endl;
            cin>>req;
            //TODO
            //Check if req is an already guessed character
            //If so read input again
            myclient.forward(req);
        }
        else if(str == "wait"){
            cout<<"Waiting for other player"<<endl;
        }
        else{
        }

        string res;
        res=myclient.receive();
        if( res.find("gameover") != string::npos ){
            cout<<"GAME OVER!"<<endl;
            int found = res.find("||");
            cout<<res.substr(8,found)<<" Wins!"<<endl;
            cout<<"Word was:"<<res.substr(found+2);
            // cout<<"Play Again(Y/N)?"<<endl;
            // string again;
            // cin>>again;
            // if(again != "y"){
            //     break;
            // }
            // else{
            //     cout<<"Waiting for next game"<<endl;
            //     while(1);
            // }

            return 0;

        }
        else{
            game.deserialize(res);
            game.render();
        }

    }
    return 0;
}
