#ifndef NODE_H
#define NODE_H

#include "Square.h"

class Node{
private:
	Square* square;
public:
	Node(Square* square);
};

#endif