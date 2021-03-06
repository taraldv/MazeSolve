#ifndef PATH_H
#define PATH_H

#include "Square.h"
#include "Node.h"

class Path{
private:
	int length;
	Node* from;
	Node* to;
public:
	Path(int length,Node* from, Node* to);
	Node* getFromNode();
	Node* getToNode();
	int getLength();
};

#endif