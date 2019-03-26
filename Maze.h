#ifndef MAZE_H
#define MAZE_H

#include "Parser.h"
#include "Square.h"
#include "Node.h"
#include "Path.h"
#include <iostream>
#include <cmath>
#include <vector>

class Maze{
private:
	Square** squareArray;
	std::vector<Path*> paths;
	int numberOfSquares;
	int sideNumber;
	Node** nodeArray;
	void addNabo(Node* nodeOne, Node* nodeTwo, int len);
public:
	Maze(Parser* parser);
	void debugging();
	void buildNodes();
	void connectNodes();
	void printNodes();
};

#endif