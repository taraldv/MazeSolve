#ifndef NODE_H
#define NODE_H

#include "Square.h"
#include <vector>
#include <iostream>

class Node{
private:
	Square* square;
	std::vector<Node*> naboVektor;
public:
	Node(Square* square);
	std::vector<Node*> getNaboer();
	void addNabo(Node* node);
	void printNaboer();
	void printSquare();
	void printCoords();
	int getRow();
	int getCol();
	Square* getSquare();
	std::string getCoords();
};

#endif