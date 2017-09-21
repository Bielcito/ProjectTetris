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
    void connect(Block* block, Direction d);
    Block* get(Direction d);

    void rotate90();
    void rotate180();
    void rotate270();

private:
    void connectAux(Block* block, Direction d);
    Piece* parentPiece;
    Space* parentSpace;
    Block* up;
    Block* down;
    Block* left;
    Block* right;
};

#endif // BLOCK_H
