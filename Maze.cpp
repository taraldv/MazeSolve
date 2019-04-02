#include "Maze.h"

using namespace std;

Maze::Maze(Parser* parser){
	squareArray = parser->parse();
	squareArrayLength = parser->getSquareNumber();
	//-2 for border, og hver square er 16 px
	height = (parser->getHeight()-2)/16;
	width = (parser->getWidth()-2)/16;
	connectNodes();
}

Square** Maze::getSquareArray(){
	return squareArray;
}

vector<Node*> Maze::getOptimalPathNodes(){
	return optimalPathNodes;
}

int Maze::getSquareArrayLength(){
	return squareArrayLength;
}

int Maze::getHeight(){
	return height;
}

int Maze::getWidth(){
	return width;
}

void Maze::addNabo(Node* one, Node* two, int len){
	Path* path = new Path(len, one, two);
	paths.push_back(path);
	one->addNabo(two);
	two->addNabo(one);
}

Node* Maze::getStartNode(){
	for(int i=0;i<width;i++){
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
	for(int i=squareArrayLength-width;i<squareArrayLength;i++){
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
	for(int i = 0;i<squareArrayLength;i++){
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
	for(int i=0;i<squareArrayLength;i++){
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
	nodeArray = new Node*[squareArrayLength];
	//cout << height << ", " << width << ", " << squareArrayLength << endl;
	for(int row=0;row<height;row++){
		bool firstRow = row == 0;
		bool lastRow = row == (height-1);
		for(int col=0;col<width;col++){
			int index = row*width+col;
			//cout << "index: " << index << endl;
			//cout << " row: "<< row << " col: "<< col << endl;
			Square* tempSquare = squareArray[index];
			/*if(!tempSquare){
				cout << "square finnes ikke,skal ikke skje" << endl;
			}*/

			//hvis currentSquare er node
			if(tempSquare->isNode(firstRow,lastRow)){
				//cout << "er node" << endl;
				Node* tempNode = new Node(tempSquare);
				//tempNode->printCoords();
				//cout << endl;
				//tempNode->printSquare();
				nodeArray[index] = tempNode;

				//hvis Square ikke har wall til venstre og col er større enn 0, finn første venstre nabo
				if(!tempSquare->hasWall(Direction::WEST) && col > 0){
					//cout << "leter etter venstre nabo" << endl;
					int westLength = 1;
					for(int x = col-1; x >= 0;x--){
						int leftSearchIndex = row*width+x;
						Square* tempLeftSquare = squareArray[leftSearchIndex];
						bool isTempLeftSquareInFirstRow = tempLeftSquare->getRow() == 0;
						bool isTempLeftSquareInLastRow = tempLeftSquare->getRow() == (height-1);
						if(tempLeftSquare->isNode(isTempLeftSquareInFirstRow,isTempLeftSquareInLastRow)){
							//cout << "fant venstre nabo" << endl;
							Node* tempLeftNode = nodeArray[leftSearchIndex];
							addNabo(tempLeftNode,tempNode,westLength);
							break;
						}
						westLength++;
					}
				}

				//leter nordover til første nabo
				if(!tempSquare->hasWall(Direction::NORTH) && row > 0){
					//cout << "leter etter nabo nordover" << endl;
					int northLength = 1;
					for(int y=row-1;y >= 0;y--){

						int northSearchIndex = y*width+col;
						Square* tempNorthSquare = squareArray[northSearchIndex];

						bool isTempNorthSquareInFirstRow = tempNorthSquare->getRow() == 0;
						bool isTempNorthSquareInLastRow = tempNorthSquare->getRow() == (height-1);
						if(tempNorthSquare->isNode(isTempNorthSquareInFirstRow,isTempNorthSquareInLastRow)){
							Node* tempNorthNode = nodeArray[northSearchIndex];
							addNabo(tempNorthNode,tempNode,northLength);
							//cout << "addedNorthNabo: " << tempNorthNode->getCoords() << endl;
							break;
						}

						northLength++;
					}
				}

			}
		}
	}
}


vector<dStruct> Maze::generateStructs(Node* start){
	vector<dStruct> output;
	for(int i=0;i<squareArrayLength;i++){
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
	cout << "er disse naboer? " << n->getCoords() << " & " << m->getCoords() << endl; 
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

vector<Node*> printPath(Node* start, Node* end,vector<dStruct> sVect){

	Node* through = end;
	Node* current = nullptr;
	vector<Node*> output;
	while(current != start){

		for(size_t i=0;i<sVect.size();i++){
			dStruct temp = sVect[i];
			if(temp.node==through){
				through = temp.throughNode;
				current = temp.node;
				output.push_back(current);
				//cout << current->getCoords() << endl;
			}
		}
	}
	return output;
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
		if(currentPathLength == numeric_limits<int>::max()){
			currentNode->printCoords();
			cout << endl;
			cout << "currentPathLength er max, burde ikke skje?" << endl;
		}
		vector<Node*> currentNodeNaboer = currentNode->getNaboer();
		for(size_t i=0;i<currentNodeNaboer.size();i++){
			Node* nabo = currentNodeNaboer[i];
			updateDStruct(currentNode,currentPathLength,nabo,structVector);
			sort(structVector.begin(),structVector.end(),vectorSort);
		}
		finished.push_back(currentStruct);
		/*for(int j=0;j<squareArrayLength;j++){
			Node* tempNode = nodeArray[j];
			dijkstraNodeDistance tempStruct = structArr[j];
		}*/
		
	}

	optimalPathNodes =  printPath(start,end,finished);
	//sorterer for å få struct som inneholder start node bakerst
	

	//begynner med nest sist struct
	//siden det ikke finnes en Path mellom start node og seg selv
	/*sort(finished.begin(),finished.end(),vectorSort);
	vector<Path*> nyPathVector;
	for(int y = finished.size()-2;y>=0;y--){
		Path* optimalPathForStruct = getPathBetweenNodes(finished[y].node,finished[y].throughNode);
		nyPathVector.push_back(optimalPathForStruct);
	}*/

	//printStructs(finished);
	
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