#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

enum Color {BLACK,WHITE};
enum Direction {WEST,NORTH,EAST,SOUTH};

class Square{
private:
	int size = 16;
	int** arr;
	Color getColor(int* arr);
	int** walls = new int*[4];
public:
	int getOpeningCount();
	bool hasWall(Direction direction);
	bool isNode();
	Square(int**arr);
	void print();
};

#endif