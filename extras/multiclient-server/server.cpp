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
        char data[1025]; // Actually this is called packet in Network Communication, which contain data and send through.
        int maxClients =4;
        // int client_sockets[maxClients]={0};
        vector<int> client_sockets;
        int master_socket = setUpServerSocket( );
        cout<<"Server runnin on Port "<<2017<<endl;
        //File Dexriptor set
        fd_set masterfds;
        FD_ZERO(&masterfds);
        FD_SET(master_socket,&masterfds);
        int max_file , socketCount;
        max_file = master_socket;

        while(true){
          masterfds = initFdset(client_sockets,master_socket);
          select( max_file + 1 , &masterfds , NULL , NULL , NULL);
          //Activity on main socket : Incoming Connection
          if(FD_ISSET(master_socket, &masterfds) ){
              int newSocket = accept(master_socket,(sockaddr*)NULL  ,NULL);
              client_sockets.push_back(newSocket);

              strcpy(data,"");
              recv(newSocket,data,sizeof(data)-1,0 );
              cout<<"New user has been added "<<data<<endl;
              max_file = updateMaxFD(client_sockets,max_file);
          }
          else{

                cout<<"Connected Clients :  "<<client_sockets.size()<<endl;
                for(auto client : client_sockets){
                      if(FD_ISSET(client,&masterfds)){
                            strcpy(data,"");
                            recv(client, data,sizeof(data),0);
                            cout<<"Received  : "<<data<<endl;
                      }
                }
          }


        }
     return 0;
}
