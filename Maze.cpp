#include "Maze.h"

using namespace std;

Maze::Maze(Parser* parser){
	squareArray = parser->parse();
	numberOfSquares = parser->getSquareNumber();
	sideNumber = sqrt(numberOfSquares);
}

void Maze::addNabo(Node* one, Node* two, int len){
	Path* path = new Path(len, one, two);
	paths.push_back(path);
	one->addNabo(two);
	two->addNabo(one);
}

void Maze::buildNodes(){
	nodeArray = new Node*[numberOfSquares];
	int count = 0;
	for(int i=0;i<numberOfSquares;i++){
		Square* tempSquare = squareArray[i];
		if(tempSquare->isNode()){
			count++;
			nodeArray[i] = new Node(tempSquare);
		}
	}
	cout << count << endl;
}

void Maze::printNodes(){
	for(int i=0;i<10;i++){
		Node* temp = nodeArray[i];
		if(temp){
			temp->printCoords();
			temp->printSquare();
		}
	}
}

void Maze::connectNodes(){
	for(int row=0;row<sideNumber;row++){
		for(int col=0;col<sideNumber;col++){
			int index = row*sideNumber+col;
			Square* tempSquare = squareArray[index];

			//hvis currentSquare er node
			if(tempSquare->isNode()){
				Node* tempNode = nodeArray[index];

				//hvis Square ikke har wall til venstre og col er større enn 0, finn første venstre nabo
				if(!tempSquare->hasWall(Direction::WEST) && col > 0){
					
					int westLength = 1;
					for(int x = col-1; x >= 0;x--){
						int leftSearchIndex = row*sideNumber+x;
						Square* tempLeftSquare = squareArray[leftSearchIndex];
						if(tempLeftSquare->isNode()){
							Node* tempLeftNode = nodeArray[leftSearchIndex];
							addNabo(tempLeftNode,tempNode,westLength);
						}
						westLength++;
					}
				}

				//leter nordover til første nabo
				if(tempSquare->hasWall(Direction::NORTH) && row > 0){
					int northLength = 1;
					for(int y=row-1;y >= 0;y-=sideNumber){
						int northSearchIndex = y*sideNumber+col;
						Square* tempNorthSquare = squareArray[northSearchIndex];
						if(tempNorthSquare->isNode()){
							Node* tempNorthNode = nodeArray[northSearchIndex];
							addNabo(tempNorthNode,tempNode,northLength);
						}
						northLength++;
					}
				}

			}
		}
	}
}

void Maze::debugging(){
	Square* first = squareArray[0];
	first->print();
	int openings = first->getOpeningCount();
	cout << openings << endl;
}