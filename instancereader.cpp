#include "instancereader.h"

InstanceReader::InstanceReader(string path)
{
    ifstream file(path);
    string line;

    getline(file, line);

    // Inicializando campo:
    unsigned rowSize;
    unsigned colSize;
    parseLine(line, rowSize, colSize);
    this->board = new Board(rowSize, colSize);

    getline(file, line);

    // Colocando muros:
    while(getline(file, line))
    {
        unsigned row;
        unsigned col;

        if(line == "")
        {
            break;
        }
        else
        {
            parseLine(line, row, col);
            this->board->insertWall(row, col);
        }
    }

    // Pegando conjunto de peças:
    unsigned piece;

    while(getline(file, line))
    {
        parseLineFirst(line, piece);
        this->pieces[piece]++;
    }
}

void InstanceReader::parseLine(string line, unsigned &row, unsigned &col)
{
    string aux;
    unsigned j = 0;
    int number[2];

    for(unsigned i = 0; i < line.size(); ++i)
    {
        aux += line[i];

        if(line[i+1] == ' ' || i+1 == line.size())
        {
            number[j++] = stoi(aux);
            i++;
            aux = "";
        }
    }

    row = number[0];
    col = number[1];
}

void InstanceReader::parseLineFirst(string line, unsigned &num)
{
    string aux;
    for(unsigned i = 0; i < line.size(); ++i)
    {
        if(line[i] != ' ' && line[i] != '\n')
        {
            aux += line[i];
        }
        else
        {
            num = stoi(aux);
            return;
        }
    }
}

string InstanceReader::piecesToString()
{
    string result = "";

    for(unsigned i = 0; i < 7; i++)
    {
        result += to_string(this->pieces[i]) + " ";
    }

    result += "\n";

    return result;
}

Board* InstanceReader::getBoard()
{
    return this->board;
}

int* InstanceReader::getPieces()
{
    return this->pieces;
}
