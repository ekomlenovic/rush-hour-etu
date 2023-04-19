/**
 * @file Coordinate.cpp
 * @brief This file contains the implementation of the Coordinate class.
*/
#include "Coordinate.hpp"

Coordinate::Coordinate(){
    x = 0; 
    y = 0;
}
Coordinate::Coordinate(int _x, int _y){
    x= _x;
    y = _y;
}

int Coordinate::getX() const{
    return x;
}

int Coordinate::getY() const{
    return y;
}

int Coordinate::setX(int _x){
    x = _x;
    return x;
}

int Coordinate::setY(int _y){
    y = _y;
    return y;
}