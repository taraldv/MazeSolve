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
#include <limits>
#include <algorithm>

struct dStruct{
	Node* node;
	Node* throughNode;
	int length;
};

class Maze{
private:
	Square** squareArray;
	std::vector<Path*> paths;
	int numberOfSquares;
	int sideNumber;
	Node** nodeArray;
	void addNabo(Node* nodeOne, Node* nodeTwo, int len);
	static bool vectorSort(dStruct x, dStruct y);
	std::vector<dStruct> generateStructs(Node* start);
	Path* getPathBetweenNodes(Node* nodeOne, Node* nodeTwo);
	//algo
	void oppdaterGraf(std::vector<Path*> nyPathVector);
	bool dfs(Node* current, Node* target, std::vector<Node*>& visited);
	bool notVisited(Node* node, std::vector<Node*>& visited);
	void updateDStruct(Node* current,int currentPathLength, Node* nabo, std::vector<dStruct>&alias);
	void connectNodes();
public:
	Node* getStartNode();
	Node* getEndNode();
	Square** getSquareArray();
	int getSides();
	int getArraySize();
	Maze(Parser* parser);

	void debugging();
	void printNodeCount();
	void printPathCount();
	void printPaths();
	//void buildNodes();
	
	void printSquares();
	void printNodes();

	//algo
	bool dfs(Node* start, Node* target);
	bool bfs(Node* start, Node* target);
	void runDijkstra(Node* start, Node* end);
};

#endif