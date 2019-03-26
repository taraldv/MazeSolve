#ifndef MAZE_H
#define MAZE_H

#include "Parser.h"
#include "Square.h"
#include "Node.h"
#include <iostream>

class Maze{
private:
	Square** squareArray;
	int numberOfSquares;
	//Node** nodeArray = new Node*[numberOfSquares];
public:
	Maze(Parser* parser);
	void debugging();
	//void build();
};

#endif