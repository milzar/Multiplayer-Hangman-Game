//Run as ./server port max-clients-no

#include <unistd.h> //contains various constants
#include<string.h>
#include<iostream>
#include "wrapper.h"
#include <sys/time.h>
#include<vector>
#include<algorithm>
using namespace std;

class Player{
    public :
          string name;
          int socket_id;
          Player(){
            name = "";
            socket_id=-1;
          }
          Player(string a, int b){
              name =a;
              socket_id=b;
          }
};


int updateMaxFD(vector<Player> clients, int maxfd){
    int x =maxfd;
    for(int i=0;i<clients.size();i++)
      x =max(x,clients[i].socket_id);
    return x;

}
fd_set initFdset(vector<Player> clients, int master){
    fd_set temp;
    FD_ZERO(&temp);
    FD_SET(master,&temp);
    for(int i=0;i<clients.size();i++){
        if(clients[i].socket_id)
            FD_SET(clients[i].socket_id,&temp);
    }
    return temp;
}

void sendGameNotification(vector<Player> clients,Server s ){
      for(auto client : clients){
              s.forward(client.socket_id,"Game Started");
      }
}

int main(int argc,char *argv[]){
        int maxPlayers =2;
        bool beginGame=false;
        // vector<int> client_sockets;
        vector<Player> players;

        Server myserver(argv[1],argv[2]);
        cout<<"Server runnin on Port "<<argv[1]<<endl;

        fd_set masterfds;
        FD_ZERO(&masterfds);
        FD_SET(myserver.mastersocket,&masterfds);
        int max_file , socketCount;
        max_file = myserver.mastersocket;

        timeval t;
        t.tv_sec = 2;
        t.tv_usec = 500000;

        while(!beginGame){
          masterfds = initFdset(players,myserver.mastersocket);
          select( max_file + 1 , &masterfds , NULL , NULL , NULL);
          //Activity on main socket : Incoming Connection before game started
          if(FD_ISSET(myserver.mastersocket, &masterfds)){
              int newSocket = accept(myserver.mastersocket,(sockaddr*)NULL  ,NULL);
              string newName = myserver.receive(newSocket);
              Player tmp = Player(newName,newSocket);
              players.push_back(tmp);
              cout<<"New User Added:\t"<<tmp.name<<endl;
              max_file = updateMaxFD(players,max_file);
              myserver.forward(newSocket,"Welcome to the server bitch" );
          }

          cout<<"Connected Clients:\t"<<players.size()<<endl;
          if(players.size()>= maxPlayers  )
              beginGame=true;

        }
        sleep(1);
        //Begin Game
        sendGameNotification(players,myserver);

        int turn=0;
        while(true){
            int currentPlayer = players[turn].socket_id;
            for(auto player : players){
                if(player.socket_id == currentPlayer)
                  myserver.forward(player.socket_id, "play");
                else
                  myserver.forward(player.socket_id, "wait");
            }
            string str = myserver.receive(currentPlayer);
            for(auto player : players){
                  myserver.forward(player.socket_id, str);
            }
            turn = (turn +1)%maxPlayers;
          }
     return 0;
}
