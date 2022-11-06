/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

/* ADTs */
#include "adts/list.h"
#include "adts/orderedCollection.h"
#include "adts/queue.h"
#include "adts/stack.h"

/* Implementations of above ADTs */
#include "adts/stlList.h"
#include "linkedQueue.h"
#include "linkedStack.h"

#include "maze.h"

using namespace std;

// Constuctor method: initializes the private fields of Maze.
Maze::Maze(int width, int height) {
  this->width = width;
  this->height = height;
  this->positions =  new Position**[width];
  for(int i = 0; i < width; i++) {
      this->positions[i] = new Position*[height];
    for(int j = 0; j < height; j++) {
      this->positions[i][j] = new Position(i,j);
    }
  }
}

// Destrcutor method: to clean the memory used by a Maze.
Maze::~Maze() {
  for(int i = 0; i < this->width; i++) {
    for(int j = 0; j < this->height; j++) {
      delete this->positions[i][j];
    }
    delete[] this->positions[i];
    }
  delete[] this->positions;
}

// Returns the width of the maze.
int Maze::getWidth() {
  return this->width;
}

// Returns the height of the maze.
int Maze::getHeight() {
  return this->height;
}

// Checks if a position in the maze is wall.
bool Maze::isWall(int x, int y) {
  return this->positions[x][y]->isWall();
}

// Sets a position in the maze as a wall.
void Maze::setWall(int x, int y) {
  this->positions[x][y]->setWall();
}

// Returns a pointer to the new list of pointers to this position's neighbors.
List<Position*>* Maze::getNeighbors(Position* position) {
  List<Position*>* neighbors = new STLList<Position*>();

  int x = position->getX();
  int y = position->getY();

  if (x > 0) {
    neighbors->insertFirst(this->positions[x - 1][y]);
  }
  if (x < this->getWidth() - 1) {
    neighbors->insertFirst(this->positions[x + 1][y]);
  }
  if (y > 0) {
    neighbors->insertFirst(this->positions[x][y - 1]);
  }
  if (y < this->getHeight() - 1) {
    neighbors->insertFirst(this->positions[x][y + 1]);
  }
  return neighbors;
}

// Solves the Maze using a breadth-first search.
List<Position*>* Maze::solveBreadthFirst() {
  // creates a new orderedCollection that's a LinkedQueue.
  OrderedCollection<Position*>* bfs_queue = new LinkedQueue<Position*>();

  // calling the solve method.
  List<Position*>* mazePath = this -> solve(bfs_queue);

  delete bfs_queue; // cleaning memory.

  return mazePath;
}

// Solves the Maze using a depth-first search.
List<Position*>* Maze::solveDepthFirst() {
  // creates a new orderedCollection that's a LinkedStack.
  OrderedCollection<Position*>* dfs_stack = new LinkedStack<Position*>();

  // calling the solve method.
  List<Position*>* mazePath = this -> solve(dfs_stack);

  delete dfs_stack; // cleaning memory.
  
  return mazePath;
}

// Performs a search using given OrderedCollection for a solution path.
List<Position*>* Maze::solve(OrderedCollection<Position*>* exploration) {
  Position* start = this->positions[0][0];
  Position* end = this->positions[this->getWidth() - 1][this->getHeight() - 1];
  exploration->insert(start);
  start->setVisited();
  while (!exploration->isEmpty()) { //while we have valid poistions to explore!
    Position* current = exploration->remove();

    if (current == end) { // we have reached end of the maze.
      List<Position*>* mazePath = new STLList<Position*>();
      mazePath->insertFirst(current);
      while (current->getPrevious() != nullptr) {
        current = current->getPrevious();
        mazePath->insertFirst(current); //creating a maze path reversing search.
      }
      return mazePath;
    }

    List<Position*>* neighbors = this->getNeighbors(current);

    for (int i = 0; i < neighbors->getSize(); i++) {
      Position* neighbor = neighbors->get(i);
      if (!neighbor->isVisited() && !neighbor->isWall()) {
        neighbor->setVisited();
        neighbor->setPrevious(current);
        exploration->insert(neighbor);
      }
    }

    delete neighbors; // cleaning memory.
  }

  // returns nullptr if the maze is non-solvable i.e. no solution path exists.
  return nullptr;
} 
      


