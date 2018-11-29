#include <arpa/inet.h>

int setUpClientSocket(int port = 2017 ){
      int socket_fd = socket(AF_INET, SOCK_STREAM, 0);;
      sockaddr_in socket_address;
      socket_address.sin_family = AF_INET;
      socket_address.sin_port = htons(port);
      socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");

      connect(socket_fd, (struct sockaddr *)&socket_address, sizeof(socket_address) );

      return socket_fd;
}

int setUpServerSocket(int port=2017, int maxClients = 20){
      //CREATE SOCKET
      //So it is just an integer number that uniquely represents an opened file/socket in operating system
      int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // creating socket
      //AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
      //domain type protocol
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
      return socket_fd;
}
