#ifndef INSTANCEREADER_H
#define INSTANCEREADER_H

#include "board.h"
#include <string>
#include <fstream>
#include <vector>
using std::string;
using std::ifstream;
using std::stoi;
using std::getline;
using std::istringstream;
using std::vector;

class InstanceReader
{
public:
    InstanceReader(string path);
	~InstanceReader();
    void parseLine(string line, unsigned &row, unsigned &col);
    void parseLineFirst(string line, unsigned &num);
    string piecesToString();
    Board* getBoard();
    int* getPieces();

private:
    Board* board;
	int* pieces;
};

#endif // INSTANCEREADER_H
