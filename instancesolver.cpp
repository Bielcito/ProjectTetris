#include "instancesolver.h"

InstanceSolver::InstanceSolver(int* pieces, Board* b)
{
    this->pieces = pieces;
    this->board = b;

    this->fillPieceList();
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

void InstanceSolver::retrievePiece()
{
	// Retira a peça do tabuleiro:
	if(this->board->hasPiece(row, col))
	{
		this->board->removePiece(row, col, false);
	}

	// Guarda a última peça do solver:
    PieceList* pl = this->solverHeap.back()->pl;

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
	insertPiece();
	stop();

	insertPiece();
	stop();

	insertPiece();
	stop();

	insertPiece();
	stop();

	insertPiece();
	stop();

	insertPiece();
	stop();

	insertPiece();
	stop();

	insertPiece();
	stop();

	insertPiece();
	stop();

	insertPiece();
	stop();
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
    for(unsigned i = 0; i < this->pieceList.size(); ++i)
    {
		if(pl->value < this->pieceList[i]->value || i == this->pieceList.size()-1)
        {
			this->pieceList.insert(this->pieceList.begin()+i, pl);
			break;
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

void InstanceSolver::nextPosition()
{
	for(unsigned i = this->row; i < this->board->getRowSize(); ++i)
	{
		for(unsigned j = this->col+1; j < this->board->getColSize(); ++j)
		{
			if(this->board->getSpace(i, j)->isEmpty())
			{
				this->row = i;
				this->col = j;
				return;
			}
		}

		this->col = 0;
	}
}

void InstanceSolver::lastPosition()
{
	if(solverHeap.size() == 0)
	{
		return;
	}

	for(int i = this->row; i >= 0; --i)
	{
		for(int j = this->col-1; j >= 0; --j)
		{
			if(this->board->hasPiece(i, j))
			{
				this->row = i;
				this->col = j;
				return;
			}
		}

		this->col = this->board->getColSize()-1;
	}
}

bool InstanceSolver::checkIfPieceFitsOnBoard()
{
	Piece* p = this->solverHeap.back()->pl->p;

	if(this->board->mountPiece(p, this->row, this->col, false))
	{
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
	getNextPiece();

	if(checkIfPieceFitsOnBoard())
	{
		nextPosition();
		return;
	}
	else
	{
		while(true)
		{
			if(hasNextRotation())
			{
				rotate();
				if(checkIfPieceFitsOnBoard())
				{
					nextPosition();
					return;
				}
				else
				{
					continue;
				}
			}
			else
			{
				// Peça que não encaixou.
				retrievePiece();
				incrementState();
			}
		}
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
