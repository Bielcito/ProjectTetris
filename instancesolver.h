#ifndef INSTANCESOLVER_H
#define INSTANCESOLVER_H

#include <vector>
#include <string>
#include "board.h"
using std::vector;
using std::string;
using std::to_string;
using std::iterator;
using std::cin;

class InstanceSolver
{
public:
    InstanceSolver(int* pieces, Board* b);
	~InstanceSolver();
    string pieceListToString();
	string solverHeapToString();
	void solveInstance();
	void stop();

private:
    int* pieces;
    Board* board;
    void fillPieceList();

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
		bool mounted = false;
	};

    // Funções da pilha:
    bool hasNextPiece();
	void getFirstPiece();
    void getNextPiece();
	void retrievePiece(bool clearRotation = true);
    bool isPieceListEmpty();
	void insertToPieceList(PieceList* pl);
	void incrementState();
	void resetState();

	// Funções do board:
	void nextPosition();
	void lastPosition();
	void lastPositionRecursive();
	bool checkIfPieceFitsOnBoard();
	bool hasNextRotation();
	void rotate(bool mounted = false);
	string lastPieceToString();

	// Funções de verdade:
	void insertPiece();
	void checkForRetrieve();
	bool checkIfEnds();

    // Armazena todas as peças:
    vector<int> queue;

    vector<PieceList*> pieceList;
    vector<SolverHeap*> solverHeap;
	unsigned row = 0;
	unsigned col = 0;
	unsigned mainState = 0;
};

#endif // INSTANCESOLVER_H
