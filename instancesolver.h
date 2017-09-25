#ifndef INSTANCESOLVER_H
#define INSTANCESOLVER_H

#include <vector>
#include <string>
#include "board.h"
using std::vector;
using std::string;
using std::to_string;
using std::iterator;

class InstanceSolver
{
public:
    InstanceSolver(int* pieces, Board* b);
    string pieceListToString();
	string solverHeapToString();
	void solveInstance();

private:
    int* pieces;
    Board* board;
    void fillPieceList();

    // Funções da pilha:
    bool hasNextPiece();
    void getNextPiece();
	void retrievePiece();
    bool isPieceListEmpty();

    // Armazena todas as peças:
    vector<int> queue;

    // Armazena as peças de forma que possam ser inseridas de forma ordenada
    struct PieceList
    {
        unsigned value;
        Piece* p;
    };

    // Armazena a pilha que está resolvendo a instância
    struct SolverHeap
    {
        PieceList* pl;
        unsigned state;
    };

    void insertToPieceList(PieceList* pl);

    vector<PieceList*> pieceList;
    vector<SolverHeap*> solverHeap;
};

#endif // INSTANCESOLVER_H
