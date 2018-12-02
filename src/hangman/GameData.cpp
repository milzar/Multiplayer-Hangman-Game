#include "GameData.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <random>

void GameData::init(int root_word_len) {
    word_length = root_word_len;
    memset(current_string, '_', word_length);
    current_string[word_length] = '\0';

    n_players = 2;
    current_turn = 0;
}

int GameData::play(std::string root_word, std::string str) {
    int len = str.size();

    // std::cout<<"playing "<<str<<"on "<<root_word<<std::endl;
    // The word is being guessed
    if(len != 1) {
        return str == root_word;
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
    std::cout << "\n\n" << '\n';
    std::cout<<"..........\t\tWord : "<<current_string<<"\t\t..........";
    std::cout << "\n\n" << '\n';

}

std::string GameData::serialize() {
  char data[1024];
  sprintf(data, "%d %s %d %d|", word_length, current_string, n_players, current_turn);
  std::string str(data);
  // std::cout<<"Serialized\t"<<str<<std::endl;
  return str;
}

void GameData::deserialize(std::string req){
    char data[1024]={0};
    req.copy(data, req.size());
    sscanf(data, "%d %s %d %d|", &word_length, current_string, &n_players, &current_turn);
    // std::cout<<"Deserializing\t"<<req<<std::endl;
}


std::string GameData::getRandomWord() {
    std::ifstream file("words.txt");
    std::string word;

    std::random_device rd;
    unsigned long rand_no = std::uniform_int_distribution<unsigned long>()(rd) % 367516;

    while(--rand_no) getline(file, word);
    getline(file, word);

    // Remove trailing newline char
    word.erase(word.length() - 1);
    std::cout<<"Root Word: "<<word<<std::endl;
    return word;
}
