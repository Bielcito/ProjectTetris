#ifndef SPACE_H
#define SPACE_H

#include "block.h"

class Block;

class Space
{
public:
    Space();
    void setBlock(Block* block);
	void setWall(bool flag);
	bool isEmpty();
	bool isWall();
	void deleteBlock();
	Block* getBlock();

private:
    Block* block;
	bool wall;
};

#endif // SPACE_H
