#ifndef BOARD_H
#define BOARD_H

#include "space.h"
#include <cstdint>
#include <string>
#include <vector>
using std::size_t;
using std::string;
using std::to_string;

/**
 * @brief The Board class Responsável pelo gerenciamento do tabuleiro.
 */
class Board
{
public:
	Board(unsigned rows, unsigned cols);
    ~Board();

	string toString();

    size_t getRowSize();
    size_t getColSize();
	bool mountPiece(Piece *p, unsigned int row, unsigned int col, bool deletePiece = true);
	void removePiece(unsigned row, unsigned col, bool deletePiece);
	void removePieceAux(Piece* p, Block* b, Block *last);
    void insertWall(unsigned row, unsigned col);
    string memoryWallToString();
	string memoryPieceToString();
	bool hasPiece(unsigned row, unsigned col);

	Space* getSpace(unsigned int row, unsigned int col);
	bool hasSpace(int row, int col, Direction d);
	int memoryPieceCount();

private:

    Space** board;

    // Armazena todas as peças que foram encaixadas
    vector<vector<Piece*>> memoryPiece;

    size_t rowSize;
    size_t colSize;

	bool mountPieceAux(Block *actual, Block* last, int row, int col);

    struct MemoryWall{
        unsigned row;
        unsigned col;
    };

    vector<MemoryWall> memoryWall;
};

#endif // BOARD_H
