#include "Writer.h"

using namespace std;

Writer::Writer(Maze* m):maze(m){

}

string Writer::getBorderColorString(){
	string output = "";
	output += "let styles = [";
	int lenght = maze->getSquareArrayLength();
	Square** arr = maze->getSquareArray();
	for(int i=0;i<lenght;i++){
		Square* square = arr[i];
		string westColor = "white";
		string northColor = "white";
		string eastColor = "white";
		string southColor = "white";
		if(square->hasWall(Direction::WEST)){
			westColor = "black";
		}
		if(square->hasWall(Direction::NORTH)){
			northColor = "black";
		}
		if(square->hasWall(Direction::EAST)){
			eastColor = "black";
		}
		if(square->hasWall(Direction::SOUTH)){
			southColor = "black";
		}
		if(i!=0){
			output += ",";
		}
		output += "\"border-left: 1px solid "+westColor+
		";border-top: 1px solid "+northColor+
		";border-right: 1px solid "+eastColor+
		";border-bottom: 1px solid "+southColor+";\"";
	}
	output += "];";
	return output;
}

string Writer::getAnimationString(){
	string output = "let path = [";
	Node* start = maze->getStartNode();
	Node* end = maze->getEndNode();
	maze->runDijkstra(start,end);
	vector<Node*> optimal = maze->getOptimalPathNodes();
	for(int i=optimal.size()-1;i>=0;i--){
		Node* tempNode = optimal[i];
		int row = tempNode->getRow();
		int col = tempNode->getCol();
		if(i!=optimal.size()-1){
			output += ",";
		}
		output += "["+to_string(row)+","+to_string(col)+"]";
	}
	output += "];";
	return output;
}

void Writer::write(){
	int file[778] = {60,33,68,79,67,84,89,80,69,32,104,116,109,108,62,13,10,60,104,116,109,108,62,13,10,60,104,101,97,100,62,13,10,9,60,109,101,116,97,32,99,104,97,114,115,101,116,61,34,85,84,70,45,56,34,62,13,10,9,60,116,105,116,108,101,62,77,97,122,101,32,83,111,108,118,101,114,60,47,116,105,116,108,101,62,13,10,9,60,115,116,121,108,101,32,116,121,112,101,61,34,116,101,120,116,47,99,115,115,34,62,13,10,9,42,123,13,10,9,9,112,97,100,100,105,110,103,58,32,48,59,13,10,9,9,109,97,114,103,105,110,58,32,48,59,13,10,9,125,13,10,9,98,111,100,121,123,13,10,9,9,119,105,100,116,104,58,32,49,48,48,37,59,13,10,9,9,109,97,114,103,105,110,45,116,111,112,58,32,50,48,112,120,59,13,10,9,125,13,10,9,116,97,98,108,101,123,13,10,9,9,109,97,114,103,105,110,58,32,97,117,116,111,59,13,10,9,9,98,111,114,100,101,114,45,99,111,108,108,97,112,115,101,58,99,111,108,108,97,112,115,101,59,13,10,9,125,13,10,9,116,100,123,13,10,9,9,119,105,100,116,104,58,32,56,112,120,59,13,10,9,9,104,101,105,103,104,116,58,32,56,112,120,59,13,10,9,125,13,10,60,47,115,116,121,108,101,62,13,10,60,47,104,101,97,100,62,13,10,60,98,111,100,121,62,13,10,9,60,115,99,114,105,112,116,32,116,121,112,101,61,34,116,101,120,116,47,106,97,118,97,115,99,114,105,112,116,34,62,13,10,13,10,9,9,13,10,9,9,108,101,116,32,116,97,98,108,101,32,61,32,100,111,99,117,109,101,110,116,46,99,114,101,97,116,101,69,108,101,109,101,110,116,40,34,116,97,98,108,101,34,41,59,13,10,9,9,102,111,114,40,108,101,116,32,105,61,48,59,105,60,104,101,105,103,104,116,59,105,43,43,41,123,13,10,9,9,9,108,101,116,32,116,97,98,108,101,82,111,119,32,61,32,100,111,99,117,109,101,110,116,46,99,114,101,97,116,101,69,108,101,109,101,110,116,40,34,116,114,34,41,59,13,10,9,9,9,102,111,114,40,108,101,116,32,106,61,48,59,106,60,119,105,100,116,104,59,106,43,43,41,123,13,10,9,9,9,9,108,101,116,32,116,97,98,108,101,68,32,61,32,100,111,99,117,109,101,110,116,46,99,114,101,97,116,101,69,108,101,109,101,110,116,40,34,116,100,34,41,59,13,10,9,9,9,9,108,101,116,32,105,110,100,101,120,32,61,32,105,42,119,105,100,116,104,43,106,59,13,10,9,9,9,9,116,97,98,108,101,68,46,115,116,121,108,101,32,61,32,115,116,121,108,101,115,91,105,110,100,101,120,93,59,13,10,9,9,9,9,116,97,98,108,101,82,111,119,46,97,112,112,101,110,100,67,104,105,108,100,40,116,97,98,108,101,68,41,59,13,10,9,9,9,125,13,10,9,9,9,116,97,98,108,101,46,97,112,112,101,110,100,67,104,105,108,100,40,116,97,98,108,101,82,111,119,41,13,10,9,9,125,13,10,9,9,100,111,99,117,109,101,110,116,46,98,111,100,121,46,97,112,112,101,110,100,67,104,105,108,100,40,116,97,98,108,101,41,59,13,10,9,60,47,115,99,114,105,112,116,62,13,10,60,47,98,111,100,121,62,13,10,60,47,104,116,109,108,62};
	int fSize = 778;
	ofstream myfile;
	myfile.open ("example.html");
	
	int width = maze->getWidth();
	int height = maze->getHeight();
	
	for(int x=0;x<fSize;x++){
		
		if(x==361){
			myfile << "let height = " << to_string(height) << ";" << endl;
			myfile << "let width = " << to_string(width) << ";" << endl;
			myfile << getAnimationString() << endl;
			myfile << getBorderColorString() << endl;
		} else {
			myfile << (char)file[x];
		}
		
	}
	
	myfile.close();
}

void Writer::writeBin(){
	std::ifstream is ("maze.html", std::ifstream::binary);
	is.seekg (0, is.end);
	int length = is.tellg();
	is.seekg (0, is.beg);

	char * buffer = new char [length];
	is.read (buffer,length);

	ofstream myfile;
	myfile.open ("htmlBytes.txt");
	myfile << "int file["+to_string(length)+"] = {";
	for(int i=0;i<length;i++){
		if(i!=0){
			myfile<< ",";
		}
		myfile <<to_string((int)buffer[i]);
	}
	myfile << "};";
	myfile.close();
}