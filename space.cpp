#include "space.h"

Space::Space()
{
    this->block = NULL;
	this->wall = false;
}

void Space::setBlock(Block* block)
{
	this->block = block;
}

void Space::setWall(bool flag)
{
	this->wall = flag;
}

bool Space::isEmpty()
{
	if(this->block || this->isWall())
	{
		return false;
	}

	return true;
}

bool Space::isWall()
{
	return this->wall;
}

Block* Space::getBlock()
{
	return this->block;
}
