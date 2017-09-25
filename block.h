#ifndef BLOCK_H
#define BLOCK_H

#include "piece.h"
#include "space.h"
#include "direction.h"

class Piece;
class Space;

class Block
{
public:
    Block(Piece* parentPiece);
	Block(Piece* parentPiece, unsigned int index);
    void connect(Block* block, Direction d);
    Block* get(Direction d);
	Piece* getParentPiece();
	Space* getParentSpace();
	void setParentSpace(Space* s);
	unsigned int getIndex();

    void rotate90();
    void rotate180();
    void rotate270();

	~Block();

private:
    void connectAux(Block* block, Direction d);
    Piece* parentPiece;
    Space* parentSpace;
    Block* up;
    Block* down;
    Block* left;
    Block* right;
	unsigned int index;
};

#endif // BLOCK_H
