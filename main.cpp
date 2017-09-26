#include "board.h"
#include "pieces.h"
#include "instancegenerator.h"
#include "instancereader.h"
#include "instancesolver.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

int main()
{
	srand(time(0));

	// Gerador de instâncias funcionando:

	for(unsigned i = 4; i <= 4; ++i)
	{
		for(unsigned j = 0; j < 1; ++j)
		{
			string a = to_string(i);
			string dir = a+"x"+a;
			mkdir(dir.c_str(), 0755);
			InstanceGenerator* g = new InstanceGenerator(i, i, InstanceGenerator::random_at_most(i));
			g->generateInstance();
			g->instanceToFile(a+"x"+a+"/instance_"+to_string(j)+".txt");
			delete g;
		}
	}

	string path = "4x4/instance_0.txt";
	InstanceReader* g = new InstanceReader(path);
	int* pieces = g->getPieces();
	Board* b = g->getBoard();
	cout << b->toString() << endl;

//	InstanceSolver* h = new InstanceSolver(pieces, b);
//	h->solveInstance();

//	for(unsigned i = 0; i < 999999999; ++i)
//	{
//		Board* a = new Board(3, 3);

//		Piece* p = new Piece(Pieces::T);
//		p->rotate90();
//		p->rotate90();
//		p->rotate90();
//		a->mountPiece(p, 0, 0);

//		Piece* p2 = new Piece(Pieces::_L);
//		p2->rotate90();
//		a->mountPiece(p2, 0, 2);

//		cout << a->toString() << endl;

//		a->removePiece(0, 0);

//		cout << a->toString() << endl;

//		delete a;
//		usleep(1);
//	}

	return 0;

}
