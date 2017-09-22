#include "piece.h"

Piece::Piece(Pieces P)
{
    this->blocks = vector<Block*>(4);

    for(int i = 0; i < 4; ++i)
    {
		this->blocks[i] = new Block(this, i);
    }

	this->pivot = 0;

    // x 1 2
    //   3
    if(P == Pieces::T)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[1]->connect(blocks[2], Direction::Right);
        this->blocks[1]->connect(blocks[3], Direction::Down);
    }
    // x 1 2
    // 3
    else if(P == Pieces::L)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[1]->connect(blocks[2], Direction::Right);
        this->blocks[0]->connect(blocks[3], Direction::Down);
    }
    // x 1 2
    //     3
    else if(P == Pieces::_L)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[1]->connect(blocks[2], Direction::Right);
        this->blocks[2]->connect(blocks[3], Direction::Down);
    }
    //   x 1
    // 2 3
    else if(P == Pieces::S)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[2]->connect(blocks[3], Direction::Right);
		this->blocks[0]->connect(blocks[3], Direction::Down);
		this->isAxisRotationEqual = true;
    }
    // x 1
    //   2 3
    else if(P == Pieces::_S)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[2]->connect(blocks[3], Direction::Right);
        this->blocks[1]->connect(blocks[2], Direction::Down);
		this->isAxisRotationEqual = true;
    }
    // x 1 2 3
    else if(P == Pieces::I)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[1]->connect(blocks[2], Direction::Right);
        this->blocks[2]->connect(blocks[3], Direction::Right);
		this->isAxisRotationEqual = true;
    }
    // x 1
    // 2 3
    else if(P == Pieces::O)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[2]->connect(blocks[3], Direction::Right);
        this->blocks[0]->connect(blocks[2], Direction::Down);
		this->isAllRotationEqual = true;
	}
}

Piece::Piece(Pieces p, Piece::Rotation r) : Piece(p)
{
	if(r == _90)
	{
		if(this->isAllRotationEqual)
		{
			return;
		}

		this->rotate90();
	}
	else if(r == _180)
	{
		if(this->isAxisRotationEqual || this->isAllRotationEqual)
		{
			return;
		}

		this->rotate180();
	}
	else if(r == _270)
	{
		if(this->isAllRotationEqual)
		{
			return;
		}

		this->rotate270();
	}
}

string Piece::toString()
{
	string r = "";
	for(int i = 0; i < 4; i++)
	{
		r += "peça["+std::to_string(i)+"]"+toStringAux(this->blocks[i]) + "\n";
	}

	return r;
}

unsigned int Piece::getPivot()
{
    return this->pivot;
}

vector<Block*> Piece::getBlocks()
{
    return this->blocks;
}

void Piece::rotate90()
{
    for(int i = 0; i < 4; i++)
    {
        this->blocks[i]->rotate90();
    }

	this->reallocatePivot();
}

void Piece::rotate180()
{
    for(int i = 0; i < 4; i++)
    {
        this->blocks[i]->rotate180();
    }

	this->reallocatePivot();
}

void Piece::rotate270()
{
    for(int i = 0; i < 4; i++)
    {
        this->blocks[i]->rotate270();
	}

	this->reallocatePivot();
}

void Piece::reallocatePivot()
{
	Block* aux = this->blocks[this->pivot];
	while(true)
	{
		if(aux->get(Up) != NULL)
		{
			aux = aux->get(Up);
		}
		else if(aux->get(Left) != NULL)
		{
			aux = aux->get(Left);
		}
		else
		{
			break;
		}
	}

	this->pivot = aux->getIndex();
}

string Piece::toStringAux(Block* b)
{
	string r = "";
	if(b->get(Up))
	{
		r+="up ";
	}
	if(b->get(Down))
	{
		r+="down ";
	}
	if(b->get(Left))
	{
		r+="left ";
	}
	if(b->get(Right))
	{
		r+="right ";
	}
	return r;
}
