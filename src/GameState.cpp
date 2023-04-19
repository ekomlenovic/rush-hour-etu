/**
 * @file GameState.cpp
 * @brief This file contains the implementation of the GameState class.
*/

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
#include <algorithm>

#include "GameState.hpp"
#include "Solver.hpp"

using namespace std;

GameState::GameState(const string &filepath):exit(-1,-1){
    readMapFile(filepath);
    mapSize = 6;
    nbMove = 0;
}

/**
 * construteur par copie profonde
*/
GameState::GameState(const GameState & gameState):exit(gameState.exit){
    this->mapSize = gameState.mapSize;
    this->nbMove = gameState.nbMove;
    for (unsigned int i = 0; i < gameState.listVehicule.size(); i++){
        this->listVehicule.push_back(new Vehicule(*gameState.listVehicule[i]));
    }
    this->mainVehicule = listVehicule.at(0);
}

GameState::~GameState(){
    for (unsigned int i = 0; i < listVehicule.size(); i++){
        delete listVehicule[i];
    }
    listVehicule.clear();
}
void GameState::readMapFile(const string &filepath){
    string buffer;
    ifstream file(filepath);
    if (file.is_open()){
        //Level parsing
        getline(file, buffer);
        int exitX = stoi(buffer.substr(0,1));
        int exitY = stoi(buffer.substr(2,3));
        exit = Coordinate(exitX, exitY);
        while(getline(file, buffer)){
            int posX =  stoi(buffer.substr(0,1));
            int posY = stoi(buffer.substr(2,3));
            int size =  stoi(buffer.substr(4,5));
            bool horizontal = stoi(buffer.substr(6,7));
            listVehicule.emplace_back(new Vehicule(posX, posY, size, horizontal));
        }
        file.close();
        mainVehicule =  listVehicule.at(0);

        cout << "Loaded " << listVehicule.size() << " vehicules !" << endl;
    }
    else{
        cerr << "Fichier non lu" << endl;
    }
}

string GameState::generateSVGExport(){
    int rectId = 1;

    //Header
    string result = "<svg width=\"2000mm\" height=\"2000mm\" viewBox=\"0 0 2000 2000\" version=\"1.1\" id=\"svg5\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:svg=\"http://www.w3.org/2000/svg\">";
    
    //Initialisation
    string frame =generateRectSvgCode(rectId, 5,5,82,82);
    string mainVehicule = "";
    if (!listVehicule.empty()){
        mainVehicule = generateRectSvgCode(rectId, listVehicule[0], "#FF0000");
    }
    string frameOpening = generateRectSvgCode(rectId, &exit, "#FFFFFF");
    string text = generateTextSvgCode(rectId,340,330,std::to_string(nbMove));
    result += frame + frameOpening+ mainVehicule+text;

    //Adding vehicules
    for (unsigned int i = 1; i < listVehicule.size();i++){
        result+=generateRectSvgCode(rectId, listVehicule[i]);
    }
    result += "</svg>";

    return result;
}

string GameState::generateRectSvgCode(int& rectId, float _x, float _y, float _width, float _height, string color){
    string result = "<rect style=\"fill:#ffffff;stroke-width:0.264583;stroke:";
    result+=color+";stroke-opacity:1\" id=\"rect" + std::to_string(rectId);
    result += "\" width=\"" + std::to_string(_width);
    result += "\" height=\"" + std::to_string(_height);
    result += "\" x=\""+std::to_string((_y));
    result += "\" y=\""+std::to_string((_x)) + "\" />\n";
    rectId++;
    return result;
}

Coordinate GameState::getExit() const{
    return exit;
}
string GameState::generateRectSvgCode(int& rectId,Vehicule* v, string color){
    int width, height, x, y;
    int margin=3;

    x = v->getX()*10+5+(margin*(v->getX()+1));
    y = v->getY()*10+5+(margin*(v->getY()+1));
    if (v->getHorizontal()){
        width = v->getSize()*10+(margin*(v->getSize()-1));
        height = 10;
    }
    else{
        width= 10;
        height = v->getSize()*10+(margin*(v->getSize()-1));
    }

    return generateRectSvgCode(rectId,x, y, width, height, color);

}

string GameState::generateRectSvgCode(int& rectId, Coordinate* c, string color){
    float x,y, width = 10, height = 10;
    int margin =3;
    int gapX = 0, gapY = 0;
    if (c->getX()== 0){
        gapX = -5;
    }
    else if (c->getX() == mapSize-1){
        gapX = 5;
    }
    if (c->getY()== 0){
        gapY = -5;
    }
    else if(c->getY()==mapSize-1){
        gapY = 5;
    }

    if (c->getX()==c->getY() || c->getX()-c->getY()==-5 || c->getX()-c->getY()==5){
        width*=1.75;
        height*= 1.75;
        if(c->getX()==mapSize-1){
            gapX-=7.5;
        }
        if (c->getY()==mapSize-1){
            gapY -= 7.5;
        }
    }
    x = c->getX()*10+5+(margin*(c->getX()+1))+gapX;
    y = c->getY()*10+5+(margin*(c->getY()+1))+gapY;

    return generateRectSvgCode(rectId, x,y,width,height, color);
}

string GameState::generateTextSvgCode(int &id, float x, float y, string text){
    string result = "<text xml:space=\"preserve\" transform=\"scale(0.26458333)\" id=\"text" + std::to_string(id) +"\"";
    result+=" style=\"font-style:normal;font-weight:normal;font-size:10px;line-height:1.25;font-family:sans-serif;white-space:pre;shape-inside:url(#rect2299);fill:#000000;fill-opacity:1;stroke:none\">";
    result+=" <tspan x=\"" + std::to_string(y);
    result += "\" y=\"" + std::to_string(x);
    result+="\" id=\"tspan"+std::to_string(id+1)+"\">"+text+"</tspan></text>";

    id+=2;
    return result;
}

void GameState::exportMapSvg(string filepath){
    ofstream file (filepath);
    if (file.is_open()){
        file << generateSVGExport() << endl;
        file.close();
    }
    else{
        cerr << "Error on export" << endl;
    }
}

string GameState::generateSVGExport(const GameState *state){
        int rectId = 1;

        //Header
        string result = "<svg width=\"2000mm\" height=\"2000mm\" viewBox=\"0 0 2000 2000\" version=\"1.1\" id=\"svg5\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:svg=\"http://www.w3.org/2000/svg\">";
        
        //Initialisation
        string frame =generateRectSvgCode(rectId, 5,5,82,82);
        string mainVehicule = generateRectSvgCode(rectId, state->listVehicule[0], "#FF0000");
        string frameOpening = generateRectSvgCode(rectId, state->exit.getX()*15+2.5, state->exit.getY()*15+2.5, 10,10, "#FFFFFF");
        result += frame + mainVehicule + frameOpening;

        //Adding vehicules
        for (unsigned int i = 1; i < state->listVehicule.size();i++){
            result+=generateRectSvgCode(rectId, state->listVehicule[i]);
        }

        result += "</svg>";

        return result;
}

void GameState::writeMapFile(const string &filepath){
    ofstream file(filepath);
    if (file.is_open()){
        file << this->to_string();
        file.close();
    }
}



std::string GameState::to_string(){
    std::string result = std::to_string(exit.getX()) + " "+ std::to_string(exit.getY())+"\n" ;
    for (unsigned int i = 0; i < listVehicule.size();i++){
        result+=std::to_string(listVehicule[i]->getX())+" "+std::to_string(listVehicule[i]->getY())+" "+
        std::to_string(listVehicule[i]->getSize())+" "+std::to_string(listVehicule[i]->getHorizontal())+"\n";
    }
    return result;
}



vector<Vehicule*> GameState::getListVehicule() const{
    return listVehicule;
}

Vehicule* GameState::getMainVehicule() const{
    return mainVehicule;
}

void GameState::setExit(const Coordinate _exit)
{
    exit = _exit;
}

void GameState::addVehicule(Vehicule *toAdd)
{
    listVehicule.push_back(toAdd);
}

void GameState::clearVehicule()
{
    for(Vehicule* v : listVehicule){
        delete v;
    }
    listVehicule.clear();
}

int GameState::getMapSize()
{
    return mapSize;
}

void GameState::setMainVehicule(Vehicule *main)
{
    mainVehicule = main;
}

bool GameState::stayInmap(Vehicule* v, int distance){
    if (v->getHorizontal()){
        return (v->getY() + distance >= 0 && v->getY() + distance + v->getSize() <= mapSize);
    }
    else{
        return (v->getX() + distance >= 0 && v->getX() + distance + v->getSize() <= mapSize);
    }
}

bool GameState::playMove(Vehicule* toMove, int distance){

    if(toMove->getHorizontal()){
        if(stayInmap(toMove, distance) && legalMove(toMove, distance)){
            toMove->setY(toMove->getY() + distance);
            nbMove++;
            return true;
        }
    }
    else{
        if(stayInmap(toMove, distance) && legalMove(toMove, distance)){
            toMove->setX(toMove->getX() + distance);
            nbMove++;
            return true;
        }
    }
    return false;
}


vector<Vehicule*> GameState::getListVehiculeOnLine(int x){
    vector<Vehicule*> listVehiculeOnLine;
    for(unsigned int i = 0; i < listVehicule.size() ; i++){
        if(listVehicule[i]->getHorizontal()){
            if(listVehicule[i]->getX() == x){
                listVehiculeOnLine.push_back(listVehicule[i]);
            }
        }else{
            for(int j = 0; j < listVehicule[i]->getSize(); j++){
                if(listVehicule[i]->getX() + j == x){
                    listVehiculeOnLine.push_back(listVehicule[i]);
                }
            }
        }
    }
    return listVehiculeOnLine;
}

vector<Vehicule*> GameState::getListVehiculeOnColumn(int y){
    vector<Vehicule*> listVehiculeOnColumn;
    for(unsigned int i = 0; i < listVehicule.size() ; i++){
        if(!listVehicule[i]->getHorizontal()){
            if(listVehicule[i]->getY() == y){
                listVehiculeOnColumn.push_back(listVehicule[i]);
            }
        }else{
            for(int j = 0; j < listVehicule[i]->getSize(); j++){
                if(listVehicule[i]->getY() + j == y){
                    listVehiculeOnColumn.push_back(listVehicule[i]);
                }
            }
        }
    }
    return listVehiculeOnColumn;
}

GameState& GameState::operator=(GameState& other)
{
    std::swap(mapSize, other.mapSize);
    std::swap(listVehicule, other.listVehicule);
    std::swap(exit, other.exit);
    std::swap(mainVehicule, other.mainVehicule);
    std::swap(nbMove, other.nbMove);
    return *this;
}

void checkvectorequal(int i, const Vehicule* toMove, vector<Vehicule*> &v){
    while(v[i]->getX() == toMove->getX() && v[i]->getY() == toMove->getY()){
        v.erase(v.begin() + i);
    }
}

void removeToMove(const Vehicule* toMove, vector<Vehicule*> &v){
    for (unsigned int i = 0; i < v.size();i++){
        if (v[i] == toMove){
            v.erase(v.begin()+i);
            return;
        }
    }
}


bool GameState::legalMove(const Vehicule* toMove, int distance){
    vector<Vehicule*> v;
    if(toMove->getHorizontal()){
        v = getListVehiculeOnLine(toMove->getX());

    }
    else{
        v = getListVehiculeOnColumn(toMove->getY());
    }
    removeToMove(toMove,v);
    return distanceTo(toMove,v,distance);
}


bool GameState::victory(){
    if (mainVehicule->getHorizontal()){
        return (mainVehicule->getX() == exit.getX() && mainVehicule->getY()+mainVehicule->getSize()-1 == exit.getY());
    }
    else{
        return(mainVehicule->getX()-mainVehicule->getSize()-1 == exit.getX() && mainVehicule->getY() == exit.getY());
    }
}

bool GameState::isReachable(Coordinate objective){
    if (mainVehicule->getHorizontal()){
        return (mainVehicule->getX() == objective.getX() && (mainVehicule->getY()+mainVehicule->getSize()-1 == objective.getY() || mainVehicule->getY() == objective.getY()));
    }
    else{
        return((mainVehicule->getX()-mainVehicule->getSize()-1 == objective.getX() || mainVehicule->getX() == objective.getX()) && mainVehicule->getY() == objective.getY());
    }
}

GameState GameState::operator=(const GameState &gameState){
    this->mapSize = gameState.mapSize;
    this->nbMove = gameState.nbMove;
    this->exit = gameState.exit;
    this->mainVehicule = gameState.mainVehicule;
    this->listVehicule = gameState.listVehicule;
    return *this;
}

bool operator==(const GameState &game1, const GameState &game2) {
    if(game1.getMainVehicule()->getX() == game2.getMainVehicule()->getX() && game1.getMainVehicule()->getY() == game2.getMainVehicule()->getY() && game1.exit.getX() == game2.exit.getX() && game1.exit.getY() == game2.exit.getY()){
        for(unsigned int i = 0; i < game1.getListVehicule().size(); i++){
            if(game1.getListVehicule()[i]->getX() != game2.getListVehicule()[i]->getX() || game1.getListVehicule()[i]->getY() != game2.getListVehicule()[i]->getY()){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool GameState::distanceTo(const Vehicule* toMove, vector<Vehicule*> frontVehicule, int deplacement){
    std::vector<int> distances;
    if (toMove->getHorizontal()){
        for (unsigned int i = 0; i < frontVehicule.size();i++){
            //Si le véhicule est a gauche
            if (frontVehicule[i]->getY()<toMove->getY()){
                //Faut prendre en compte la longueur du vehicule a gauche
                int distance = frontVehicule[i]->getY() - toMove->getY();
                if (frontVehicule[i]->getHorizontal()){
                    distance+= frontVehicule[i]->getSize()-1;
                } 
                //distance *= -1;
                distances.push_back(distance);
            }
            else{
                int distance = toMove->getY() + toMove->getSize()-1 - frontVehicule[i]->getY();
                distance *= -1;
                distances.push_back(distance);
                //Faut prendre en compte la longueur du vehicule a deplacer
            
            }    
        }
    }
    //vertical
    else{
        for (unsigned int i = 0; i < frontVehicule.size();i++){
            //Si le vehicule est au dessus
            if (frontVehicule[i]->getX() < toMove->getX()){
                //Faut prendre en compte la longueur du vehicule a gauche
                int distance = frontVehicule[i]->getX()-toMove->getX(); 
                if (!frontVehicule[i]->getHorizontal()){
                    distance+=frontVehicule[i]->getSize()-1;  
                }
                //distance *= -1;
                distances.push_back(distance);
            }
            //si le vehciule est au dessous
            else{
                //Faut prendre en compte la longueur du vehicule a deplacer
                int distance = toMove->getX() + toMove->getSize()-1 - frontVehicule[i]->getX();

                distance *= -1;
                distances.push_back(distance);
            }
        }
    }

    if (deplacement < 0){
        for (unsigned int i = 0; i<distances.size();i++){
            if (distances[i] <= 0 && distances[i] >= deplacement){
                return false;   
            }
        }
    }
    else{
        for (unsigned int i = 0; i<distances.size();i++){
            if (distances[i] >= 0 && distances[i] <= deplacement){
                return false;   
            }
        }
    }

    return true;
}

bool operator<(const GameState &game1, const GameState &game2) {
    vector<Vehicule*> list_game1 = game1.getListVehicule();
    vector<Vehicule*> list_game2 = game2.getListVehicule();
    for(unsigned int i = 0; i < list_game1.size(); i++){
        if(list_game1[i]->getX() < list_game2[i]->getX()){
            return true;
        }else if(list_game1[i]->getY() < list_game2[i]->getY()){
            return true;
        }else if(list_game1[i]->getSize() < list_game2[i]->getSize()){
            return true;
        }else if(list_game1[i]->getHorizontal() < list_game2[i]->getHorizontal()){
            return true;
        }
    }
    if(game1.getExit().getX() < game2.getExit().getX()){
        return true;
    }else if(game1.getExit().getY() < game2.getExit().getY()){
        return true;
    }
    return false;
}



GameState::GameState(){
    //Var init
    nbMove = 0;
    mapSize =6;
    exit = Coordinate(0,0);
    listVehicule.push_back(new Vehicule(0,0,2,true));
    mainVehicule = listVehicule[0];
}



