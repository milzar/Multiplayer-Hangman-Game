#include <unistd.h> //contains various constants
#include<string.h>
#include<iostream>
#include "tcp.h"
#include <sys/time.h>
#include<vector>
#include<algorithm>
using namespace std;

int updateMaxFD(vector<int> clients, int maxfd){
    int x =maxfd;
    for(int i=0;i<clients.size();i++)
      x =max(x,clients[i]);
    return x;

}
fd_set initFdset(vector<int> clients, int master){
    fd_set temp;
    FD_ZERO(&temp);
    FD_SET(master,&temp);
    for(int i=0;i<clients.size();i++){
        if(clients[i])
            FD_SET(clients[i],&temp);
    }
    return temp;
}

int main(){
        int maxClients =4;
        vector<int> client_sockets;

        Server myserver;

        cout<<"Server runnin on Port "<<2017<<endl;

        fd_set masterfds;
        FD_ZERO(&masterfds);
        FD_SET(myserver.mastersocket,&masterfds);
        int max_file , socketCount;
        max_file = myserver.mastersocket;

        while(true){
          masterfds = initFdset(client_sockets,myserver.mastersocket);
          select( max_file + 1 , &masterfds , NULL , NULL , NULL);
          //Activity on main socket : Incoming Connection
          if(FD_ISSET(myserver.mastersocket, &masterfds) ){
              int newSocket = accept(myserver.mastersocket,(sockaddr*)NULL  ,NULL);
              client_sockets.push_back(newSocket);

              cout<<"New User Added:\t"<<myserver.receive(newSocket)<<endl;
              max_file = updateMaxFD(client_sockets,max_file);

              myserver.forward(newSocket,"Welcome to the server bitch" );
          }
          else{
                cout<<"Connected Clients:\t"<<client_sockets.size()<<endl;
                for(auto client : client_sockets){
                      if(FD_ISSET(client,&masterfds)){
                            string data = myserver.receive(client);
                            cout<<"Received:\t"<<myserver.receive(client)<<endl;
                            if( data  == "begin"){
                                for(auto c : client_sockets){
                                    myserver.forward(c, "Game Started");
                                }
                            }
                      }
                }
          }


        }
     return 0;
}
