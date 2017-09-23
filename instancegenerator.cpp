#include "instancegenerator.h"

InstanceGenerator::InstanceGenerator(unsigned int rows, unsigned int cols, unsigned int numWalls)
{
	this->board = new Board(rows, cols);
	for(unsigned int i = 0; i < numWalls; ++i)
	{
		this->addWall();
	}
}

InstanceGenerator::InstanceGenerator(Board* b)
{
	this->board = b;
	countNumWalls();
}

PaintBoard* InstanceGenerator::fillAll()
{
	PaintBoard* aux = new PaintBoard(this->board->getRowSize(), this->board->getColSize());

	// Pega o tipo da posição:
	for(unsigned int i = 0; i < this->board->getRowSize(); ++i)
	{
		for(unsigned int j = 0; j < this->board->getColSize(); ++j)
		{
			int type = this->getBoardType(i, j);
			int number = aux->getNumbers()[type];
			if(this->fillAux(aux, type, number, i, j))
			{
				++aux->getNumbers()[type];
			}
		}
	}

	return aux;
}

int InstanceGenerator::getNumWalls()
{
	return this->numWalls;
}

void InstanceGenerator::addWall()
{
	int row, col;
	row = random_at_most(this->board->getRowSize()-1);
	col = random_at_most(this->board->getColSize()-1);

	if(this->board->getSpace(row, col)->isWall())
	{
		return;
	}

	this->board->getSpace(row, col)->setWall(true);
	++this->numWalls;
}

long InstanceGenerator::random_at_most(long max)
{
	unsigned long
	// max <= RAND_MAX < ULONG_MAX, so this is okay.
	num_bins = (unsigned long) max + 1,
	num_rand = (unsigned long) RAND_MAX + 1,
	bin_size = num_rand / num_bins,
	defect   = num_rand % num_bins;

	long x;
	do {
		x = random();
	}
	// This is carefully written not to overflow
	while (num_rand - defect <= (unsigned long)x);

	// Truncated division is intentional
	return x/bin_size;
}

int InstanceGenerator::getBoardType(unsigned int row, unsigned int col)
{
	if(this->board->getSpace(row, col)->isEmpty())
	{
		return 0;
	}
	else
	{
		if(this->board->getSpace(row, col)->isWall())
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
}

Board* InstanceGenerator::getBoard()
{
	return this->board;
}

void InstanceGenerator::countNumWalls()
{
	this->numWalls = 0;
	for(unsigned int i = 0; i < this->board->getRowSize(); i++)
	{
		for(unsigned int j = 0; j < this->board->getColSize(); j++)
		{
			if(this->board->getSpace(i, j)->isWall())
			{
				++this->numWalls;
			}
		}
	}
}

bool InstanceGenerator::fillAux(PaintBoard* aux, int lastType, int number, unsigned int row, unsigned int col)
{
	// Verifica se já foi pintado:
	if(aux->isPainted(row, col))
	{
		return false;
	}

	// Verifica se o tipo do atual é o mesmo do anterior, se sim, pinta.
	if(this->getBoardType(row, col) == lastType)
	{
		aux->paint(lastType, number, row, col);
	}
	else
	{
		return false;
	}

	// Chama recursivamente para os próximo:
	if(this->board->hasSpace(row, col, Up))
	{
		this->fillAux(aux, lastType, number, row-1, col);
	}
	if(this->board->hasSpace(row, col, Down))
	{
		this->fillAux(aux, lastType, number, row+1, col);
	}
	if(this->board->hasSpace(row, col, Left))
	{
		this->fillAux(aux, lastType, number, row, col-1);
	}
	if(this->board->hasSpace(row, col, Right))
	{
		this->fillAux(aux, lastType, number, row, col+1);
	}

	return true;
}
