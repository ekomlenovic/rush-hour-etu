/**
 * @file PuzzleGenerator.cpp
 * @brief This file contains the implementation of the PuzzleGenerator class.
*/

#include "PuzzleGenerator.hpp"
#include "utilities.hpp"

PuzzleGenerator::PuzzleGenerator(){
    srand(time(NULL));
}

GameState PuzzleGenerator::dijkstraGeneration()
{
    GameState result;
    result.clearVehicule();
    bool remainingPlace = true;
    int nbVehicule = 0;
    baseSituation(result);
    vector<GameState> neighbourhood;
    do{
        neighbourhood = neighbours(result);
        if (!neighbourhood.empty()){
            vector<int> scores = evaluateNeighbours(neighbourhood);
            vector<int> bestNeighboursIndex = selectNeighbour(scores);
            int index = bestNeighboursIndex[getRandomNumber(0,bestNeighboursIndex.size()-1)];
            if (scores[index]!=0){
                result = neighbourhood[index];
                nbVehicule++;
            }
            else{
                remainingPlace = false;
            }
        }
    }while(!neighbourhood.empty() && nbVehicule < 15 && remainingPlace);
    return result;
}

GameState PuzzleGenerator::naiveGeneration(){
    GameState result;
    result.clearVehicule();
    int maxTry = 20;
    unsigned int maxDifficulty = 0;
    Solver solv;
    for (int i = 0; i < maxTry;i++){
        GameState g;
        g.clearVehicule();
        randomFillMap(g);
        vector<GameState*> soluce = solv.BFS(&g);
        if (!soluce.empty() && soluce.size() > maxDifficulty){
            result = g;
        }
        destroy_vec_gamestate(soluce);
    }
    return result;
}

void PuzzleGenerator::randomFillMap(GameState & g)
{
    baseSituation(g);

    //Attempting to add 15 vehicules to the map
    int maxVehicule = 15;
    for (int i = 0; i < maxVehicule;i++){
        addRandomVehicule(g);
    }

}

vector<vector<int>> PuzzleGenerator::convertGameStateToTab(GameState g)
{
    /**
     * if the place's empty : 0
     * else : car position in the vector (+1)
    */

    vector<vector<int>> result;
    //Filling the map with "0"
    for (int i = 0; i < 6;i++){
        result.push_back(vector<int>());
        for (int j = 0; j < g.getMapSize();j++){
            result[i].push_back(0);
        }
    }
    vector<Vehicule*> listVehicule = g.getListVehicule();
    for (unsigned int i = 0; i < listVehicule.size();i++){
        Vehicule* current = listVehicule[i];
        if (current->getHorizontal()){
            for (int j = current->getY();j< current->getY()+current->getSize();j++){
                result[current->getX()][j] = i+1;
            }
        }
        else{
            for (int j = current->getX();j < current->getX()+current->getSize();j++){
                result[j][current->getY()] = i+1;
            }
        }
    }

    return result;
}

void PuzzleGenerator::revealFreePlaces(GameState g,vector<vector<int>> &parking)
{   
    for (unsigned int i = 0; i < parking.size();i++){
        for (unsigned int j = 0; j< parking[i].size();j++){
            if (i+1 >= (unsigned int)g.getMapSize() && j+1 >= (unsigned int)g.getMapSize()){
                continue;
            }
            else if (parking[i][j]==0){
                if (i+1 >= (unsigned int)g.getMapSize()&& parking[i][j+1]==0){
                    parking[i][j] = -1;
                }
                if (j+1 >= (unsigned int)g.getMapSize() && parking[i+1][j]==0){
                    parking[i][j] = -1;
                }
                if (j+1 < (unsigned int)g.getMapSize() && i+1 < (unsigned int)g.getMapSize() && (parking[i][j+1]==0 || parking[i+1][j]==0)){
                    parking[i][j] = -1;
                }
            }
        }
    }
}

vector<Vehicule> PuzzleGenerator::allVehiculeOnPlace(GameState g, Coordinate place)
{
    //TODO : Rework, fetching member fun used
    vector<vector<int>> parking =  convertGameStateToTab(g);
    revealFreePlaces(g,parking);
    vector<Vehicule> result;
    bool placeable = true;
    if (parking[place.getY()][place.getX()]==-1){
        //Vertical

        //2 size : 2 and 3
        for (int size = 2; size<4;size++){

            if ((getOccupiedSpaceOnColumn(g,place.getX())+size)>=5){
                placeable = false;
            }

            //OUT of bound verif
            if (place.getY()+(size-1) >= g.getMapSize()){
                placeable = false;
            }


            //collision verif
            else{
                for (int i = place.getY(); i < place.getY()+size;i++){
                    if(parking[i][place.getX()]>0){
                        placeable = false;
                    }
                }
            }


            if (placeable){
                result.push_back(Vehicule(place.getY(),place.getX(),size,false));
            }
            placeable = true;
        }
        
        //Horizontal
        for (int size = 2; size<4;size++){ 
            
            
            if ((getOccupiedSpaceOnLine(g,place.getY())+size)>=5){
                placeable = false;
            }


            //Verif line main vehicule       
            if (place.getY()==g.getMainVehicule()->getX()){
                placeable=false;
            }

            //Verif out of bound
            if (place.getX()+(size-1) >= g.getMapSize()){
                placeable = false;
            }



            //Verif collision
            else{
                for (int i = place.getX(); i < place.getX()+size;i++){
                    if(parking[place.getY()][i]>0){
                        placeable = false;
                    }
                }
            }


            if (placeable){
                result.push_back(Vehicule(place.getY(),place.getX(),size,true));
            }
            placeable = true;
        }
    }
    return result;
}

vector<Coordinate> PuzzleGenerator::freePlaces(GameState g)
{
    vector<Coordinate> result;
    vector<vector<int>> parking = convertGameStateToTab(g);

    for (unsigned int i = 0; i < parking.size();i++){
        for (unsigned int j = 0; j< parking[i].size();j++){
            if (i+1 >= (unsigned int)g.getMapSize() && j+1 >= (unsigned int)g.getMapSize()){
                //continue;
            }
            else if (parking[i][j]==0){
                if (i+1 >= (unsigned int)g.getMapSize()&& parking[i][j+1]==0){
                    result.push_back(Coordinate(j,i));
                }
                else if (j+1 >= (unsigned int)g.getMapSize() && parking[i+1][j]==0){
                    result.push_back(Coordinate(j,i));
                }
                else if (j+1 < (unsigned int)g.getMapSize() && i+1 < (unsigned int)g.getMapSize() && (parking[i][j+1]==0 || parking[i+1][j]==0)){
                    result.push_back(Coordinate(j,i));
                }
            }
        }
    }

    return result;
}

int PuzzleGenerator::getOccupiedSpaceOnLine(GameState g, int line)
{
    int result = 0;
    vector<Vehicule*> vehiculeOnLine = g.getListVehiculeOnLine(line);
    for (unsigned int i = 0; i < vehiculeOnLine.size();i++){
        if (vehiculeOnLine[i]->getHorizontal()){
            result+= vehiculeOnLine[i]->getSize();
        }
    }
    return result;
}

int PuzzleGenerator::getOccupiedSpaceOnColumn(GameState g, int column)
{
    int result = 0;
    vector<Vehicule*> vehiculeOnColumn = g.getListVehiculeOnColumn(column);
    for (unsigned int i = 0; i < vehiculeOnColumn.size();i++){
        if (!vehiculeOnColumn[i]->getHorizontal()){
            result+=vehiculeOnColumn[i]->getSize();
        }
    }
    return result;
}

void PuzzleGenerator::addRandomVehicule(GameState& g)
{
    vector<Coordinate> places = freePlaces(g);
    if (!places.empty()){
        int selectedPlace = getRandomNumber(0,places.size()-1);
        vector<Vehicule> vehicules = allVehiculeOnPlace(g,places[selectedPlace]);
        if (!vehicules.empty()){
            int selectedVehicule = getRandomNumber(0, vehicules.size()-1);
            g.addVehicule(new Vehicule(vehicules[selectedVehicule].getX(), vehicules[selectedVehicule].getY(),
                                        vehicules[selectedVehicule].getSize(),vehicules[selectedVehicule].getHorizontal()));
        }
    }
}

void PuzzleGenerator::baseSituation(GameState & g)
{
    g.clearVehicule();
    //Generating exit
    Coordinate exit = Coordinate(getRandomNumber(0,5),5);
    g.setExit(exit);


    //Generating main vehicule
    int mainVehiculeSize = getRandomNumber(2,3);
    g.addVehicule(new Vehicule(exit.getX(), 0, mainVehiculeSize, true));
    g.setMainVehicule(g.getListVehicule()[0]);
}

vector<GameState> PuzzleGenerator::neighbours(GameState g)
{
    vector<GameState> result;
    vector<Coordinate> places = freePlaces(g);
    GameState created = g;

    if (!places.empty()){
        for (unsigned int i =0; i < places.size();i++){
            vector<Vehicule> vehicules = allVehiculeOnPlace(g,places[i]);
            if (!places.empty()){
                for (unsigned int i =0; i < vehicules.size();i++){
                    GameState created = g;
                    created.addVehicule(new Vehicule(vehicules[i]));
                    result.push_back(created);
                }
            }
        }
    }
    return result;
}

vector<int> PuzzleGenerator::evaluateNeighbours(vector<GameState> neighbours)
{   
    Solver solv;
    vector<int> result;
    for (unsigned int i =0; i < neighbours.size();i++){
        vector<GameState*> tmp = solv.BFS(&neighbours[i]);
        result.push_back(tmp.size());
        destroy_vec_gamestate(tmp);
    }
    return result;
}

vector<int> PuzzleGenerator::selectNeighbour(vector<int> scores)
{
    vector<int> indexes;
    if (!scores.empty()){
        //finding max
        int indexMax = 0;
        for (unsigned int i = 0; i < scores.size();i++){
            if (scores[i]>scores[indexMax]){
                indexMax = i;
            }
        }

        int maxValue = scores[indexMax];

        for (unsigned int i = 0; i < scores.size();i++){
            if (scores[i]==maxValue){
                indexes.push_back(i);   
            }
        }
    }
    return indexes;
}

