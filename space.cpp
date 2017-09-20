#include "space.h"

Space::Space()
{
    this->block = NULL;
}

void Space::setBlock(Block *block)
{
    this->block = block;
}

bool Space::hasBlock()
{
    return this->block;
}
