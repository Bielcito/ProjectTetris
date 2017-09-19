#include "board.h"

Board::Board(size_t n, size_t m)
{
    this->board = new Space*[n];

    for(size_t i = 0; i < n; i++)
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

void Board::setPiece(int **p)
{

}
