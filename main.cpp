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

	board.mountPiece(&p, 0, 1);
	board.mountPiece(&p, 2, 1);
	board.mountPiece(&p, 1, 3);

	cout << board.toString() << endl;

    return 0;
}
