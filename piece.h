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

class Block;

class Piece
{
public:
    Piece(Pieces p);
    string toString();
private:
    string toStringAux(Block *actual, Block* last, std::string r);
    vector<Block*> blocks;
    Block* pivot;
};

#endif // PIECE_H
