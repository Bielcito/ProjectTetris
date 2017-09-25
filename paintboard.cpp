#include "paintboard.h"

PaintBoard::PaintBoard(unsigned row, unsigned col)
{
	this->board = new TypeIden*[row];
	for(unsigned int i = 0; i < row; i++)
	{
		this->board[i] = new TypeIden[col];
		for(unsigned int j = 0; j < col; j++)
		{
			this->board[i][j].type = -1;
			this->board[i][j].number = 0;
		}
	}

	this->row = row;
    this->col = col;
}

PaintBoard::~PaintBoard()
{
    for(unsigned i = 0; i < this->row; ++i)
    {
        delete[] this->board[i];
    }

    delete[] this->board;
}

void PaintBoard::paint(int type, int number, unsigned int row, unsigned int col)
{
	this->board[row][col].type = type;
	this->board[row][col].number = number;
}

bool PaintBoard::isPainted(unsigned int row, unsigned int col)
{
	if(this->board[row][col].type == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int* PaintBoard::getNumbers()
{
	return this->numbers;
}

string PaintBoard::toString()
{
	string result = "";

	for(unsigned i = 0; i < this->row; ++i)
	{
		for(unsigned j = 0; j < this->col; ++j)
		{
			result += std::to_string(this->board[i][j].type)+"-"+std::to_string(this->board[i][j].number)+" ";
		}

		result += "\n";
	}

	return result;
}
