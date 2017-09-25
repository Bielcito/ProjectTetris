#include "board.h"

Board::Board(unsigned rows, unsigned cols)
{
	this->board = new Space*[rows];
	for(unsigned int i = 0; i < rows; ++i)
    {
		this->board[i] = new Space[cols];
    }

	this->memoryPiece = vector< vector<Piece*> >(rows, vector<Piece*>(cols));

	this->rowSize = rows;
	this->colSize = cols;
}

Board::~Board()
{
	for(unsigned i = 0; i < this->rowSize; ++i)
    {
        delete[] this->board[i];
    }

    delete[] this->board;

	for(unsigned i = 0; i < this->memoryPiece.size(); ++i)
	{
		for(unsigned j = 0; j < this->memoryPiece[i].size(); j++)
		{
			delete this->memoryPiece[i][j];
		}
	}
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
	this->memoryPiece[row][col] = p;

    // Caso a peça tenha sido encaixada
	if(mountPieceAux(p->getBlocks()[p->getPivot()], NULL, row, col))
	{
		return true;
	}
	else
	{
        removePiece(row, col);
		return false;
    }
}

void Board::removePiece(unsigned row, unsigned col)
{
	Block* aux = this->getSpace(row, col)->getBlock();
	if(!aux)
	{
		return;
	}

	if(this->memoryPiece[row][col])
	{
		this->removePieceAux(aux, aux);
		delete this->memoryPiece[row][col];
		this->memoryPiece[row][col] = NULL;
	}
}

void Board::removePieceAux(Block* actual, Block* last)
{
    if(actual->get(Up) && actual->get(Up) != last)
    {
        removePieceAux(actual->get(Up), actual);
    }
    if(actual->get(Down) && actual->get(Down) != last)
    {
        removePieceAux(actual->get(Down), actual);
    }
    if(actual->get(Left) && actual->get(Left) != last)
    {
        removePieceAux(actual->get(Left), actual);
    }
    if(actual->get(Right) && actual->get(Right) != last)
    {
        removePieceAux(actual->get(Right), actual);
    }

	if(actual->getParentSpace())
	{
		actual->getParentSpace()->deleteBlock();
	}
}

void Board::insertWall(unsigned row, unsigned col)
{
    if(this->board[row][col].isEmpty())
    {
        this->board[row][col].setWall(true);

        MemoryWall aux = {
            row, col
        };

        this->memoryWall.push_back(aux);
    }
}

string Board::memoryWallToString()
{
    string aux = "";

    for(unsigned i = 0; i < this->memoryWall.size(); ++i)
    {
        aux += to_string(this->memoryWall[i].row) + " " + to_string(this->memoryWall[i].col) + "\n";
    }

	return aux;
}

string Board::memoryPieceToString()
{
	string result = "";

	for(unsigned i = 0; i < this->rowSize; ++i)
	{
		for(unsigned j = 0; j < this->colSize; ++j)
		{
			if(this->memoryPiece[i][j])
			{
				result += this->memoryPiece[i][j]->toString() + " ";
			}
			else
			{
				result += "  0 ";
			}
		}

		result += "\n";
	}

	return result;
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

bool Board::mountPieceAux(Block* actual, Block* last, int row, int col)
{
	// Seta o bloco:
	this->board[row][col].setBlock(actual);
	actual->setParentSpace(&this->board[row][col]);

    // Testa os parâmetros, retorna falso se menor que zero
    if(row < 0 || col < 0)
    {
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
