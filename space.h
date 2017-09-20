#ifndef SPACE_H
#define SPACE_H

#include "block.h"

class Block;

class Space
{
public:
    Space();
    void setBlock(Block* block);
    bool hasBlock();
private:
    Block* block;
};

#endif // SPACE_H
