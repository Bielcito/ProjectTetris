#ifndef PIECE_H
#define PIECE_H

#include "block.h"
#include "pieces.h"
#include <string>
#include <vector>
#include <iostream>
using std::vector;
using std::string;
using std::runtime_error;
using std::cout;
using std::endl;

class Block;

class Piece
{
public:
    Piece(Pieces p);
    string toString();
    Block* getPivot();
    vector<Block*> getBlocks();
    void rotate90();
    void rotate180();
    void rotate270();
private:
    string toStringAux(Block *actual, Block* last, std::string r);
    vector<Block*> blocks;
    Block* pivot;
};

#endif // PIECE_H
