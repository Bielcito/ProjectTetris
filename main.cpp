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

    cout << board.mountPiece(&p, 0, 1) << endl;

    return 0;
}
