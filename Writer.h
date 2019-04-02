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
	std::string getSquareBorderString();
	int speed;
public:
	Writer(Maze* m, int s);
	void write();
	void writeBin();
};

#endif