#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

enum Color {BLACK,WHITE};
enum Direction {WEST,NORTH,EAST,SOUTH};

class Square{
private:
	int size = 16;
	int** arr;
	bool* walls;
	void setWalls();
	Color getColor(int* arr);
	int row;
	int col;
public:
	int getOpeningCount();
	bool hasWall(Direction direction);
	bool isNode(bool firstRow, bool lastRow);
	Square(int**arr, int col, int row);
	void print();
	int getSize();
	void printCoords();
	void debugWalls();
};

#endif