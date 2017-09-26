#ifndef INSTANCEGENERATOR_H
#define INSTANCEGENERATOR_H

#include "board.h"
#include "paintboard.h"
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <fstream>
using std::string;
using std::to_string;
using std::ofstream;

class InstanceGenerator
{
public:
	InstanceGenerator(Board* b);
	InstanceGenerator(unsigned int rows, unsigned int cols, unsigned int numWalls);
    ~InstanceGenerator();
	PaintBoard* fillAll();

	void addWall();
    static long random_at_most(long max);
	int getBoardType(unsigned int row, unsigned int col);
	Board* getBoard();

    void generateInstance();
    void generateInstanceAux(unsigned row, unsigned col);
    void saveOnMemory(unsigned piece, unsigned rotation, unsigned row, unsigned col);
    string memoryToString();
	string memoryPiecesToString();
    void instanceToFile(string file);

private:
    PaintBoard* p;
    struct Memory
    {
        unsigned piece;
        unsigned rotation;
        unsigned row;
        unsigned col;
    };

    vector<Memory> memory;

    bool placeRandomPiece(unsigned int row, unsigned int col);
    bool placeRandomPieceFromCollection(unsigned int row, unsigned int col);
	bool fillAux(PaintBoard* aux, int lastType, int number, unsigned int row, unsigned int col);
    void fillWithWalls();
	Board* board;
};

#endif // INSTANCEGENERATOR_H
