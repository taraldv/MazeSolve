#include "Maze.h"
#include <iostream>

using namespace std;


int main() {
	Parser* p = new Parser("maze.png");
	Maze* maze = new Maze(p);
	//maze->debugging();
	maze->connectNodes();

	//maze->printNodeCount();

	//maze->printPathCount();

	//maze->printPaths();

	/*Node* start = maze->getStartNode();
	start->printCoords();
	cout << endl;
	start->printSquare();

	Node* end = maze->getEndNode();
	end->printCoords();
	cout << endl;
	end->printSquare();*/

	//bool depthFirst = maze->dfs(start,end);
	//bool breadthFirst = maze->bfs(start,end);

	//cout << "dfs: " << depthFirst << " bfs: " << breadthFirst << endl;

	maze->printNodes();
	//maze->debugging();
	//delete p;
	//p->process();
}
