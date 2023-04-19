/**
 * @file utilities.cpp
 * @brief This file contains the implementation of the utilities functions.
*/
#include <filesystem>
#include <iostream>
#include "utilities.hpp"

void write_gamestate(const vector<GameState*> &gamestate, const string &foldername , const string &filename ){
    for(unsigned int i = 0; i < gamestate.size(); i++){
        if(foldername == "" && filename == "" ){
            gamestate[i]->exportMapSvg(string("export/map_BFS_ShortPath_")+ std::to_string(i) + ".svg");
            gamestate[i]->writeMapFile(string("map/map_BFS_ShortPath_")+ std::to_string(i) + ".txt");
        }else{
                std::filesystem::create_directory("export/"  + foldername);
                std::filesystem::create_directory("map/" +foldername);
                gamestate[i]->exportMapSvg("export/" +foldername + "/" + filename + "_" + std::to_string(i) + ".svg");
                gamestate[i]->writeMapFile("map/" + foldername + "/" + filename + "_" + std::to_string(i) + ".txt");
        }
    }
}


void destroy_vec_gamestate(vector<GameState*> &gamestate){
    for(unsigned int i = 0; i < gamestate.size(); i++){
        delete gamestate[i];
    }
    gamestate.clear();
}

void printDVector(vector<vector<int>> vec){
    std::cout << std::endl << std::endl;
    for (unsigned int i = 0; i < vec.size();i++){
        for (unsigned int j = 0; j < vec[i].size();j++){
            if (vec[i][j] == -1){
                std::cout << "X  ";
            }
            else{
                std::cout << vec[i][j] << "  " ;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int getRandomNumber(int min, int max){
    return min + rand() % (max - min + 1);
}