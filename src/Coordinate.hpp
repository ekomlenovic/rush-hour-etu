/**
 * @file Coordinate.hpp
 * @brief This file contains the declaration of the Coordinate class.
 */

#pragma once
/**
 * @class Coordinate
 * @brief The Coordinate class represents a point in two-dimensional space.
 */
class Coordinate{
    private:
        int x; /**< An integer representing the X coordinate of the point. */
        int y; /**< An integer representing the Y coordinate of the point. */
    public:
        Coordinate();
        /**
         * @brief Constructor for Coordinate.
         * @param _x The x coordinate of the point.
         * @param _y The y coordinate of the point.
         */
        Coordinate(int _x, int _y);
        /**
         * @brief Gets the x coordinate of the point.
         * @return The x coordinate of the point.
         */
        int getX() const;
        /**
         * @brief Gets the y coordinate of the point.
         * @return The y coordinate of the point.
         */
        int getY() const;


        /**
         * @brief Sets the x coordinate of the point.
         * @param _x The new x coordinate of the point.
         * @return The new x coordinate of the point.
         */
        int setX(int _x);

        /**
         * @brief Sets the y coordinate of the point.
         * @param _y The new y coordinate of the point.
         * @return The new y coordinate of the point.
         */
        int setY(int _y);
};