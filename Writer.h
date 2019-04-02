#ifndef WRITER_H
#define WRITER_H

#include "Maze.h"
#include <iostream>
#include <fstream>

class Writer{
private:
	Maze* maze;
	std::string getBorderColorString();
	std::string getAnimationString();
public:
	Writer(Maze* m);
	void write();
	void writeBin();
};

#endif