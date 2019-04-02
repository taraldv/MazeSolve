#include "Writer.h"

#include <iostream>

using namespace std;


int main() {
	Parser* p = new Parser("maze3.png");
	//p->parse();
	Maze* maze = new Maze(p);
	delete p;
	

	Writer* w = new Writer(maze);
	w->write();
	//w->writeBin();

	//maze->printNodeCount();

	//maze->printPathCount();

	//maze->printPaths();

	//Node* start = maze->getStartNode();
	/*start->printCoords();
	cout << endl;
	start->printSquare();*/

	//Node* end = maze->getEndNode();
	/*end->printCoords();
	cout << endl;
	end->printSquare();*/

	/*bool depthFirst = maze->dfs(start,end);
	bool breadthFirst = maze->bfs(start,end);

	cout << "dfs: " << depthFirst << " bfs: " << breadthFirst << endl;*/

	//maze->printPaths();

	//maze->printNodes();
	//maze->runDijkstra(start,end);



	//maze->printPaths();

	//maze->printNodes();
	//maze->debugging();
	//delete p;
	//p->process();
}
