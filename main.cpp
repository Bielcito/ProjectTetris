#include "board.h"
#include "pieces.h"
#include "instancegenerator.h"
#include "instancereader.h"
#include "instancesolver.h"
#include <iostream>
#include <string>
#include <unistd.h>
using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

int main()
{
    srand(time(0));

    // Comando usado para gerar as instâncias:
//    for(unsigned i = 1; i <= 100; ++i)
//    {
//        for(unsigned j = 0; j < 1000; ++j)
//        {
//            string a = to_string(i);
//            InstanceGenerator* g = new InstanceGenerator(i, i, InstanceGenerator::random_at_most(i/4));
//            g->generateInstance();
//            g->instanceToFile(a+"x"+a+"/instance_"+to_string(j)+".txt");
//            delete g;
//        }
//    }

	InstanceReader* g = new InstanceReader("10x10/instance_0.txt");
	cout << g->piecesToString() << endl;
	int* pieces = g->getPieces();
	Board* b = g->getBoard();

	InstanceSolver* h = new InstanceSolver(pieces, b);
	h->solveInstance();

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
