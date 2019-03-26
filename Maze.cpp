#include "Maze.h"

using namespace std;

Maze::Maze(Parser* parser){
	squareArray = parser->parse();
	numberOfSquares = parser->getSquareNumber();
}

/*void Maze::build(){
	int count = 0;
	for(int i=0;i<numberOfSquares;i++){
		Square* tempSquare = squareArray[i];
		if(tempSquare->isNode()){
			count++;
			nodeArray[i] = new Node(tempSquare);
		}
	}
	cout << count << endl;
}*/

void Maze::debugging(){
	Square* first = squareArray[0];
	first->print();
	int openings = first->getOpeningCount();
	cout << openings << endl;
}