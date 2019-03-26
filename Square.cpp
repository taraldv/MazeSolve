#include "Square.h"

using namespace std;

void Square::printCoords(){
	cout << "row: " << row << " col: " << col << endl;
}

void Square::setWalls(){
	walls = new bool[4];
	int westCount = 0;
	int northCount = 0;
	int eastCount = 0;
	int southCount = 0;
	for(int i=0;i<size*size;i++){
		if(i%size==0 && getColor(arr[i])==Color::BLACK){
			westCount++;
			//cout << "index: " << i << " venstre kant RGB: " << arr[i][0]<< " " << arr[i][1] << " " << arr[i][2] << " color: " << getColor(arr[i]) << endl;
		}
		if(i<size && getColor(arr[i])==Color::BLACK){
			northCount++;
			//cout << "index: " << i << " øvre kant RGB: " << arr[i][0]<< " " << arr[i][1] << " " << arr[i][2] << " color: " << getColor(arr[i]) << endl;
		}
		if (i%size==15 && getColor(arr[i])==Color::BLACK){
			eastCount++;
			//cout << "index: " << i << " høyre kant RGB: " << arr[i][0]<< " " << arr[i][1] << " " << arr[i][2] << " color: " << getColor(arr[i]) << endl;
		}
		if(i>=size*size-size && getColor(arr[i])==Color::BLACK){
			southCount++;
			//cout << "index: " << i << " nedre kant RGB: " << arr[i][0]<< " " << arr[i][1] << " " << arr[i][2] << " color: " << getColor(arr[i]) << endl;
		}
	}
	//hvis svart telling er større enn size/2, finnes veggen
	walls[0] = westCount>size/2;
	walls[1] = northCount>size/2;
	walls[2] = eastCount>size/2;
	walls[3] = southCount>size/2;

}

Square::Square(int** arr, int col, int row):arr(arr),row(row),col(col){
	setWalls();
}

void Square::debugWalls(){
	setWalls();
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
	return  walls[(int)direction];
}

bool Square::isNode(bool firstRow, bool lastRow){
	bool west = hasWall(Direction::WEST);
	bool north = hasWall(Direction::NORTH);
	bool east = hasWall(Direction::EAST);
	bool south = hasWall(Direction::SOUTH);
	//horisonal path betyr vegger kun north & south
	bool horisontalPath = north && south && !west && !east;
	//verticalPath er motsatt
	bool verticalPath = !north && !south && west && east;

	//hvis begge paths er false, er square en node. 
	//Eller hvis vi er i første rad og ingen north wall, eller vi er i siste rad og ingen south wall
	return (!horisontalPath && !verticalPath) || (firstRow && !north) || (lastRow && !south);
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

int Square::getSize(){
	return size;
}

//old print
/*void Square::print(){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			int* temp = arr[i*size+j];
			cout << temp[0]<< " " << temp[1] << " " << temp[2] << " , ";
		}
		cout << endl;
	}
}*/

void Square::print(){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			int* temp = arr[i*size+j];
			Color c = getColor(temp);
			cout << c << " ";
		}
		cout << endl;
	}
}