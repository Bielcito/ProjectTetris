#include "board.h"

Board::Board(unsigned int n, unsigned int m)
{
    this->board = new Space*[n];
	for(unsigned int i = 0; i < n; ++i)
    {
		this->board[i] = new Space[m];
    }

	this->memory = vector<Memory>();

    this->rowSize = n;
	this->colSize = m;
}

string Board::toString()
{
	string result = "";
	for(unsigned int i = 0; i < this->rowSize; i++)
	{
		for(unsigned int j = 0; j < this->colSize; j++)
		{
			if(this->board[i][j].isEmpty())
			{
				result += "0 ";
			}
			else
			{
				if(this->board[i][j].isWall())
				{
					result += "X ";
				}
				else
				{
					result += "1 ";
				}
			}
		}
		result += "\n";
	}

	return result;
}

size_t Board::getRowSize()
{
    return this->rowSize;
}

size_t Board::getColSize()
{
    return this->colSize;
}

bool Board::mountPiece(Piece* p, unsigned int row, unsigned int col)
{
	if(mountPieceAux(p->getBlocks()[p->getPivot()], NULL, row, col))
	{
		this->fixBlock();
		return true;
	}
	else
	{
		this->memory.clear();
		return false;
	}
}

Space* Board::getSpace(unsigned int row, unsigned int col)
{
	return &this->board[row][col];
}

bool Board::hasSpace(int row, int col, Direction d)
{
	if(d == Up)
	{
		if(row > 0)
		{
			return true;
		}
	}
	else if(d == Down)
	{
		if(row < (int)this->rowSize-1)
		{
			return true;
		}
	}
	else if(d == Left)
	{
		if(col > 0)
		{
			return true;
		}
	}
	else
	{
		if(col < (int)this->colSize-1)
		{
			return true;
		}
	}

	return false;
}

bool Board::addMemoryPoint(Block* b, unsigned int row, unsigned int col)
{
	if(b == NULL)
	{
		return false;
	}

	if(row >= this->rowSize || col >= this->colSize)
    {
		return false;
    }

	if(!this->board[row][col].isEmpty())
	{
		return false;
	}

	Memory aux{b, row, col};
	this->memory.push_back(aux);

	return true;
}

void Board::fixBlock()
{
	for(unsigned int i = 0; i < this->memory.size(); ++i)
	{
		this->board[this->memory[i].row][this->memory[i].col].setBlock(this->memory[i].b);
	}
}

bool Board::mountPieceAux(Block* actual, Block* last, int row, int col)
{
    // Testa os parâmetros, retorna falso se menor que zero
    if(row < 0 || col < 0)
    {
        return false;
    }

	if(!this->addMemoryPoint(actual, row, col))
    {
		cout << "Erro ao setar bloco" << endl;
		return false;
    }

	if(actual->get(Up) && actual->get(Up) != last)
	{
		if(!this->mountPieceAux(actual->get(Up), actual, row-1, col))
		{
			return false;
		}
	}
	if(actual->get(Down) && actual->get(Down) != last)
	{
		if(!this->mountPieceAux(actual->get(Down), actual, row+1, col))
		{
			return false;
		}
	}
	if(actual->get(Left) && actual->get(Left) != last)
	{
		if(!this->mountPieceAux(actual->get(Left), actual, row, col-1))
		{
			return false;
		}
	}
	if(actual->get(Right) && actual->get(Right) != last)
	{
		if(!this->mountPieceAux(actual->get(Right), actual, row, col+1))
		{
			return false;
		}
	}

	return true;
}
