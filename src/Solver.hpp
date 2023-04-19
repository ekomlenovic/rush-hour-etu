/**
 * @file Solver.hpp
 * @brief This file contains the declaration of the Solver class and tree_node struct.
*/
#pragma once
#include <vector>
#include <queue>
#include "GameState.hpp"
#include <map>

struct tree_node;

/**
 * @struct tree_node
 * @brief This struct is used to create a tree of GameStates.
 * @details Previous is a pointer to the previous GameState. Current is a pointer to the current GameState.
*/
struct tree_node{
    tree_node* previous;
    GameState* current;
    tree_node(tree_node* p , GameState* c){
        previous = p;
        current = c;
    }

    ~tree_node(){
        delete current;
        previous = nullptr;
    }
};
/**
 * @class Solver
 * @brief This class contains the BFS algorithm to find the shortest path to the objetive.
*/
class Solver{
    public:     
        /**
         * @brief Returns a vector of Gamestate with the shortest path to the objetive.
         * @param start The initial GameState.
         * @param objetive The objetive Coordinate (Optionnal (default : -1, -1)).
        */
        std::vector<GameState*> BFS(GameState* start, Coordinate objetive = Coordinate(-1,-1));
        
        /**
         * @brief Auxiliar function for BFS.
         * @param start The initial GameState.
         * @param objetive The objetive Coordinate.
         * @param nodes A vector of tree_node*.
        */
        std::vector<GameState*> BFS_aux(GameState* start, Coordinate objetive, vector<tree_node*> &nodes); 

        /**
         * @brief Returns a vector of Gamestate with the shortest path to the objetive.
         * @param end The last tree_node of the path.
        */

        std::vector<GameState*> shortestPath(tree_node* end);

        /**
         * @brief Returns a vector of Gamestate with all possible moves.
         * @return A vector of Gamestate with all possible moves.
         */
        vector<GameState*> neighbours(const GameState* _game);


};