#include "instancesolver.h"

InstanceSolver::InstanceSolver(int* pieces, Board* b)
{
    this->pieces = pieces;
    this->board = b;

	this->fillPieceList();
}

InstanceSolver::~InstanceSolver()
{
	for(unsigned i = 0; i < pieceList.size(); i++)
	{
		delete pieceList[i]->p;
	}
}

string InstanceSolver::pieceListToString()
{
    string result = "";

    for(unsigned i = 0; i < this->pieceList.size(); i++)
    {
        result += to_string(this->pieceList[i]->value) + " " + this->pieceList[i]->p->toString() + "\n";
    }

    return result;
}

bool InstanceSolver::hasNextPiece()
{
	if(this->solverHeap.size() == 0 && this->pieceList.size() > 0)
	{
		return true;
	}

	if(this->solverHeap.back()->state >= this->pieceList.size()-1)
    {
//		cout << "Sem próximas peças." << endl;
//		cout << this->solverHeap.size() << endl;
        return false;
    }
    else
    {
        return true;
	}
}

/**
 * @brief InstanceSolver::getNextPiece
 * Pega a próxima peça a ser inserida no solveHeap
 */
void InstanceSolver::getNextPiece()
{	
	unsigned state;

	// Checa se o solveHeap está vazio:
	if(this->solverHeap.empty())
	{
		state = this->mainState;
	}
	else
	{
		state = this->solverHeap.back()->state;
	}

	if(state >= this->pieceList.size())
	{
		return;
	}

	// Salvo a peça que está na lista:
	PieceList* pl = this->pieceList[state];

	// Apago a peça da lista:
	this->pieceList.erase(this->pieceList.begin()+state);

	// Coloca no solver:
	SolverHeap* sh = new SolverHeap();
	sh->pl = pl;
	sh->state = 0;

	this->solverHeap.push_back(sh);
}

void InstanceSolver::retrievePiece(bool clearRotation)
{
	// Retira a peça do tabuleiro:
	if(this->board->hasPiece(row, col))
	{
		this->board->removePiece(row, col, false);
	}

	// Guarda a última peça do solver:
	SolverHeap* aux = this->solverHeap.back();
	PieceList* pl = aux->pl;
	delete aux;

	// Reseta a rotação da peça:
	if(clearRotation)
	{
		pl->p->clearRotation();
	}

	//delete this->solverHeap.back();
	this->solverHeap.pop_back();

    // Insere em sua respectiva posição na lista:
    this->insertToPieceList(pl);
}

bool InstanceSolver::isPieceListEmpty()
{
    if(this->pieceList.empty())
    {
        return true;
    }

	return false;
}

string InstanceSolver::solverHeapToString()
{
	string result = "";
	for(unsigned i = 0; i < solverHeap.size(); i++)
	{
		result += to_string(solverHeap[i]->pl->value) + " " + solverHeap[i]->pl->p->toString() + " " + to_string(solverHeap[i]->state) + "\n";
	}

	return result;
}

void InstanceSolver::solveInstance()
{
	// Verifica se o espaço inicial é um muro, se não for, pega o próximo:
	if(board->getSpace(row, col)->isWall())
	{
		nextPosition();
	}

	getNextPiece();

	while(true)
	{
		checkForRetrieve();
		insertPiece();
		if(checkIfEnds())
		{
			return;
		}
	}
}

void InstanceSolver::solveHeuristic(unsigned time)
{
	// Configuração inicial:
	firstConfiguration();

	// Início da meta-heurística:
	high_resolution_clock::time_point t1, t2, diff;

	// Tempo que inicia a metaheurística:
	t1 = high_resolution_clock::now();

	while(true)
	{
		t2 = high_resolution_clock::now();
		unsigned duration = duration_cast<microseconds>( t2 - t1 ).count();
		if(duration > time)
		{
			break;
		}
		cout << duration << endl;

		/*t2 =
		diff = t2 - t1;

		removeBunchPieces();
		if(changeRandomPieceWithRandomEmptySpace() || changeTwoRandomPiecesPosition())
		{
			if(insertAnotherPiece())
			{
				break;
			}
		}*/
	}
}

void InstanceSolver::stop()
{
	cout << endl;
	cout << this->board->toString() << endl;
	cout << this->pieceListToString() << endl;
	cout << this->solverHeapToString() << endl;
	cout << "row: " << row << " col: " << col << endl;
	std::cin.get();
	system("clear");
}

void InstanceSolver::insertToPieceList(PieceList* pl)
{
	if(this->pieceList.size() == 0)
	{
		this->pieceList.push_back(pl);
	}
	else
	{
		for(unsigned i = 0; i <= this->pieceList.size(); ++i)
		{
			if(pl->value < this->pieceList[i]->value || i == this->pieceList.size())
			{
				this->pieceList.insert(this->pieceList.begin()+i, pl);
				break;
			}
		}
	}
}

void InstanceSolver::incrementState()
{
	if(this->solverHeap.empty())
	{
		++this->mainState;
	}
	else
	{
		++this->solverHeap.back()->state;
	}
}

void InstanceSolver::resetState()
{
	if(this->solverHeap.empty())
	{
		this->mainState = 0;
	}
	else
	{
		this->solverHeap.back()->state = 0;
	}
}

bool InstanceSolver::hasNextPosition()
{
	if(this->row < this->board->getRowSize()-1 || this->col < this->board->getColSize()-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void InstanceSolver::nextPosition()
{
	while(true)
	{
		if(row == board->getRowSize()-1 && col == board->getColSize()-1)
		{
			return;
		}
		else
		{
			col++;
			if(col == board->getColSize())
			{
				col = 0;
				row++;
			}

			if(board->getSpace(row, col)->isEmpty())
			{
				return;
			}
		}
	}
}

void InstanceSolver::lastPosition()
{
	while(true)
	{
		if(row == 0 && col == 0)
		{
			return;
		}
		else
		{
			if(col == 0)
			{
				col = board->getColSize()-1;
				row--;
			}
			else
			{
				col--;
			}

			if(!board->getSpace(row, col)->isWall())
			{
				return;
			}
		}
	}
}

void InstanceSolver::lastPositionRecursive()
{
	while(true)
	{
		if(row == 0 && col == 0)
		{
			return;
		}

		lastPosition();

		if(board->hasPiece(row, col))
		{
			return;
		}
	}
}

bool InstanceSolver::checkIfPieceFitsOnBoard()
{
	// Verifica se há alguma peça a ser verificada:
	if(solverHeap.size() == 0)
	{
		return false;
	}

	Piece* p = this->solverHeap.back()->pl->p;

	if(this->board->mountPiece(p, this->row, this->col, false))
	{
		this->solverHeap.back()->mounted = true;
		return true;
	}
	else
	{
		return false;
	}
}

bool InstanceSolver::hasNextRotation()
{
	if(this->solverHeap.back()->pl->p->hasNextRotation())
	{
		return true;
	}

	return false;
}

void InstanceSolver::rotate(bool mounted)
{
	// Caso a peça já esteja montada:
	if(mounted)
	{
		unsigned rotation = this->solverHeap.back()->pl->p->getRotationState();

		retrievePiece();
		getNextPiece();

		for(unsigned i = 0; i < rotation; i++)
		{
			rotate();
		}
	}
	else
	{
		this->solverHeap.back()->pl->p->rotate90();
	}
}

string InstanceSolver::lastPieceToString()
{
	return this->solverHeap.back()->pl->p->toString();
}

void InstanceSolver::insertPiece()
{
	// Verifica se ela encaixa:
	if(checkIfPieceFitsOnBoard())
	{
		// Caso encaixe, muda a posição para a próxima:
		nextPosition();
		getNextPiece();
		return;
	}
	else
	{
		// Caso não encaixe, começa o processo para ver se deve retirar a peça ou não:
		while(true)
		{
			// Verifica se o solver tem alguma peça, se não tiver, sai do loop.
			if(this->solverHeap.size() == 0)
			{
				break;
			}
			// Caso a peça tenha uma próxima rotação
			if(hasNextRotation())
			{
				// Rotaciona
				rotate();
				// Verifica se encaixa
				if(checkIfPieceFitsOnBoard())
				{
					// Caso encaixe, vai para a próxima posição.
					nextPosition();
					// Pega a próxima peça:
					getNextPiece();
					return;
				}
				else
				{
					// Caso não encaixe, repete o processo:
					continue;
				}
			}
			else
			{
				retrievePiece();
				//lastPosition();

				incrementState();
				getNextPiece();
				break;
			}
		}
	}
}

void InstanceSolver::checkForRetrieve()
{
	// Verifica se o state é maior que o número de peças em PieceList:
	while(true)
	{
		// Verifica se há peças no solveHeap:
		if(solverHeap.size() == 0)
		{
			getNextPiece();
			break;
		}

		if(!solverHeap.back()->mounted)
		{
			return;
		}

		if(solverHeap.back()->state >= pieceList.size())
		{
			// Verifica se tem próxima rotação, se tiver, rotaciona e continua o processo:
			if(hasNextRotation())
			{
				lastPositionRecursive();
				retrievePiece(false);
				getNextPiece();
				rotate();
				resetState();
				break;
			}
			else
			{
				// Verifica se tem peça na posição atual, se não tiver, volta para a posição anterior
				if(!this->board->hasPiece(row, col))
				{
					lastPositionRecursive();
				}

				retrievePiece();
				incrementState();

				if(solverHeap.size() > 0)
				{
					if(!(solverHeap.back()->state >= pieceList.size()))
					{
						getNextPiece();
					}
				}
			}
		}
		else
		{
			break;
		}
	}
}

bool InstanceSolver::checkIfEnds()
{
	if(pieceList.size() == 0 && solverHeap.back()->mounted)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void InstanceSolver::fillPieceList()
{
    unsigned value = 0;

    for(unsigned i = 0; i < 7; ++i)
    {
        for(int j = 0; j < pieces[i]; ++j)
        {
            PieceList* pl = new PieceList();
            pl->value = value++;
			pl->p = new Piece((Pieces)i);

            this->pieceList.push_back(pl);
        }
    }
}

/**
 * @brief InstanceSolver::random_at_most
 * Generate random number between 0 and max (inclusive).
 * @param max
 * @return
 */
long InstanceSolver::random_at_most(long max)
{
    unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

    long x;
    do {
        x = random();
    }
    // This is carefully written not to overflow
    while (num_rand - defect <= (unsigned long)x);

    // Truncated division is intentional
	return x/bin_size;
}

void InstanceSolver::returnPieceToInicialPosition(Piece *p, unsigned p1, unsigned p2, unsigned pR)
{
	p->clearRotation();
	while(true)
	{
		if(p->getRotationState() == pR)
		{
			break;
		}
		else
		{
			p->rotate90();
		}
	}
	this->board->mountPiece(p, p1, p2, false);
}

void InstanceSolver::firstConfiguration()
{
	// Shuffle PieceList.
	std::random_shuffle(pieceList.begin(), pieceList.end());

	if(board->getSpace(row, col)->isWall())
	{
		nextPosition();
	}

	while(true)
	{
		// Para, caso não tenha próxima peça para ser pega.
		if(!hasNextPiece())
		{
//			cout << "Não tem próxima peça. Resetou estado." << endl;
			resetState();
			if(!hasNextPosition())
			{
//				cout << "Não tem próxima posição." << endl;
				break;
			}
			else
			{
//				cout << "next" << endl;
				nextPosition();
			}
		}

		// Pega próxima peça.
//		cout << "Pegou próxima peça." << endl;
		getNextPiece();

		while(true)
		{
			if(checkIfPieceFitsOnBoard())
			{
//				cout << "Peça encaixou. Next." << endl;
				nextPosition();
				break;
			}
			else
			{
//				cout << "Não encaixou." << endl;
				if(hasNextRotation())
				{
//					cout << "Rotacionou." << endl;
					rotate();
				}
				else
				{
//					cout << "Devolveu." << endl;
					retrievePiece();
					incrementState();
					break;
				}
			}
		}
	}
}

bool InstanceSolver::changeTwoRandomPiecesPosition()
{
	// Pega duas peças aleatórias, remove-as e pega suas posições:
	int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
	Piece *a = NULL,*b = NULL;
	int* numbers = generateTwoRandomNumbersWithoutRepeat(solverHeap.size()-1);

//	cout << "nubmers: " << numbers[0] << " " << numbers[1] << endl;

	int counter = 0;

	for(unsigned i = 0; i < this->board->getRowSize(); ++i)
	{
		for(unsigned j = 0; j < this->board->getColSize(); j++)
		{
			if(this->board->hasPiece(i, j))
			{
				if(counter == numbers[0])
				{
					a = this->board->getSpace(i, j)->getBlock()->getParentPiece();
					a1 = i;
					a2 = j;
					this->board->removePiece(i, j, false);
				}
				else if(counter == numbers[1])
				{
					b = this->board->getSpace(i, j)->getBlock()->getParentPiece();
					b1 = i;
					b2 = j;
					this->board->removePiece(i, j, false);
				}

				++counter;
			}
		}
	}

	// Tenta trocar as peças de posição:
	bool isA = false;
	bool isB = false;

	unsigned aR = a->getRotationState();
	unsigned bR = b->getRotationState();

	if(a->getNumber() == b->getNumber())
	{
		returnPieceToInicialPosition(a, a1, a2, aR);
		returnPieceToInicialPosition(b, b1, b2, bR);
		return false;
	}

	a->clearRotation();
	b->clearRotation();

	// tentando encaixar peça a na posição da peça b:
	while(true)
	{
		if(this->board->mountPiece(a, b1, b2, false))
		{
			isA = true;
			break;
		}
		else
		{
			if(a->hasNextRotation())
			{
				a->rotate90();
			}
			else
			{
				break;
			}
		}
	}

	if(isA)
	{
		// Tenta encaixar a peça b na posição da peça a:
		while(true)
		{
			if(this->board->mountPiece(b, a1, a2, false))
			{
				isB = true;
				break;
			}
			else
			{
				if(b->hasNextRotation())
				{
					b->rotate90();
				}
				else
				{
					// Funcionou A e não funcionou B:
					// Retira-se o A, e para.
					// Volta para a posição o A.
					this->board->removePiece(b1, b2, false);
					returnPieceToInicialPosition(a, a1, a2, aR);
					break;
				}
			}
		}
	}
	else
	{
		returnPieceToInicialPosition(a, a1, a2, aR);
	}

	if(!isB)
	{
		returnPieceToInicialPosition(b, b1, b2, bR);
	}
	else
	{
		return true;
	}

	return false;
}

bool InstanceSolver::changeRandomPieceWithRandomEmptySpace()
{
	// Escolhe a peça que será apagada para ser trocada com algum espaço em branco, salvando ela em 'a' e depois removendo-a:
	unsigned number = (unsigned) random_at_most(this->solverHeap.size()-1);
	unsigned a1, a2;
	Piece* a;

	unsigned counter = 0;

	for(unsigned i = 0; i < this->board->getRowSize(); ++i)
	{
		for(unsigned j = 0; j < this->board->getColSize(); j++)
		{
			if(this->board->hasPiece(i, j))
			{
				if(counter == number)
				{
					a = this->board->getSpace(i, j)->getBlock()->getParentPiece();
					a1 = i;
					a2 = j;
					this->board->removePiece(i, j, false);
				}

				++counter;
			}
		}
	}

	// Salva a posição inicial da peça:
	unsigned aR = a->getRotationState();

	// Percorre os espaços vazios sobrando e tenta encaixar a peça, evitando encaixar na mesma posição em que ela já se encontrava:
	for(unsigned i = 0; i < this->board->getRowSize(); ++i)
	{
		for(unsigned j = 0; j < this->board->getColSize(); ++j)
		{
			if(this->board->getSpace(i, j)->isEmpty())
			{
				a->clearRotation();

				while(true)
				{
					if(i != a1 && j != a2 && a->getRotationState() != aR)
					{
						if(this->board->mountPiece(a, i, j, false))
						{
							return true;
						}
						else
						{
							if(a->hasNextRotation())
							{
								a->rotate90();
							}
							else
							{
								break;
							}
						}
					}
					else
					{
						break;
					}
				}
			}
		}
	}

	returnPieceToInicialPosition(a, a1, a2, aR);

	return false;
}

bool InstanceSolver::insertAnotherPiece()
{
	// Percorre a pilha de peças disponíveis para serem encaixadas, e tenta encaixá-las em cada um dos espaços no tabuleiro:
	for(unsigned i = 0; i < this->pieceList.size(); ++i)
	{
		PieceList* pl = this->pieceList[i];

		for(unsigned j = 0; j < this->board->getRowSize(); ++j)
		{
			for(unsigned k = 0; k < this->board->getColSize(); ++k)
			{
				if(this->board->getSpace(j, k)->isEmpty())
				{
					while(true)
					{
						if(this->board->mountPiece(pl->p, j, k, false))
						{
							this->pieceList.erase(this->pieceList.begin() + i);
							SolverHeap* sh = new SolverHeap();
							sh->pl = pl;
							sh->state = 0;
							this->solverHeap.push_back(sh);
							return true;
						}
						else
						{
							if(pl->p->hasNextRotation())
							{
								pl->p->rotate90();
							}
							else
							{
								break;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

bool InstanceSolver::removeBunchPieces(double factor)
{
	// Inicializando vetor de peças:
	vector<int> pieces = vector<int>(this->solverHeap.size());
	for(unsigned i = 0; i < this->solverHeap.size(); ++i)
	{
		pieces[i] = i;
	}

	// Embaralhando:
	std::random_shuffle(std::begin(pieces), std::end(pieces));

	// Definindo o número de peças que serão removidas:
	unsigned counter = 0;
	unsigned value = (this->solverHeap.size()-1) * factor;
	unsigned piecesToBeRemoved = random_at_most(value)+1;
	cout << "removendo " << piecesToBeRemoved << " peças." << endl;

	// Removendo as peças:
	for(unsigned i = 0; i < this->board->getRowSize(); ++i)
	{
		for(unsigned j = 0; j < this->board->getColSize(); ++j)
		{
			if(this->board->hasPiece(i, j))
			{
				// Verifica se a peça que existe é igual a alguma das peças a serem deletadas:
				for(unsigned m = 0; m < piecesToBeRemoved; m++)
				{
					if(pieces[m] == counter)
					{
						// Caso tenha alguma peça na posição especificada, salva ela em uma variavel auxiliar,
						// adiciona ela resetada ao pieceList, e apaga ela do tabuleiro.
						Piece* p = this->board->getSpace(i, j)->getBlock()->getParentPiece();
						PieceList* pl = new PieceList();
						pl->p = p;
						pl->value = 0;
						this->pieceList.push_back(pl);
						this->board->removePiece(i, j, false);

						// Remove a peça do solverHeap:
						for(unsigned k = 0; k < solverHeap.size(); ++k)
						{
							if(solverHeap[k]->pl->p == p)
							{
								solverHeap.erase(solverHeap.begin() + k);
								break;
							}
						}
					}
				}

				++counter;
			}
		}
	}

	return false;
}

int* InstanceSolver::generateTwoRandomNumbersWithoutRepeat(unsigned size)
{
    int* numbers = new int[2];
	int a = (int) random_at_most(size);
    numbers[0] = a;
    int b = random_at_most(1);
    if((b == 0 || a == (int)size) && a != 0)
    {
        numbers[1] = random_at_most(a-1);
    }
    else if((b == 1 || a == 0) && a != (int)size)
    {
        numbers[1] = random_at_most(size-a-1) + a + 1;
    }

    return numbers;
}
