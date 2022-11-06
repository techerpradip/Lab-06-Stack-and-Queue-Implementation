/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <utility>

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

// Initiation point of the maze program.
int main(int argc, char** argv) {
  // Checks the validity of the command-line and functions as required!
  if (argc == 3) {
    string filename = argv[1];
    string search_method = argv[2];

    Maze* maze_data;
    
    /* 
      ** Loads the data into a maze with maze_data pointer. 
      ** throws runtime error for invalid filename.
      */
    try{
      maze_data = loadMap(filename);
    } catch (runtime_error e) {
      throw runtime_error("Invalid filename!");
    }

    List<Position*>* solution_path;

    if (search_method == "breadth"){
      solution_path = maze_data->solveBreadthFirst(); // executes BFS
    } else if (search_method == "depth"){
      solution_path = maze_data->solveDepthFirst(); // executes DFS
    } else {
      delete maze_data;
      throw runtime_error("Invalid search type!"); // throws runtim error
    }

    // calls the renderAnser() method to get a solved maze string
    string solved_maze = renderAnswer(maze_data, solution_path);
    cout << solved_maze << endl;

    /* 
      ** Calls the deconstructor for the maze_data & sulution_path, 
      ** to clear the memory usage.
      */
    delete maze_data;
    delete solution_path;
    
    return 0;

  } else {
    // runtime error incase of invalid # of arguments in command line!
    throw runtime_error("Invalid number of command-line arguments!");
  }
}
