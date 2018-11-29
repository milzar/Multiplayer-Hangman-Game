#include <iostream>
#include <string.h>
#include "GameData.h"

int main() {
    std::cout<<"Connecting to server on port"<<PORT_NO<<std::endl;
    // Client try connecting to server
    //NETWORK


    std::cout<<"Connected to server"<<std::endl;

    // If it is client's turn to play
    bool turn = false;
    GameData game(1);

    // Read from server turn and GameData initially
    //NETWORK


    while(true) {
        game.render();
        if(turn) {
            std::string str;
            std::cout<<"Your turn to play: "<<std::endl;
            std::cin>>str;

            // Send str to server
            //NETWORK

        }

        // Read from server turn and GameData
        //NETWORK

    }
}
