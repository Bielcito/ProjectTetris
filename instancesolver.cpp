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
    if(this->solverHeap.back()->state == this->pieceList.size())
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
	//Inicializa o Solver Heap com seu primeiro elemento:
	this->getNextPiece();
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

void InstanceSolver::fillPieceList()
{
    unsigned value = 0;

    for(unsigned i = 0; i < 7; ++i)
    {
        for(int j = 0; j < pieces[i]; ++j)
        {
            PieceList* pl = new PieceList();
            pl->value = value++;
            pl->p = new Piece((Pieces)pieces[i]);

            this->pieceList.push_back(pl);
        }
    }
}
