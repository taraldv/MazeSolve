#ifndef WRITER_H
#define WRITER_H

#include "Maze.h"
#include <iostream>
#include <fstream>

class Writer{
private:
	Maze* maze;
public:
	Writer(Maze* m);
	void write();
	void writeBin();
};

#endif