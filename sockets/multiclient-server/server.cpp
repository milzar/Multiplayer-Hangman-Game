#include <unistd.h> //contains various constants
#include<string.h>
#include<iostream>
#include "tcp.h"
#include <sys/time.h>
#include<vector>
using namespace std;

int updateMaxFD(vector<int> clients, int max){
    int x = max_element(clients.begin(),clients.end());
    return max > x ? max : x;

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
          cout<<"selecting .. "<<endl;
          select( max_file + 1 , &masterfds , NULL , NULL , NULL);
          //Activity on main socket : Incoming Connection
          if(FD_ISSET(master_socket, &masterfds) ){
              int newSocket = accept(master_socket,(sockaddr*)NULL  ,NULL);
              client_sockets.push_back(newSocket);

              strcpy(data,"");
              recv(newSocket,data,sizeof(data)-1,0 );
              cout<<"New user has been added"<<data<<endl;
              max_file = updateMaxFD(client_sockets,max_file);
          }
          else{

                cout<<"Connected Clients :  "<<client_sockets.size()<<endl;
                for(auto client : client_sockets){
                      if(FD_SET(client,masterfds)){
                        
                      }
                }
          }

        }

     return 0;
}
