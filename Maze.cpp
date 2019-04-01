#include "Maze.h"

using namespace std;

Maze::Maze(Parser* parser){
	squareArray = parser->parse();
	numberOfSquares = parser->getSquareNumber();
	sideNumber = sqrt(numberOfSquares);
	connectNodes();
}

Square** Maze::getSquareArray(){
	return squareArray;
}
int Maze::getArraySize(){
	return numberOfSquares;
}

int Maze::getSides(){
	return sideNumber;
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
	cout << "skal ikke skje" << endl;
	return nullptr;
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
	cout << "skal ikke skje" << endl;
	return nullptr;
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
			length += paths[i]->getLength()-1;
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
			//int tempSquareRow = tempSquare->getRow();
			//int tempSquareCol = tempSquare->getCol();


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


vector<dStruct> Maze::generateStructs(Node* start){
	vector<dStruct> output;
	for(int i=0;i<numberOfSquares;i++){
		Node* temp = nodeArray[i];

		/* setter avstand til alle nodes lik max, lagrer det i en struct arr */
		if(temp){
			dStruct tempStruct;

			// lengden til start settes lik 0
			if(temp == start){
				tempStruct.length = 0;
			} else {
				tempStruct.length = numeric_limits<int>::max();
			}
			tempStruct.node = temp;
			tempStruct.throughNode = temp;
			output.push_back(tempStruct);
		}
	}
	return output;
}

bool Maze::vectorSort(dStruct x, dStruct y){
	return x.length>y.length;
}

void Maze::oppdaterGraf(vector<Path*> nyPathVector){
	//går igjennom alle Pather i grafen
	for (size_t j = 0;j<paths.size();j++){
		Path* path = paths[j];
		bool isOptimalPath = false;

		for(size_t i=0;i<nyPathVector.size();i++){
			Path* tempPath = nyPathVector[i];
			if(path==tempPath){
				isOptimalPath = true;
				break;
			}
		}

		//hvis current Path ikke finnes i nyPathVector, skal den slettes
		if(!isOptimalPath){
			delete path;
		}
	}
	paths = nyPathVector;
}

Path* Maze::getPathBetweenNodes(Node* n, Node* m){
	for(size_t i=0;i<paths.size();i++){
		Path* p = paths[i];
		Node* from = p->getFromNode();
		Node* to = p->getToNode();
		bool fromMatch = (from == n || from == m);
		bool toMatch = (to == n || to == m);
		if(fromMatch && toMatch) return p;
	}
	cout << "path not found, burde ikke skje" << endl;
	return NULL;
}

void printStructs(vector<dStruct>&alias){
	for(size_t i=0;i<alias.size();i++){
		int length = alias[i].length;
		Node* node = alias[i].node;
		Node* throughNode = alias[i].throughNode;
		cout << node->getCoords() << " len:" << length << " through " << throughNode->getCoords() << endl;
	}
}

void Maze::updateDStruct(Node* current,int currentPathLength, Node* nabo, vector<dStruct>&alias){
	Path* p = getPathBetweenNodes(current,nabo);
	/*current->printCoords();
	cout << " <-- " << p->getLength() << " --> ";
	nabo->printCoords();
	cout << endl;*/

	int length = p->getLength()+currentPathLength;
	for(size_t i=0;i<alias.size();i++){
		dStruct tempStruct = alias[i];
		Node* structNode = tempStruct.node;
		if(nabo==structNode){
			int currentDistance = tempStruct.length;

			if(length<currentDistance){
				//cout << "oppdaterer struct" << endl;
				alias[i].length = length;
				alias[i].throughNode = current;
			}
		}
	}
}

void printPath(Node* start, Node* end,vector<dStruct> sVect){

	Node* through = end;
	Node* current = nullptr;

	while(current != start){

		for(size_t i=0;i<sVect.size();i++){
			dStruct temp = sVect[i];
			if(temp.node==through){
				through = temp.throughNode;
				current = temp.node;
				cout << current->getCoords() << endl;
			}
		}
	}
}

void Maze::runDijkstra(Node* start, Node* end){
	vector<dStruct> structVector = generateStructs(start);
	vector<dStruct> finished;

	sort(structVector.begin(),structVector.end(),vectorSort);

	//for hver node, oppdater avstand hvis kortere fra current
	while(!structVector.empty()){

		dStruct currentStruct = structVector.back();
		int currentPathLength = currentStruct.length;
		structVector.pop_back();
		//cout << currentStruct.length << endl;
		Node* currentNode = currentStruct.node;
		vector<Node*> currentNodeNaboer = currentNode->getNaboer();
		for(size_t i=0;i<currentNodeNaboer.size();i++){
			Node* nabo = currentNodeNaboer[i];
			updateDStruct(currentNode,currentPathLength,nabo,structVector);
			sort(structVector.begin(),structVector.end(),vectorSort);
		}
		finished.push_back(currentStruct);
		/*for(int j=0;j<numberOfSquares;j++){
			Node* tempNode = nodeArray[j];
			dijkstraNodeDistance tempStruct = structArr[j];
		}*/
		
	}

	//sorterer for å få struct som inneholder start node bakerst
	sort(finished.begin(),finished.end(),vectorSort);

	//begynner med nest sist struct
	//siden det ikke finnes en Path mellom start node og seg selv
	vector<Path*> nyPathVector;
	for(int y = finished.size()-2;y>=0;y--){
		Path* optimalPathForStruct = getPathBetweenNodes(finished[y].node,finished[y].throughNode);
		nyPathVector.push_back(optimalPathForStruct);
	}

	//printStructs(finished);
	printPath(start,end,finished);
	//oppdaterGraf(nyPathVector);
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