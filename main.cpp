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

//	for(unsigned i = 6; i <= 6; ++i)
//	{
//		for(unsigned j = 0; j < 1000; ++j)
//		{
//			string a = to_string(i);
//			string dir = a+"x"+a;
//			mkdir(dir.c_str(), 0755);
//			InstanceGenerator* IG = new InstanceGenerator(i, i, InstanceGenerator::random_at_most(i));
//			IG->generateInstance();
//			IG->instanceToFile(a+"x"+a+"/instance_"+to_string(j)+".txt");
//			delete IG;
//		}
//	}

	for(int i = 0; i<1000; i++)
	{
		string path = "6x6/instance_"+to_string(i)+".txt";
		InstanceReader* IR = new InstanceReader(path);
		int* pieces = IR->getPieces();
		Board* b = IR->getBoard();

		InstanceSolver* IS = new InstanceSolver(pieces, b);
		IS->solveInstance();
		cout << i << endl;
		usleep(10000);
	}

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
