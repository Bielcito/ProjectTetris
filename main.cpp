#include "board.h"
#include "pieces.h"
#include "instancegenerator.h"
#include "instancereader.h"
#include "instancesolver.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <chrono>
using std::string;
using std::cout;
using std::endl;
using std::runtime_error;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

/**
 * @brief generateInstances
 * Cria 'num' instâncias de tamanho 'de' até 'ate'.
 * @param de
 * @param ate
 * @param num
 */
void generateInstances(unsigned de, unsigned ate, unsigned num)
{
	for(unsigned i = de; i <= ate; ++i)
	{
		for(unsigned j = 0; j < num; ++j)
		{
			string a = to_string(i);
			string dir = a+"x"+a;
			mkdir(dir.c_str(), 0755);
			InstanceGenerator* IG = new InstanceGenerator(i, i, InstanceGenerator::random_at_most(i));
			IG->generateInstance();
			IG->instanceToFile(a+"x"+a+"/instance_"+to_string(j)+".txt");
			delete IG;
		}
	}
}

/**
 * @brief instanceSolver
 * Resolve 'num' instâncias de problemas de tamanho 'number'.
 * @param num
 * @param number
 */
void instanceSolver(unsigned num, unsigned number)
{
	cout << "Resolvendo " << num << " instâncias de tamanho " << number << "x" << number << "." << endl;
	cout << "Pressione qualquer tecla para continuar..." << endl;
	cin.get();
	for(int i = 0; i<num; i++)
	{
		string path = to_string(number)+"x"+to_string(number)+"/instance_"+to_string(i)+".txt";
		InstanceReader* IR = new InstanceReader(path);
		int* pieces = IR->getPieces();
		Board* b = IR->getBoard();

		InstanceSolver* IS = new InstanceSolver(pieces, b);
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		IS->solveInstance();
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>( t2 - t1 ).count();
		delete IR;
		delete IS;
		cout << i << " " << duration << endl;
		usleep(10000);
	}
	cout << "Todas as instâncias foram resolvidas" << endl;
}

int main()
{
	srand(time(0));

	/* Não executar a função de gerar instâncias e de resolver
	 instâncias ao mesmo tempo, elas não foram feitas para
	 trabalhar juntas.
	*/

	// Gera instâncias de tamanho 4x4 até 7x7, descomentar:
	// generateInstances(4, 7, 1000);

	// Resolve as intâncias de tamanho 4x4, descomentar:
	instanceSolver(1000, 6);

	return 0;

}
