/**
 * @file utilities.hpp
 * @brief This file contains the declaration of the utilities functions.
*/
#pragma once
#include "GameState.hpp"
/**
 * @brief Write the GameState to files (txt and svg format).
 * @param gamestate A vector of pointers to GameState objects.
 * @param foldername The name of the folder in which to write the file(s). Defaults to "".
 * @param filename The name of the file to write. Defaults to "".
 */
void write_gamestate(const vector<GameState*> &gamestate, const string &foldername = "", const string &filename = "");

void printDVector(vector<vector<int>>);

/**
 * @brief Deletes the GameState objects in the vector and clears the vector.
 * @param gamestate A vector of pointers to GameState objects.
*/
void destroy_vec_gamestate(vector<GameState*> &gamestate);

/**
 * @brief Returns a random number between min and max.
*/
int getRandomNumber(int min, int max);
