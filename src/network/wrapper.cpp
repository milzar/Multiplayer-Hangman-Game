#include "wrapper.h"
#include<vector>
#include<algorithm>
#include <arpa/inet.h>


Client::Client(){
  Client::init("127.0.0.1",2017);
}

Client::Client(char *ip,char *port){
    Client::init(ip,atoi(port) );
}


void Client::init(std::string serverIp , int port ){
      char *IP;
      IP = (char*) malloc(serverIp.size());
      serverIp.copy(IP,serverIp.size());

      int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
      sockaddr_in socket_address;
      socket_address.sin_family = AF_INET;
      socket_address.sin_port = htons(port);
      socket_address.sin_addr.s_addr = inet_addr(IP);

      connect(socket_fd, (struct sockaddr *)&socket_address, sizeof(socket_address) );
      mastersocket = socket_fd;
}
void  Client::init(char* serverIp , int port ){
      int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
      sockaddr_in socket_address;
      socket_address.sin_family = AF_INET;
      socket_address.sin_port = htons(port);
      socket_address.sin_addr.s_addr = inet_addr(serverIp);

      connect(socket_fd, (struct sockaddr *)&socket_address, sizeof(socket_address) );
      mastersocket = socket_fd;
}

int Client::forward(std::string str){
    char data[1024]={0};
    str.copy(data, str.size());
    send(mastersocket, data,strlen(data),0);
    return str.size();
}
int Client::forward(char *str){
  char data[1024]={0};
  strcpy(data,str);
  send(mastersocket, data,strlen(data),0);
  return strlen(str);
}

std::string Client::receive(){
    char data[1024]={0};
    recv(mastersocket, data , sizeof(data) , 0);
    return std::string(data);
}

Server::Server(){
      init(2017,20);
}
Server::Server(char *port,int maxClients){
      init(atoi(port),maxClients);
}

void Server::init(int port, int maxClients = 20){
      //CREATE SOCKET
      //So it is just an integer number that uniquely represents an opened file/socket in operating system
      int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // creating socket
      //AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
      //SOCK_STREAM: TCP(reliable, connection oriented)
      //SOCK_DGRAM: UDP(unreliable, connectionless)

      //Bind ip and port to socket
      sockaddr_in socket_address;
      socket_address.sin_family = AF_INET;
      socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
      socket_address.sin_port = htons(port);         // this is the port number of running server
      bind(socket_fd, (sockaddr*)&socket_address , sizeof(socket_address));

      //LISTEN Socket
      listen(socket_fd , maxClients);
      //20 - max no of connections
      mastersocket = socket_fd;
}

std::string Server::receive(int client){
      char data[1024]={0};
      recv(client, data , sizeof(data) , 0);
      return std::string(data);
  }

int Server::forward(int client, std::string str){
      char data[1024]={0};
      str.copy(data, str.size());
      send(client, data,strlen(data),0);
      return str.size();
  }
  int Server::forward(int client, char *str){
    char data[1024]={0};
    strcpy(data,str);
    send(client, data,strlen(data),0);
    return strlen(str);
  }

Player::Player(){
  name = "";
  socket_id=-1;
}
Player::Player(std::string a, int b){
    name =a;
    socket_id=b;
}


int updateMaxFD(std::vector<Player> clients, int maxfd){
    int x =maxfd;
    for(int i=0;i<clients.size();i++)
      x =std::max(x,clients[i].socket_id);
    return x;

}
fd_set initFdset(std::vector<Player> clients, int master){
    fd_set temp;
    FD_ZERO(&temp);
    FD_SET(master,&temp);
    for(int i=0;i<clients.size();i++){
        if(clients[i].socket_id)
            FD_SET(clients[i].socket_id,&temp);
    }
    return temp;
}
