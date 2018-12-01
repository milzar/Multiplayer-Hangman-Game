#include "GameData.h"
#include <string.h>
#include <iostream>

void GameData::init(int root_word_len) {
    word_length = 4;
    memset(current_string, '_', word_length);
    current_string[word_length] = '\0';

    n_players = 2;
    current_turn = 0;
}

int GameData::play(char* root_word, const char* str) {
    int len = strlen(str);

    // The word is being guessed
    if(len != 1) {
        return (!strcmp(root_word, str));
    }

    // A letter is being guessed
    char letter = str[0];
    bool game_finished = true;

    for(int i = 0; i < word_length; ++i) {
        if(root_word[i] == letter) {
            current_string[i] = letter;
        }
        if(current_string[i] == '_') {
            game_finished = false;
        }
    }
    return game_finished;
}

void GameData::render() {
    std::cout<<"Current string : "<<current_string<<std::endl;
}

