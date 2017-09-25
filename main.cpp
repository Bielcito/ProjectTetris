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
    cout << h->pieceListToString() << endl;

	return 0;

}
