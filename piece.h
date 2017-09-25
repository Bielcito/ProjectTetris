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
using std::to_string;

class Block;

class Piece
{
public:
	enum Rotation{
		_0, _90, _180, _270
	};

	Piece(Pieces p);
	Piece(Pieces p, Rotation r);
    ~Piece();
    string toString();
	unsigned int getPivot();
    vector<Block*> getBlocks();
    void rotate90();
    void rotate180();
    void rotate270();
	void reallocatePivot();
    bool hasNextRotation();
	void clearRotation();
private:
	std::string text;
	string toStringAux(Block *b);
    vector<Block*> blocks;
	unsigned int pivot;
	bool isAxisRotationEqual = false;
	bool isAllRotationEqual = false;
    unsigned rotationState = 0;
};

#endif // PIECE_H
