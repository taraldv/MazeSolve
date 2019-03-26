#include "Node.h"

using namespace std;

Node::Node(Square* square):square(square){
}

void Node::addNabo(Node* node){
	naboVektor.push_back(node);
}

void Node::printNaboer(){
	for(size_t i=0;i<naboVektor.size();i++){
		naboVektor[i]->printSquare();
	}
}

void Node::printSquare(){
	square->print();
}

void Node::printCoords(){
	square->printCoords();
}

Square* Node::getSquare(){
	return square;
}

vector<Node*> Node::getNaboer(){
	return naboVektor;
}