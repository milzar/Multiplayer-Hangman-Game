#include <arpa/inet.h>
#include<string>
#include<string.h>

class Client{
  public :
    int mastersocket; //The fd of the socket of the client
            Client(){
                init("127.0.0.1",2017);
            }
            Client(char *ip,char *port){
                init(ip,atoi(port) );
            }

            //Opens a tcp connection to a server at port and ip and sets the socket_fd
            void  init(std::string serverIp , int port ){
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
            void  init(char* serverIp , int port ){
                  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
                  sockaddr_in socket_address;
                  socket_address.sin_family = AF_INET;
                  socket_address.sin_port = htons(port);
                  socket_address.sin_addr.s_addr = inet_addr(serverIp);

                  connect(socket_fd, (struct sockaddr *)&socket_address, sizeof(socket_address) );
                  mastersocket = socket_fd;
            }
            //Sends the message to the server
            int forward(std::string str){
                char data[1024]={0};
                str.copy(data, str.size());
                send(mastersocket, data,strlen(data),0);
                return str.size();
            }
            int forward(char *str){
              char data[1024]={0};
              strcpy(data,str);
              send(mastersocket, data,strlen(data),0);
              return strlen(str);
            }
            // template <class T>
            // int forwardObject(T obj){
            //   return send(mastersocket, (char*) obj,sizeof(T),0);
            // }

            std::string receive(){
                char data[1024]={0};
                recv(mastersocket, data , sizeof(data) , 0);
                return std::string(data);
            }

            // template <class T>
            // T receiveObject(){
            //     T obj;
            //     char data[1024]={0};
            //     recv(mastersocket, &obj , sizeof(T) , 0);
            //     return obj;
            // }

};


class Server{
  public :

    int mastersocket;

          Server(){
                init(2017,20);
          }
          Server(char *port,int maxClients){
                init(atoi(port),maxClients);
          }

          void init(int port, int maxClients = 20){
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

        std::string receive(int client){
                char data[1024]={0};
                recv(client, data , sizeof(data) , 0);
                return std::string(data);
            }

        int forward(int client, std::string str){
                char data[1024]={0};
                str.copy(data, str.size());
                send(client, data,strlen(data),0);
                return str.size();
            }
            int forward(int client, char *str){
              char data[1024]={0};
              strcpy(data,str);
              send(client, data,strlen(data),0);
              return strlen(str);
            }

        // template <class T>
        // int forwardObject(int client, T obj){
        //   return send(mastersocket, (char*) obj,sizeof(T),0);
        // }
        //
        // template <class T>
        // T receiveObject(int client){
        //     T obj;
        //     char data[1024]={0};
        //     recv(mastersocket, &obj , sizeof(T) , 0);
        //     return obj;
        // }

};
