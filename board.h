#ifndef BOARD_H
#define BOARD_H

#include "space.h"
#include <cstdint>
using std::size_t;

/**
 * @brief The Board class Responsável pelo gerenciamento do tabuleiro.
 */
class Board
{
public:
    Board(size_t n, size_t m);

    size_t getRowSize();
    size_t getColSize();

    void setPiece(int** p);

private:
    Space** board;
    size_t rowSize;
    size_t colSize;
};

#endif // BOARD_H
