#ifndef PATH_H
#define PATH_H

#include "Square.h"

class Path{
private:
	int length;
	Square** arr;
public:
	Path(int length, Square** arr);
};

#endif