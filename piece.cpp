#include "piece.h"

Piece::Piece(Pieces P)
{
    this->blocks = vector<Block*>(4);
    for(int i = 0; i < 4; ++i)
    {
        this->blocks[i] = new Block(this);
    }

    // 1 x 1
    //   1
    if(P == Pieces::T)
    {
        this->pivot = blocks[0];
        this->blocks[0]->connect(blocks[1], Direction::Down);
        this->blocks[0]->connect(blocks[2], Direction::Left);
        this->blocks[0]->connect(blocks[3], Direction::Right);
    }
    else if(P == Pieces::L)
    {

    }
    else if(P == Pieces::L)
    {

    }
    else if(P == Pieces::L)
    {

    }
    else if(P == Pieces::L)
    {

    }
    else if(P == Pieces::L)
    {

    }
}

string Piece::toString()
{
    string result = toStringAux(this->pivot, NULL, "Pivot->");

    return result;
}

Block *Piece::getPivot()
{
    return this->pivot;
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
