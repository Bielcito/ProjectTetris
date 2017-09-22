#include "board.h"
#include "pieces.h"
#include "instancegenerator.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

int main()
{
	Board board(3, 3);
	board.getSpace(1,1)->setWall(true);
	cout << board.toString() << endl;

	InstanceGenerator* g = new InstanceGenerator(&board);
	cout << g->getNumWalls() << endl;

    return 0;
}
