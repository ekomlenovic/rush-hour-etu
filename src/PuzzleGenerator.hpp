/**
 * @file PuzzleGenerator.hpp
 * @brief This file contains the declaration of the PuzzleGenerator class.
*/

#include <iostream>
#include "Solver.hpp"

class PuzzleGenerator{

    private :
        //NAIVE VER PV METHODS

        /**
         * @brief Randomly fill a map
         * @param game Reference to a game situation that will be filled
        */
        void randomFillMap(GameState& game);

        /**
         * @brief Add a random vehicule to a map if possible
        */
        void addRandomVehicule(GameState& g);

        /**
         * @brief Convert a gameState to a 2D tab representing every vehicules
        */
        vector<vector<int>> convertGameStateToTab(GameState game);

        /**
         * @brief Set -1 on a 2D vector if a vehicule is placeable
        */
        void revealFreePlaces(GameState,vector<vector<int>>& parking);

        /**
         * @brief Find all possible vehicule on a specified place
        */
        vector<Vehicule> allVehiculeOnPlace(GameState g, Coordinate place);


        /**
         * @brief Find every place where a vehicule can be added
        */
        vector<Coordinate> freePlaces(GameState);

        /**
         * @return Number of space left on a specified line for a given gamestate
        */
        int getOccupiedSpaceOnLine(GameState g, int line);

        /**
         * @return Number of space left on a specified column for a given gamestate
        */
        int getOccupiedSpaceOnColumn(GameState g, int column);

        //DIJKSTRA VER PV METHODS

        /**
         * @brief Add the exit and the main vehicule to a GameState
         * @param game Reference to the edited GameState
        */
        void baseSituation(GameState& game);

        /**
         * @brief Returns a vector containing every neighbours for a given situation
         * @return Vector containing the given gamestate + 1 vehicule
        */
        vector<GameState> neighbours(GameState game);

        /**
         * @brief Compute the minimal number of move to resolve every gamestate
        */
        vector<int> evaluateNeighbours(vector<GameState> neighbours);

        /**
        * @return Vector containing indexes of longest shortest path
       */
        vector<int> selectNeighbour(vector<int>);


    public :
        PuzzleGenerator();
        //DIJKSTRA

        /**
         * @brief Generate a puzzle using a derived dijkstra algorithm
         * @return A base game situation
        */
        GameState dijkstraGeneration();

        //NAIVE
        /**
         * @brief Generate n completely random puzzle and select the hardest one
         * @return A base game situation
        */
        GameState naiveGeneration();

};