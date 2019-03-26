#include "Path.h"

Path::Path(int len, Node* to, Node* from):length(len),from(from),to(to){
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