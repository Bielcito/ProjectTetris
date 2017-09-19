#include "block.h"

Block::Block(Piece* parentPiece)
{   
    this->parentPiece = parentPiece;
    this->up = NULL;
    this->down = NULL;
    this->left = NULL;
    this->right = NULL;
}

void Block::connect(Block *block, Direction d)
{
    if(d == Up)
    {
        this->up = block;
        block->connectAux(this, Down);
    }
    else if(d == Down)
    {
        this->down = block;
        block->connectAux(this, Up);
    }
    else if(d == Left)
    {
        this->left = block;
        block->connectAux(this, Right);
    }
    else if(d == Right)
    {
        this->right = block;
        block->connectAux(this, Left);
    }
}

Block* Block::get(Direction d)
{
    if(d == Up)
    {
        return this->up;
    }
    else if(d == Down)
    {
        return this->down;
    }
    else if(d == Left)
    {
        return this->left;
    }
    else
    {
        return this->right;
    }
}

void Block::connectAux(Block *block, Direction d)
{
    if(d == Up)
    {
        this->up = block;
    }
    else if(d == Down)
    {
        this->down = block;
    }
    else if(d == Left)
    {
        this->left = block;
    }
    else if(d == Right)
    {
        this->right = block;
    }
}
