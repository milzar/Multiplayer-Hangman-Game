#include <arpa/inet.h>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
class Client{
  public :
    int mastersocket; //The fd of the socket of the client
            Client();
            Client(char *ip,char *port);

            //Opens a tcp connection to a server at port and ip and sets the socket_fd
            void  init(std::string serverIp , int port );
            void  init(char* serverIp , int port );
            //Sends the message to the server
            int forward(std::string str);
            int forward(char *str);
            std::string receive();
};


class Server{
  public :

    int mastersocket;

          Server();
          Server(char *port,int maxClients);

          void init(int port, int maxClients);

          std::string receive(int client);

          int forward(int client, std::string str);
          int forward(int client, char *str);


};



class Player{
    public :
          std::string name;
          int socket_id;
          Player();
          Player(std::string a, int b);
};
int updateMaxFD(std::vector<Player> clients, int maxfd);
fd_set initFdset(std::vector<Player> clients, int master);
