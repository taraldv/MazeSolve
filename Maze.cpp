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

Node* Maze::getStartNode(){
	for(int i=0;i<sideNumber;i++){
		Node* tempNode = nodeArray[i];
		if(tempNode){
			Square* temp = nodeArray[i]->getSquare();
			if(!temp->hasWall(Direction::NORTH)){
				return tempNode;
			}
		}
	}
}

Node* Maze::getEndNode(){
	for(int i=numberOfSquares-sideNumber;i<numberOfSquares;i++){
		Node* tempNode = nodeArray[i];
		if(tempNode){
			Square* temp = nodeArray[i]->getSquare();
			if(!temp->hasWall(Direction::SOUTH)){
				return tempNode;
			}
		}
	}
}

void Maze::printNodes(){
	for(int i = 0;i<numberOfSquares;i++){
		Node* temp = nodeArray[i];
		if(temp){
			cout << temp->getCoords() << " -> ";
			vector<Node*> tempNaboer = temp->getNaboer();
			for(size_t j=0;j<tempNaboer.size();j++){
				cout << tempNaboer[j]->getCoords() << " ";
			}
			cout << endl;
		}
	}
}

void Maze::printSquares(){
	for(int i=0;i<10;i++){
		Node* temp = nodeArray[i];
		if(temp){
			temp->printCoords();
			temp->printSquare();
		}
	}
}

void Maze::printNodeCount(){
	int count = 0;
	for(int i=0;i<numberOfSquares;i++){
		if(nodeArray[i]) count++;
	}
	cout << "nodeCount: " << count << endl;
}

void Maze::printPaths(){
	for(size_t i=0;i<paths.size();i++){
		Path* p = paths[i];
		Node* from = p->getFromNode();
		Node* to = p->getToNode();
		to->printCoords();
		cout << " <-- " << p->getLength() << " --> ";
		from->printCoords();
		cout << endl;
	}
}

void Maze::printPathCount(){
	int count = 0;
	int length = 0;
	for(size_t i=0;i<paths.size();i++){
		if(paths[i]->getLength()>1){
			length += paths[i]->getLength();
			count++;
		}
	}
	cout << "pathAbove1Count: " << count << " pathAbove1LengthSum: " << length << endl;
}

void Maze::connectNodes(){
	nodeArray = new Node*[numberOfSquares];
	for(int row=0;row<sideNumber;row++){
		bool firstRow = row == 0;
		bool lastRow = row == (sideNumber-1);
		for(int col=0;col<sideNumber;col++){
			int index = row*sideNumber+col;
			Square* tempSquare = squareArray[index];
			int tempSquareRow = tempSquare->getRow();
			int tempSquareCol = tempSquare->getCol();


			//hvis currentSquare er node
			if(tempSquare->isNode(firstRow,lastRow)){
				Node* tempNode = new Node(tempSquare);
				nodeArray[index] = tempNode;

				//hvis Square ikke har wall til venstre og col er større enn 0, finn første venstre nabo
				if(!tempSquare->hasWall(Direction::WEST) && col > 0){
					
					int westLength = 1;
					for(int x = col-1; x >= 0;x--){
						int leftSearchIndex = row*sideNumber+x;
						Square* tempLeftSquare = squareArray[leftSearchIndex];
						bool isTempLeftSquareInFirstRow = tempLeftSquare->getRow() == 0;
						bool isTempLeftSquareInLastRow = tempLeftSquare->getRow() == (sideNumber-1);
						if(tempLeftSquare->isNode(isTempLeftSquareInFirstRow,isTempLeftSquareInLastRow)){
							Node* tempLeftNode = nodeArray[leftSearchIndex];
							addNabo(tempLeftNode,tempNode,westLength);
							break;
						}
						westLength++;
					}
				}

				//leter nordover til første nabo
				if(!tempSquare->hasWall(Direction::NORTH) && row > 0){
					
					int northLength = 1;
					for(int y=row-1;y >= 0;y--){

						int northSearchIndex = y*sideNumber+col;
						Square* tempNorthSquare = squareArray[northSearchIndex];

						bool isTempNorthSquareInFirstRow = tempNorthSquare->getRow() == 0;
						bool isTempNorthSquareInLastRow = tempNorthSquare->getRow() == (sideNumber-1);
						if(tempNorthSquare->isNode(isTempNorthSquareInFirstRow,isTempNorthSquareInLastRow)){
							Node* tempNorthNode = nodeArray[northSearchIndex];
							addNabo(tempNorthNode,tempNode,northLength);

							break;
						}

						northLength++;
					}
				}

			}
		}
	}
}

void Maze::debugging(){
	for(int i=numberOfSquares-sideNumber;i<numberOfSquares;i++){
		Node* temp = nodeArray[i];
		if(temp){
			temp->printCoords();
			temp->printSquare();
		}
	}
}

void Maze::runDijkstra(Node* start){

}

bool Maze::dfs(Node * start, Node * target) {
	vector<Node*> visited;
	return dfs(start, target, visited);
}

bool Maze::dfs(Node * current, Node * target, std::vector<Node*>& visited) {
	if (current == target) {
		return true;
	}
	visited.push_back(current);
	for (size_t i = 0; i < current->getNaboer().size(); i++) {
		Node* tempNabo = current->getNaboer().at(i);
		if (notVisited(tempNabo,visited)) {
			if (dfs(tempNabo, target, visited)) {
				return true;
			}
		}
	}
	return false;
}

bool Maze::bfs(Node* start, Node* target) {
	vector<Node*> visited;
	queue<Node*> toVisit;
	toVisit.push(start);
	while (!toVisit.empty()) {
		Node* current = toVisit.front();
		current->printCoords();
		cout << endl;
		toVisit.pop();
		if (notVisited(current, visited)) {
			if (current == target) {
				return true;
			}
			vector<Node*> currentNaboer = current->getNaboer();
			for (size_t i = 0; i < currentNaboer.size(); i++) {
				if (notVisited(currentNaboer.at(i), visited)) {
					toVisit.push(currentNaboer.at(i));
				}
			}
			visited.push_back(current);
		}
	}
	return false;
}

bool Maze::notVisited(Node * node, std::vector<Node*>& visited) {
	for (size_t i = 0; i < visited.size(); i++) {
		if (visited.at(i) == node) {
			return false;
		}
	}
	return true;
}