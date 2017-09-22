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
	enum Rotation{
		_0, _90, _180, _270
	};

	Piece(Pieces p);
	Piece(Pieces p, Rotation r);
    string toString();
	unsigned int getPivot();
    vector<Block*> getBlocks();
    void rotate90();
    void rotate180();
    void rotate270();
	void reallocatePivot();
private:
	string toStringAux(Block *b);
    vector<Block*> blocks;
	unsigned int pivot;
	bool isAxisRotationEqual = false;
	bool isAllRotationEqual = false;
};

#endif // PIECE_H
