#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <iostream>
#include "Square.h"

class Parser{
private:
	int width, height;
	png_byte color_type;
	png_byte bit_depth;
	png_bytep *row_pointers;
	int* getPixels(int x, int y);
	int squares;
public:
	Parser(char* fname);
	~Parser();
	void process();
	//void write(char* fname);
	Square** parse();
	int getSquareNumber();
	int getHeight();
	int getWidth();
};
#endif