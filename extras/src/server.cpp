#include <iostream>
#include <string.h>
#include "GameData.h"

int main() {
    vector<int> client_sockets;

    std::cout<<"Starting server on port"<<PORT_NO<<std::endl;
    // Server stuff
    //NETWORK


    std::cout<<"Server setup, now listening for clients"<<std::endl;
    // Accept connections
    // push to client_sockets, I guess
    //NETWORK


    // After connections established
    char* root_word;
    strcpy(root_word, "ball");
    GameData game(4);

    while(true) {
        // Listen to the player whose turn it is
        // client_sockets[game.current_player()]
        // He sends a string to be put in str
        //NETWORK
        char *str;

        // True if game over
        if(game.play(root_word, str)) {
            std::cout<<"Game over, player "<<game.current_player()<<" won."<<std::endl;

            // Close sockets
            //NETWORK


            return 1;
        }

        // Update the game for all the clients
        // Send GameData game to all clients
        //NETWORK

    }

}
