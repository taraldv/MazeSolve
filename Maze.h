#ifndef MAZE_H
#define MAZE_H

#include "Parser.h"
#include "Square.h"
#include "Node.h"
#include "Path.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

class Maze{
private:
	Square** squareArray;
	std::vector<Path*> paths;
	int numberOfSquares;
	int sideNumber;
	Node** nodeArray;
	void addNabo(Node* nodeOne, Node* nodeTwo, int len);

	//algo
	bool dfs(Node* current, Node* target, std::vector<Node*>& visited);
	bool notVisited(Node* node, std::vector<Node*>& visited);
public:
	Node* getStartNode();
	Node* getEndNode();
	Maze(Parser* parser);
	void debugging();
	//void buildNodes();
	void connectNodes();
	void printNodes();

	//algo
	bool dfs(Node* start, Node* target);
	bool bfs(Node* start, Node* target);
};

#endif