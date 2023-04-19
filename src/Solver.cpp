/**
 * @file Solver.cpp
 * @brief This file contains the implementation of the Solver class.
*/

#include <iostream>
#include <algorithm>

#include "Solver.hpp"


vector<GameState*> Solver::BFS_aux(GameState* start, Coordinate objetive, vector<tree_node*> &nodes){
    GameState * tmp = new GameState(*start);
    std::queue<tree_node*> queue;
    std::map<string, bool> visited; 
    tree_node* inspected;
    tree_node* startNode = new tree_node(nullptr, tmp);  
    vector<GameState*> path;
    vector<GameState*> BFS;
    nodes.push_back(startNode);
    queue.push(startNode);
    visited.insert(std::pair<string, bool>(startNode->current->to_string(), true));
    while(!queue.empty()){
        inspected = queue.front();
        if (inspected->current->isReachable(objetive)){
            path = shortestPath(inspected);
            return path;
        }
        vector<GameState*> neighbours  = this->neighbours(inspected->current);
        for (unsigned int i =0; i < neighbours.size() ; i++){
            if (!visited.contains(neighbours[i]->to_string())){
                visited.insert(std::pair<string, bool>(neighbours[i]->to_string(), true));
                BFS.push_back(neighbours[i]);
                tree_node* newNode = new tree_node(inspected,neighbours[i]);
                nodes.push_back(newNode);
                queue.push(newNode);
            }else{
                GameState* tmp = neighbours[i];
                neighbours.erase(neighbours.begin()+i);
                delete tmp;
                i--;
            }
        }
        queue.pop();
    }
    return path;
}
    

vector<GameState*> Solver::shortestPath(tree_node* end){
    vector<GameState*> result;
    tree_node* actual =  end;
    while (actual->previous != nullptr){
        GameState * tmp = new GameState(*actual->current);
        result.push_back(tmp);
        actual = actual->previous;
    }
    std::reverse(result.begin(), result.end());
    return result;
}


vector<GameState*> Solver::neighbours(const GameState* _game){
    vector<GameState*> neighbours;
    for(unsigned int i = 0; i < _game->getListVehicule().size(); i++){
        for(int j = 1 ; j < 6; j++){
            GameState* g1 = new GameState(*_game);
            GameState* g2 = new GameState(*_game);
            if(g1->playMove(g1->getListVehicule()[i], j)){
                neighbours.push_back(g1);
            }else{
                delete g1;
            }
            if(g2->playMove(g2->getListVehicule()[i], -j)){
                neighbours.push_back(g2);
            }else{
                delete g2;
            }
           
        }
            
    }
    return neighbours;
}


vector<GameState*> Solver::BFS(GameState* start, Coordinate objetive){
    if (start->getListVehicule().empty()){
        std::cout << "Pas de véhicule" << std::endl;
        return vector<GameState*>();
    }
    if(objetive.getX() == -1 && objetive.getY() == -1){
        objetive = start->getExit();
    }
    vector<tree_node*> nodes;
    vector<GameState*> BFS = BFS_aux(start, objetive, nodes);
    for(unsigned int i = 0; i < nodes.size(); i++){
        delete nodes[i];
    }
    nodes.clear();
    return BFS;
    
}

