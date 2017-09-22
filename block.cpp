#include "block.h"

Block::Block(Piece* parentPiece)
{   
    this->parentPiece = parentPiece;
    this->up = NULL;
    this->down = NULL;
    this->left = NULL;
	this->right = NULL;
	this->index = 0;
}

Block::Block(Piece* parentPiece, unsigned int index) : Block(parentPiece)
{
	this->index = index;
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

Piece* Block::getParentPiece()
{
	return this->parentPiece;
}

unsigned int Block::getIndex()
{
	return this->index;
}

void Block::rotate90()
{
    Block* aux = this->up;
    this->up = this->left;
    this->left = this->down;
    this->down = this->right;
    this->right = aux;
}

void Block::rotate180()
{
    Block* aux = this->up;
    this->up = this->down;
    this->down = aux;

    aux = this->left;
    this->left = this->right;
    this->right = aux;
}

void Block::rotate270()
{
    Block* aux = this->up;
    this->up = this->right;
    this->right = this->down;
    this->down = this->left;
	this->left = aux;
}

Block::~Block()
{
	this->parentPiece = NULL;
	this->parentSpace = NULL;
	this->up = NULL;
	this->down = NULL;
	this->left = NULL;
	this->right = NULL;
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
