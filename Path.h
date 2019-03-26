#ifndef PATH_H
#define PATH_H

#include "Square.h"
#include "Node.h"

class Path{
private:
	int length;
	Node* to;
	Node* from;
public:
	Path(int length, Node* to, Node* from);
	Node* getFromNode();
	Node* getToNode();
	int getLength();
};

#endif