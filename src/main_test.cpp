/**
 * @file main_test.cpp
 * @brief This file contains the main function for the tests.
*/

#include <iostream>
#include <string>
#include <cassert>

#include "utilities.hpp"
#include "PuzzleGenerator.hpp"
//===== Running tests =====

//comment to activate / deactivate tests


#define OPERATOR_INF_TEST
#define OPERATOR_EQUAL_TEST
#define NEIGHBOURS_TEST
#define GAME_TO_STRING_TEST
#define VICTORY_TEST 
#define BFS_TEST
#define MAP_GENERATOR_TEST_NAIVE
#define MAP_GENERATOR_TEST_DIJKSTRA

//===== Testing =====

int main() {

    Solver* solv =  new Solver();
    srand(time(NULL));

    GameState game1 = GameState("map/map_1_test.txt");
    GameState game2 = GameState("map/map_2_test.txt");
    GameState game3 = game1;


    #ifdef OPERATOR_INF_TEST
  {
    assert(game1 < game2);
    std::cout<<"Assert game1 < game2 passed"<<std::endl;
  }
    #endif
    
    #ifdef OPERATOR_EQUAL_TEST
    {
        assert(game1 == game3);
        std::cout<<"Assert game1 == game3 passed"<<std::endl;
    }
    #endif

    #ifdef NEIGHBOURS_TEST
    {
        std::vector<GameState*> neighbours_g1 = solv->neighbours(&game1);
        assert(neighbours_g1.size() == 9);
        std::cout<<"Assert neighbours_g1.size() == 9 passed"<<std::endl;
        destroy_vec_gamestate(neighbours_g1);
    }
    #endif

    #ifdef GAME_TO_STRING_TEST
    {
        std::cout<<"game3.to_string() "<<std::endl;
        std::cout<<"======================================="<<std::endl;
        std::cout << game3.to_string() <<std::endl;
        std::cout<<"======================================="<<std::endl;
    }
    #endif

    #ifdef VICTORY_TEST
    {
        GameState game4 = GameState("map/map_win_test.txt");
        std::vector<GameState*> v = solv->neighbours(&game4);
        for(unsigned int i = 3; i < v.size(); i++){
            v[i]->victory();
            assert(v[i]->victory());
        }
        std::cout<<"Assert victory() passed"<<std::endl;
        destroy_vec_gamestate(v);
    }
    #endif

    #ifdef BFS_TEST
    {
        std::vector<GameState*> BFS = solv->BFS(&game1);
        write_gamestate(BFS, "BFS_Initial_MAP", "Initial_MAP_Soluce");
        assert(BFS.size() == 14);
        std::cout<<"Assert BFS.size() == 14 passed"<<std::endl;
        destroy_vec_gamestate(BFS);
    }
    #endif

    #ifdef MAP_GENERATOR_TEST_NAIVE
    {
        PuzzleGenerator pg;
        GameState game5 = pg.naiveGeneration();
        std::vector<GameState*> BFS = solv->BFS(&game5);
        assert(BFS.size() != 0);
        std::cout<<"Assert BFS.size() != 0 passed TEST_NAIVE"<<std::endl;
        destroy_vec_gamestate(BFS);
    }
    #endif

    #ifdef MAP_GENERATOR_TEST_DIJKSTRA
    {
        PuzzleGenerator pg;
        GameState game6 = pg.dijkstraGeneration();
        std::vector<GameState*> BFS = solv->BFS(&game6);
        assert(BFS.size() != 0);
        std::cout<<"Assert BFS.size() != 0 passed TEST_DIJKSTRA"<<std::endl;
        destroy_vec_gamestate(BFS);
    }
    #endif




    delete solv;
    return 0;
}