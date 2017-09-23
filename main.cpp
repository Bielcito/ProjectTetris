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
	/*Board board(3, 3);
	board.getSpace(1,1)->setWall(true);​
	cout << board.toString() << endl;*/

	srand(time(0));
	InstanceGenerator* g = new InstanceGenerator(4, 4, 4);
	cout << g->fillAll()->toString() << endl;
	return 0;
}
