#include "board.h"
#include "pieces.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

int main()
{
    Board board(20, 8);
    Piece p(Pieces::T);
    cout << "Up: " << p.getBlocks()[1]->get(Up) << endl;
    cout << "Down: " << p.getBlocks()[1]->get(Down) << endl;
    cout << "Left: " << p.getBlocks()[1]->get(Left) << endl;
    cout << "Right: " << p.getBlocks()[1]->get(Right) << endl;

    p.rotate90();

    cout << endl;
    cout << "Up: " << p.getBlocks()[1]->get(Up) << endl;
    cout << "Down: " << p.getBlocks()[1]->get(Down) << endl;
    cout << "Left: " << p.getBlocks()[1]->get(Left) << endl;
    cout << "Right: " << p.getBlocks()[1]->get(Right) << endl;

    cout << board.mountPiece(&p, 0, 0) << endl;

    return 0;
}
