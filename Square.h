#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

enum Color {BLACK,WHITE};
enum Direction {WEST,NORTH,EAST,SOUTH};

class Square{
private:
	int size = 16;
	int** arr;
	int** walls = new int*[4];
	Color getColor(int* arr);
	int row;
	int col;
public:
	int getOpeningCount();
	bool hasWall(Direction direction);
	bool isNode();
	Square(int**arr, int col, int row);
	void print();
	int getSize();
	void printCoords();
};

#endif