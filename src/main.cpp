/**
 * @file main.cpp
 * @brief This file contains the resolution of the initial problem, generate maps, and solve them .
*/

#include <iostream>
#include <string>
#include "utilities.hpp"
#include "PuzzleGenerator.hpp"

void make_gif() {
    std::cout << "Making gif" << std::endl;
    int script = system("bash export/BFS_Initial_MAP/script_gif.sh");
    if (script == 0) {
        std::cout << "Script executed successfully." << std::endl;
    } else {
        std::cout << "Error executing script." << std::endl;
    }
}

void parse_command_line(int argc, char ** argv) {
    for (int i = 1; i < argc; i++) {
    if (string(argv[i]) ==  "--gif") {
        make_gif();
        i++;
    } else {
        cout << "ERROR: Unknown option: " << argv[i] << endl;
        exit (1);
    }
  }
}

int main(int argc, char ** argv) {
    srand(time(NULL));
    
    // Partie résulution du puzzle de base
    Solver * solver = new Solver();
    GameState game1 = GameState("map/puzzle.txt");
    std::vector<GameState*> BFS = solver->BFS(&game1);
    write_gamestate(BFS, "BFS_Initial_MAP", "Initial_MAP_Soluce");
    std::cout<<"Minimum de coup pour la resolution du puzzle initial : "<<BFS.size()<<std::endl;
    destroy_vec_gamestate(BFS);


    // Partie génération
    PuzzleGenerator pg;
    GameState game2 = pg.naiveGeneration();
    game2.exportMapSvg("export/naive_generation.svg");
    game2.writeMapFile("map/naive_generation.txt");


    GameState game3 = pg.dijkstraGeneration();
    game3.exportMapSvg("export/dijkstra_generation.svg");
    game3.writeMapFile("map/dijkstra_generation.txt");

    // resultion de nos maps
    BFS = solver->BFS(&game2);
    write_gamestate(BFS, "BFS_naive_MAP", "naive_MAP_Soluce");
    std::cout<<"Minimum de coup pour la génération naive : "<<BFS.size()<<std::endl;
    destroy_vec_gamestate(BFS);

    BFS = solver->BFS(&game3);
    write_gamestate(BFS, "BFS_dijkstra_MAP", "dijkstra_MAP_Soluce");
    std::cout<<"Minimum de coup pour la génération dijkstra : "<<BFS.size()<<std::endl;
    destroy_vec_gamestate(BFS);



    parse_command_line(argc, argv);
    return 0;
}
