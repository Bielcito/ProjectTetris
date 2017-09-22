#ifndef BOARD_H
#define BOARD_H

#include "space.h"
#include <cstdint>
#include <string>
using std::size_t;
using std::string;

/**
 * @brief The Board class Responsável pelo gerenciamento do tabuleiro.
 */
class Board
{
public:
    Board(unsigned int n, unsigned int m);

	string toString();

    size_t getRowSize();
    size_t getColSize();
    bool mountPiece(Piece *p, unsigned int row, unsigned int col);

	Space* getSpace(unsigned int row, unsigned int col);
	bool hasSpace(int row, int col, Direction d);

private:
    Space** board;
    size_t rowSize;
    size_t colSize;

    bool mountPieceAux(Block *actual, Block* last, int row, int col);
	bool addMemoryPoint(Block* b, unsigned int row, unsigned int col);
	void fixBlock();

	struct Memory{
        Block* b;
		unsigned int row;
		unsigned int col;
    };

	vector<Memory> memory;
};

#endif // BOARD_H
