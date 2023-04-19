/**
 * @file Vehicule.hpp
 * @brief This file contains the declaration of the Vehicule class.
 */
#pragma once
#include "Coordinate.hpp"


/**
 * @brief The Vehicule class represents a vehicle. 
 * 
 * Vehicles have a location represented by a Coordinate object, a size, and a direction (horizontal or vertical).
 */
class Vehicule{
    private:
        Coordinate location; /**< The location of the vehicle. */
        int size; /**< The size of the vehicle. */
        bool horizontal;  /**< Whether the vehicle is horizontal (true) or vertical (false). */
    public:

        /**
         * @brief Constructor for Vehicule.
         * @param _x The x coordinate of the vehicle's location.
         * @param _y The y coordinate of the vehicle's location.
         * @param _size The size of the vehicle.
         * @param _horizontal Whether the vehicle is horizontal (true) or vertical (false).
         */
        Vehicule(int _x, int _y, int _size, bool _horizontal);


        Vehicule(const Vehicule &vehicule);

        /**
         * @brief Gets the x coordinate of the vehicle's location.
         * @return The x coordinate of the vehicle's location.
         */
        int getX() const;

        /**
         * @brief Gets the y coordinate of the vehicle's location.
         * @return The y coordinate of the vehicle's location.
         */
        int getY() const;

        /**
         * @brief Gets the size of the vehicle.
         * @return The size of the vehicle.
         */
        int getSize() const;

        /**
         * @brief Gets whether the vehicle is horizontal or vertical.
         * @return true if the vehicle is horizontal, false if it is vertical.
         */
        bool getHorizontal() const;

        /**
         * @brief Sets the x coordinate of the vehicle's location.
         * @param _x The new x coordinate of the vehicle's location.
         * @return The new x coordinate of the vehicle's location.
         */
        int setX(int _x);

        /**
         * @brief Sets the y coordinate of the vehicle's location.
         * @param _y The new y coordinate of the vehicle's location.
         * @return The new y coordinate of the vehicle's location.
         */
        int setY(int _y);

};