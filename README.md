# Battle-Royale-Hangman

A Multiplayer Hangman game written in C++ based on the client-server model using the basics of socket programming.
Currently the source code has been compiled for Linux systems. Here's what the server (Player 1) needs to do to set up a game :

### Compilation Steps
make

```
./server.out Port NoOfPlayers    
```
server.out is the compiled output file for creating the server.                                                                             

Server will wait till NoOfPlayers clients have connected to start the game
The client (Player 2) should type in -

```
./client.out Server-IP Server-port ClientName
```

client.out is the compiled output file for connecting to the server. Given a server has already been set up, the client should be able to connect comfortably to the server.

Feel free to report any bugs. Suggestions are welcome.
