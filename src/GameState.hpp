#pragma once
/**
 * @file GameState.hpp
 * @brief This file contains the declaration of the GameState class, which represents the state of the game.
 */
#include <vector>
#include <string>

#include "Vehicule.hpp"
#include "Coordinate.hpp"

using namespace std;
/**
 * @class GameState
 * @brief The GameState class represents the state of the game.
 */
class GameState{
    private :
        Vehicule* mainVehicule; /**< A pointer to the main vehicle in the game. */
        std::vector<Vehicule*> listVehicule;  /**< A vector of all vehicles in the game. */
        int mapSize;   /**< An integer representing the size of the game map. */
        Coordinate exit; /**< A Coordinate representing the exit of the game. */
        string generateSVGExport();
        string generateSVGExport(const GameState *state);
        string generateRectSvgCode(int&, float, float, float, float, string color="#000000");
        string generateRectSvgCode(int&, Vehicule*, string color="#000000");
        string generateRectSvgCode(int&, Coordinate*, string color="#000000");
        string generateTextSvgCode(int&, float, float, string text);

        int nbMove; /**< An integer representing the number of moves made in the game(for svg export). */

        /**
         * @brief Reads the game map file.
         * @param filepath A string representing the file path to the game map.
         */
        void readMapFile(const string &filepath);


    public:
        /**
         * @brief Writes the game map file.
         * @param filepath A string representing the file path to the game map.
         * @param listVehicule A vector of all vehicles in the game.    
         */
        void writeMapFile(const string &filepath);

        //CONSTRUCTORS


        /**
         * @brief Default constructor that builds a random map
        */
        GameState();


        /**
         * @brief Copy constructor for the GameState class.
         * @param gameState A const reference to the GameState object to copy.
        */
        GameState(const GameState &gameState);

        /**
         * @brief Constructor for the GameState class.
         * @param filePath A string representing the file path to the game map.
         */
        GameState(const string &filePath);

        /**
         * @brief Destructor for the GameState class.
        */
        ~GameState();

        //GETTER AND SETTERS

        /**
         * @brief get the exit coordinate
        */
        Coordinate getExit() const;

        /**
         * @brief Returns the vector of vehicles in the game.
         * @return A const reference to the vector of vehicles in the game.
         */
        std::vector<Vehicule*> getListVehicule() const;

        /**
         * @brief Returns the main vehicle in the game.
         * @return A const pointer to the main vehicle in the game.
         */
        Vehicule* getMainVehicule() const;

        /**
         * @brief Sets the exit coordinate.
         * @param exit A const reference to the new exit coordinate.
        */
        void setExit(const Coordinate);

        /**
         * @brief Add a vehicle to the std::vector<Vehicule*> listVehicule
         * @param toAdd A pointer to the vehicle to add.
        */
        void addVehicule(Vehicule* toAdd);

        /**
         * @brief Delete and remove all vehicles from the std::vector<Vehicule*> listVehicule
        */
        void clearVehicule();

        /**
         * @brief Returns the size of the game map.
         * @return An integer representing the size of the game map.
         */
        int getMapSize();

        /**
         * @brief set the main vehicle of the game
         * @param main A pointer to the new main vehicle of the game
        */
        void setMainVehicule(Vehicule* main);

        //MOVE METHODS

        /**
         * @brief Plays a move.
         * @param toMove A pointer to the vehicle to move.
         * @param distance An integer representing the distance to move the vehicle.
        */
        bool playMove(Vehicule* toMove , int distance);

        /**
         * @brief Determines whether the player has won the game.
         * @return A boolean value indicating whether the player has won the game.
         */
        bool victory();

        /**
         * @brief Determines whether a move is legal.
         * @param toMove A pointer to the vehicle to move.
         * @param distance An integer representing the distance to move the vehicle.
        */
        bool legalMove(const Vehicule* toMove, int distance);

        /**
         * @brief Determines whether a vehicle can stay in the map.
         * @param v A pointer to the vehicle to move.
         * @param distance An integer representing the distance to move the vehicle.
        */
        bool stayInmap(Vehicule* v, int distance);

        /**
         * @brief check if the vehicle can move over a certain distance (deplacement)
         * @param toMove A pointer to the vehicle to move.
         * @param frontVehicule A vector of all vehicles in front of the vehicle to move.
         * @param deplacement An integer representing the distance to move the vehicle.
        */
        bool distanceTo(const Vehicule* toMove, vector<Vehicule*> frontVehicule, int deplacement);

        //EXPORT METHODS

        /**
        * @brief Exports the game map to a SVG file.
        * @param filepath A string representing the file path to the game map.
        */
        void exportMapSvg(string);

        /**
         * @brief Returns a string representation of the game state.
        */
        string to_string();

        /**
         * @brief Returns if the objective is reachable
         * @param objective A Coordinate representing the objective
        */
        bool isReachable(Coordinate objective);


        /**
         * @brief Returns a vector of all vehicles on the same line as x.
         * @param x An integer representing the line.
        */
        vector<Vehicule*> getListVehiculeOnLine(int x);

       
        /**
         * @brief Returns a vector of all vehicles on the same column as y.
         * @param y An integer representing the column.
        */
        vector<Vehicule*> getListVehiculeOnColumn(int y);


        //OPERATOR
        /**
         * @brief Operator = for gamestate
         * @param gameState A const reference to the GameState object to copy.
        */
        GameState operator=(const GameState &gameState);

        /**
         * @brief Overloads the equality operator for Gamestate objects.
         * @param game1 The first Gamestate object to compare.
         * @param game2 The second Gamestate object to compare.
         * @return True if the two Gamestate objects are equal, false otherwise.
        */
        friend bool operator==(const GameState &game1, const GameState &game2);

        /**
         * @brief Overloads the less than operator for Gamestate objects.
         * @param game1 The first Gamestate object to compare.
         * @param game2 The second Gamestate object to compare.
         * @return True if the first Gamestate object is less than the second one, false otherwise.
        */
        friend bool operator<(const GameState &game1, const GameState &game2);

        /**
         * @brief Operator = for gamestate&
         * @param other A reference to the GameState object to copy.
        */
        GameState& operator=(GameState& other);


};