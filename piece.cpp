#include "piece.h"

Piece::Piece(Pieces P)
{
    this->blocks = vector<Block*>(4);
    this->pivot = blocks[0];
    for(int i = 0; i < 4; ++i)
    {
        this->blocks[i] = new Block(this);
    }

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
    }
    // x 1
    //   2 3
    else if(P == Pieces::_S)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[2]->connect(blocks[3], Direction::Right);
        this->blocks[1]->connect(blocks[2], Direction::Down);
    }
    // x 1 2 3
    else if(P == Pieces::I)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[1]->connect(blocks[2], Direction::Right);
        this->blocks[2]->connect(blocks[3], Direction::Right);
    }
    // x 1
    // 2 3
    else if(P == Pieces::O)
    {
        this->blocks[0]->connect(blocks[1], Direction::Right);
        this->blocks[2]->connect(blocks[3], Direction::Right);
        this->blocks[0]->connect(blocks[2], Direction::Down);
    }
}

string Piece::toString()
{
    string result = toStringAux(this->pivot, NULL, "Pivot->");

    return result;
}

Block* Piece::getPivot()
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
}

void Piece::rotate180()
{
    for(int i = 0; i < 4; i++)
    {
        this->blocks[i]->rotate180();
    }
}

void Piece::rotate270()
{
    for(int i = 0; i < 4; i++)
    {
        this->blocks[i]->rotate270();
    }
}

string Piece::toStringAux(Block* actual, Block* last, string r)
{
    string result = "";
    if(actual->get(Up) && actual->get(Up) != last)
    {
        result += r + "Up->";
        result += toStringAux(actual->get(Up), actual, result);
        result += "\n";
    }
    if(actual->get(Down) && actual->get(Down) != last)
    {
        result += r + "Down->";
        result += toStringAux(actual->get(Down), actual, result);
        result += "\n";
    }
    if(actual->get(Left) && actual->get(Left) != last)
    {
        result += r + "Left->";
        result += toStringAux(actual->get(Left), actual, result);
        result += "\n";
    }
    if(actual->get(Right) && actual->get(Right) != last)
    {
        result += r + "Right->";
        result += toStringAux(actual->get(Right), actual, result);
        result += "\n";
    }

    return result;
}
