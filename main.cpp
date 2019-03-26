#include "Maze.h"

int main() {
	Parser* p = new Parser("maze.png");
	Maze* maze = new Maze(p);
	//maze->buildNodes();
	maze->connectNodes();
	//maze->printNodes();
	//maze->debugging();
	//delete p;
	//p->process();
}
