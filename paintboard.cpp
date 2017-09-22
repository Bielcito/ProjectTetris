#include "paintboard.h"

PaintBoard::PaintBoard(unsigned int row, unsigned int col)
{
	this->board = new int*[row];
	for(int i = 0; i < row; i++)
	{
		this->board[i] = new int[col];
	}
}
