#include "board.h"

Board::Board(unsigned int n, unsigned int m)
{
    this->board = new Space*[n];

    for(size_t i = 0; i < n; ++i)
    {
        this->board[i] = new Space[m];
    }

    this->rowSize = n;
    this->colSize = m;
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
    return mountPieceAux(p->getPivot(), NULL, row, col);
}

bool Board::setBlock(Block *b, unsigned int row, unsigned int col)
{
    if(row >= this->rowSize && col >= this->colSize)
    {
        this->board[row][col].setBlock(b);
        return true;
    }

    return false;
}

bool Board::mountPieceAux(Block *actual, Block *last, int row, int col)
{
    bool flag = true;

    // Testa os parâmetros, retorna falso se menor que zero
    if(row < 0 || col < 0)
    {
        return false;
    }

    // Posiciona a peça da vez no tabuleiro, retorna verdadeiro se conseguir
    if(this->setBlock(actual, row, col))
    {
        if(actual->get(Up) && actual->get(Up) != last)
        {
            flag = flag && this->mountPieceAux(actual->get(Up), actual, row-1, col);
        }
        if(actual->get(Down) && actual->get(Down) != last)
        {
            flag = flag && this->mountPieceAux(actual->get(Down), actual, row+1, col);
        }
        if(actual->get(Left) && actual->get(Left) != last)
        {
            flag = flag && this->mountPieceAux(actual->get(Left), actual, row, col-1);
        }
        if(actual->get(Right) && actual->get(Right) != last)
        {
            flag = flag && this->mountPieceAux(actual->get(Right), actual, row, col+1);
        }
    }

    return flag;
}
