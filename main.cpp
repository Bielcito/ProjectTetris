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
	for(int i = 0; i<num; i++)
	{
		string path = to_string(number)+"x"+to_string(number)+"/instance_"+to_string(i)+".txt";
		InstanceReader* IR = new InstanceReader(path);
		int* pieces = IR->getPieces();
		Board* b = IR->getBoard();

		InstanceSolver* IS = new InstanceSolver(pieces, b);
		IS->solveInstance();
		cout << i << endl;
		usleep(10000);
	}
}

int main()
{
	srand(time(0));

	/* Não executar a função de gerar instâncias e de resolver
	 instâncias ao mesmo tempo, elas não foram feitas para
	 trabalhar juntas.
	*/

	// Gera instâncias, descomentar:
	// generateInstances(4, 10, 1000);

	// Resolve as intâncias, descomentar:
	// instanceSolver(1000, 7);

	/* Infelizmente essa função "instanceSolver" está com memory leak em algum lugar...
	 o uso de memória vai aumentando aos poucos, é algo que
	 não deu tempo de corrigir, mas que provavelmente não é tão difícil.
	 recomendo resolver um número pequeno de instâncias, e acompanhar pelo comando
	 'top' o quanto a memória está incrementando.
	 o processo de acúmulo de memória é um tanto lento para um método de brute force,
	 quanto maior o tamanho do tabuleiro, mais rápido aumenta o uso de memória.
	 O tempo médio para estourar a memória é de uns 5 minutos, dependo da velocidade
	 de processamento do computador.
	 mas mesmo assim, recomendo parar o processo quando atingr uns 50% do uso de memória.
	 PARA PARAR A EXECUÇÃO, BASTA DAR UM CTRL+C NA JANELA DE EXECUÇÃO DO CÓDIGO.
	 Para 1000 instâncias de tamanho igual a 4, 5 e 6, o risco de dar problemas é muito baixo.
	 Para 1000 instâncias de tamanho 7 para cima, comece a se preocupar
	*/

	return 0;

}
