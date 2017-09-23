#ifndef INSTANCEGENERATOR_H
#define INSTANCEGENERATOR_H

#include "board.h"
#include "paintboard.h"
#include <stdlib.h>

class InstanceGenerator
{
public:
	InstanceGenerator(Board* b);
	InstanceGenerator(unsigned int rows, unsigned int cols, unsigned int numWalls);
	PaintBoard* fillAll();

	int getNumWalls();
	void addWall();
	long random_at_most(long max);
	int getBoardType(unsigned int row, unsigned int col);
	Board* getBoard();

private:
	void countNumWalls();
	bool fillAux(PaintBoard* aux, int lastType, int number, unsigned int row, unsigned int col);
	Board* board;
	int numWalls;
};

#endif // INSTANCEGENERATOR_H
