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
	if(this->solverHeap.back()->state >= this->pieceList.size()-1)
    {
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

void InstanceSolver::solveInstance2()
{
	if(board->getSpace(row, col)->isWall())
	{
		nextPosition();
	}

	getNextPiece();

	while(true)
	{
		getNextPiece();
		retrievePiece();
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
