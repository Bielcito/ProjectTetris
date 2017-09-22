#ifndef INSTANCEGENERATOR_H
#define INSTANCEGENERATOR_H

#include "board.h"

class InstanceGenerator
{
public:
	InstanceGenerator(Board* b);
	InstanceGenerator(unsigned int rows, unsigned int cols, unsigned int numWalls);
	int fill(unsigned int row, unsigned int col);

	int getNumWalls();
private:
	void fillAux(Board* aux, unsigned int row, unsigned int col, int &count);
	Board* board;
	int numWalls;
};

#endif // INSTANCEGENERATOR_H
