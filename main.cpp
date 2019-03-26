#include "Maze.h"

int main() {
	std::cout << "hay";
	Parser* p = new Parser("maze.png");
	Maze* maze = new Maze(p);
	//maze->build();
	//maze->debugging();
	//delete p;
	//p->process();
}
