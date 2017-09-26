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
	if(this->solverHeap.back()->state >= this->pieceList.size())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void InstanceSolver::getNextPiece()
{	
	// Salvo a peça que está na lista:
    PieceList* pl = this->pieceList[0];

	// Apago a peça da lista:
    this->pieceList.erase(this->pieceList.begin());

    // Coloca no solver:
    SolverHeap* sh = new SolverHeap();
    sh->pl = pl;
    sh->state = 0;

	this->solverHeap.push_back(sh);
}

void InstanceSolver::retrievePiece()
{
    // Retira a última peça do solver:
    PieceList* pl = this->solverHeap.back()->pl;

    delete this->solverHeap.back();

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
		result += solverHeap[i]->pl->p->toString() + "\n";
	}

	return result;
}

void InstanceSolver::solveInstance()
{
	// Inicializa a primeira peça:
	this->getNextPiece();

	// Verifica se ela pode ser encaixada:
	if(this->checkIfPieceFitsOnBoard())
	{
		// Pega a próxima posição válida:
		this->nextPosition();

		// Chamo a próxima peça:
		this->getNextPiece();
		// Verifico se ela pode ser encaixada:
		if(this->checkIfPieceFitsOnBoard())
		{
			this->nextPosition();

			this->getNextPiece();
			if(this->checkIfPieceFitsOnBoard())
			{
				this->nextPosition();
				this->getNextPiece();
				if(this->checkIfPieceFitsOnBoard())
				{
					this->nextPosition();
					this->getNextPiece();
					if(this->checkIfPieceFitsOnBoard())
					{

					}
					else
					{
						cout << "Pôde não sô de quatro é mais gostoso :)" << endl;
						cout << lastPieceToString() << endl;
						cout << row << " " << col << endl;
						cout << this->board->toString() << endl;

						this->rotate();
						this->rotate();
						this->rotate();

						if(hasNextRotation())
						{
							this->rotate();
						}
						else
						{
							cout << "Cabou as rotação maluco" << endl;
						}

						if(this->checkIfPieceFitsOnBoard())
						{

						}
						else
						{
							cout << "Rotacionando tbm n deu certo, rapaz..." << endl;
						}
					}
				}
				else
				{
					cout << "Pôde não sô TRÊIS :(" << endl;
				}
			}
			else
			{
				cout << "Pôde não sô 2 :(" << endl;
			}
		}
		else
		{
			cout << "Pôde não sô :(" << endl;
		}
	}
	else
	{
		this->rotate();
	}

}

void InstanceSolver::insertToPieceList(PieceList* pl)
{
    for(unsigned i = 0; i < this->pieceList.size(); ++i)
    {
        if(pl->value < this->pieceList[i]->value)
        {
            this->pieceList.insert(this->pieceList.begin(), pl);
        }
	}
}

void InstanceSolver::incrementState()
{
	++this->solverHeap.back()->state;
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
	for(int i = this->row; i >= 0; --i)
	{
		for(int j = this->col-1; j >= 0; --j)
		{
			if(this->board->hasPiece(i, j))
			{
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

void InstanceSolver::rotate()
{
	this->solverHeap.back()->pl->p->rotate90();
}

string InstanceSolver::lastPieceToString()
{
	return this->solverHeap.back()->pl->p->toString();
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
