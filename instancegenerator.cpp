#include "instancegenerator.h"

InstanceGenerator::InstanceGenerator(unsigned int rows, unsigned int cols, unsigned int numWalls)
{
	this->board = new Board(rows, cols);
}

InstanceGenerator::InstanceGenerator(Board* b)
{
	this->board = b;
	int size = b->getRowSize() * b->getColSize();
	int fill = this->fill(0, 0);
	this->numWalls = size - fill;
}

int InstanceGenerator::fill(unsigned int row, unsigned int col)
{
	int count = 0;
	Board aux(this->board->getRowSize(), this->board->getColSize());
	this->fillAux(&aux, row, col, count);

	return count;
}

int InstanceGenerator::getNumWalls()
{
	return this->numWalls;
}

void InstanceGenerator::fillAux(Board* aux, unsigned int row, unsigned int col, int &count)
{
	if(!aux->getSpace(row, col)->isWall() && this->board->getSpace(row, col)->isEmpty())
	{
		aux->getSpace(row, col)->setWall(true);
		++count;

		if(this->board->hasSpace(row, col, Up))
		{
			this->fillAux(aux, row-1, col, count);
		}
		if(this->board->hasSpace(row, col, Down))
		{
			this->fillAux(aux, row+1, col, count);
		}
		if(this->board->hasSpace(row, col, Left))
		{
			this->fillAux(aux, row, col-1, count);
		}
		if(this->board->hasSpace(row, col, Right))
		{
			this->fillAux(aux, row, col+1, count);
		}
	}
	else
	{
		return;
	}
}
