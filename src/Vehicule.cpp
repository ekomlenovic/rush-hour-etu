/**
 * @file Vehicule.cpp
 * @brief This file contains the implementation of the Vehicule class.
*/
#include <cstdlib>
#include <iostream>
#include "Vehicule.hpp"

        

Vehicule::Vehicule(int _x, int _y, int _size, bool _horizontal):location(_x,_y){
    size = _size;
    horizontal = _horizontal;
}

Vehicule::Vehicule(const Vehicule &vehicule):location(vehicule.getX(),vehicule.getY()){
    size = vehicule.size;
    horizontal = vehicule.horizontal;
}

int Vehicule::getX() const{
    return location.getX();
}

int Vehicule::getY() const{
    return location.getY();
}


int Vehicule::getSize() const{
    return size;
}

bool Vehicule::getHorizontal() const{
    return horizontal;
}

int Vehicule::setX(int _x){
    return location.setX(_x);
}

int Vehicule::setY(int _y){
    return location.setY(_y);
}
