#include "Square.h"

using namespace std;

Square::Square(int** arr):arr(arr){
//begynner med venstre og går klokka
	//Color** test = new Color*;
	int* westWall = new int[size];
	int* northWall = new int[size];
	int* eastWall= new int[size];
	int* southWall= new int[size];
	for(int i=0;i<size*size;i++){
		if(i%size==0){
			if(getColor(arr[i])==Color::BLACK){
				westWall[i/16] = Color::BLACK;
			} else {
				westWall[i/16] = Color::WHITE;
			}
			//cout << "index: " << i << " venstre kant RGB: " << arr[i][0]<< " " << arr[i][1] << " " << arr[i][2] << " color: " << getColor(arr[i]) << endl;
		}
		if(i<size){
			if(getColor(arr[i])==Color::BLACK){
				northWall[i] = Color::BLACK;
			} else {
				northWall[i] = Color::WHITE;
			}
			//cout << "index: " << i << " øvre kant RGB: " << arr[i][0]<< " " << arr[i][1] << " " << arr[i][2] << " color: " << getColor(arr[i]) << endl;
		}
		if (i%size==15){
			int eastIndex = i/size;
			//cout << "i "<< i << " eastIndex " << eastIndex << endl;
			if(getColor(arr[i])==Color::BLACK){
				eastWall[eastIndex] = Color::BLACK;
			} else {
				eastWall[eastIndex] = Color::WHITE;
			}
			//cout << "index: " << i << " høyre kant RGB: " << arr[i][0]<< " " << arr[i][1] << " " << arr[i][2] << " color: " << getColor(arr[i]) << endl;
		}
		if(i>=size*size-size){
			if(getColor(arr[i])==Color::BLACK){
				southWall[i-240] = Color::BLACK;
			} else {
				southWall[i-240] = Color::WHITE;
			}
			//cout << "index: " << i << " nedre kant RGB: " << arr[i][0]<< " " << arr[i][1] << " " << arr[i][2] << " color: " << getColor(arr[i]) << endl;
		}
	}
	walls[0] = westWall;
	walls[1] = northWall;
	walls[2] = eastWall;
	walls[3] = southWall;
}

Color Square::getColor(int* arr){
	int r = arr[0];
	int g = arr[1];
	int b = arr[2];
	if(r == 0 && g == 0 && b == 0){
		return Color::BLACK;
	} else if(r == 255 && g == 255 && b == 255){
		return Color::WHITE;
	} else {
		cout << "farge problemer" << "RGB: " << arr[0] << " " << arr[1] << " " << arr[2] << endl;
	}
}

bool Square::hasWall(Direction direction){
	int count = 0;
	for(int i=0;i<size;i++){
		count += walls[direction][i];
	}
	return count > size/2;
}

bool Square::isNode(){
	bool west = hasWall(Direction::WEST);
	bool north = hasWall(Direction::NORTH);
	bool east = hasWall(Direction::EAST);
	bool south = hasWall(Direction::SOUTH);
	//horisonal path betyr vegger kun north & south
	bool horisontalPath = north && south && !west && !east;
	//verticalPath er motsatt
	bool verticalPath = !north && !south && west && east;

	//hvis en av de er true, er square en path
	return !horisontalPath || !verticalPath;
}

int Square::getOpeningCount(){
	int count = 0;
	for(int i=0;i<4;i++){
		if(!hasWall((Direction)i)){
			count++;
		}
	}
	return count;
}

//debugging
void Square::print(){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			int* temp = arr[i*size+j];
			cout << temp[0]<< " " << temp[1] << " " << temp[2] << " , ";
		}
		cout << endl;
	}
}