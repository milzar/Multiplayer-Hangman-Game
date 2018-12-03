//Run as ./server port max-clients-no

#include "network/wrapper.h"
#include "hangman/GameData.h"

#include <unistd.h> //contains various constants
#include<string.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void sendGameNotification(vector<Player> clients,Server s ,GameData game){
      for(auto client : clients){
              s.forward(client.socket_id,game.serialize());
      }
}
int main(int argc,char *argv[]){

        int maxPlayers =atoi(argv[2]);
        bool beginGame=false;
        vector<Player> players;
        cout<<"Server runnin on Port "<<argv[1]<<endl;


        Server myserver(argv[1],maxPlayers);

        fd_set masterfds;
        FD_ZERO(&masterfds);
        FD_SET(myserver.mastersocket,&masterfds);
        int max_file ;
        max_file = myserver.mastersocket;


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
              myserver.forward(newSocket,"Welcome to Battle Royale Hangman(2018)" );
          }

          cout<<"No of Players:\t"<<players.size()<<endl;
          if(players.size()>= maxPlayers  )
              beginGame=true;

        }
        sleep(1);
        //Begin Game
        string root_word = GameData::getRandomWord();
        GameData game(root_word.size());
        sendGameNotification(players,myserver,game);
        //GAMEDATA

        int turn=0;
        while(true){
            int currentPlayer = players[turn].socket_id;
            for(auto player : players){
                if(player.socket_id == currentPlayer)
                  myserver.forward(player.socket_id, "play");
                else
                  myserver.forward(player.socket_id, "wait");
            }
            //Receive Client guess
            string guess = myserver.receive(currentPlayer);
            if(game.play(root_word,guess) ){
                cout<<"Game Over\t"<<players[turn].name<<" Wins\t"<<endl;
                string res = "gameover"+players[turn].name + "||" +root_word;
                for(auto player : players){
                      myserver.forward(player.socket_id, res);
                }
                // cout<<"Play Again?"<<endl;
                // sleep(1);
                // res = myserver.receive();
                break;
            }
            else{
                string res = game.serialize();
                for(auto player : players){
                      myserver.forward(player.socket_id, res);
                }
                turn = (turn +1)%maxPlayers;
            }

            sleep(1);
          }
     return 0;
}
