#include "Writer.h"

#include <iostream>

using namespace std;


int main(int argc, char** argv) {

	char* file;
	char* speed;
	for(int i=0;i<argc;i++){
		string temp = (string)argv[i];
		if(temp.compare("-f")==0){
			//cout << temp << endl;
			file = argv[i+1];
		}
		if(temp.compare("-s")==0){
			//cout << temp << endl;
			speed = argv[i+1];
		}
	}


	if((file == nullptr) && (speed == nullptr)){
		cout << "noe gikk galt med input, fant ikke -s og -f" << endl;
		return 1;
	}

	Parser* p = new Parser(file);
	Maze* maze = new Maze(p);
	delete p;
	string s = (string)speed;
	Writer* w = new Writer(maze,stoi(s));
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
