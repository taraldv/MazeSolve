#include "Path.h"

Path::Path(int len, Node* from, Node* to):length(len),from(from),to(to){
}

Node* Path::getFromNode(){
	return from;
}

int Path::getLength(){
	return length;
}

Node* Path::getToNode(){
	return to;
}