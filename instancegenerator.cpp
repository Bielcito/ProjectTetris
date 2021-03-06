#include "instancegenerator.h"

InstanceGenerator::InstanceGenerator(unsigned int rows, unsigned int cols, unsigned int numWalls)
{
    this->board = new Board(rows, cols);
	for(unsigned int i = 0; i < numWalls; ++i)
	{
		this->addWall();
    }
}

InstanceGenerator::~InstanceGenerator()
{
    delete this->board;
}

InstanceGenerator::InstanceGenerator(Board* b)
{
    this->board = b;
}

void InstanceGenerator::addWall()
{
	int row, col;
	row = random_at_most(this->board->getRowSize()-1);
	col = random_at_most(this->board->getColSize()-1);
    this->board->insertWall(row, col);
}

long InstanceGenerator::random_at_most(long max)
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

int InstanceGenerator::getBoardType(unsigned int row, unsigned int col)
{
	if(this->board->getSpace(row, col)->isEmpty())
	{
		return 0;
	}
	else
	{
		if(this->board->getSpace(row, col)->isWall())
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
}

Board* InstanceGenerator::getBoard()
{
    return this->board;
}

void InstanceGenerator::generateInstance()
{
    int row = this->board->getRowSize();
    int col = this->board->getColSize();
	this->generateInstanceAux(row, col);
	this->fillWithWalls();
}

void InstanceGenerator::generateInstanceAux(unsigned row, unsigned col)
{
    for(unsigned  int i = 0; i < row; ++i)
    {
        for(unsigned int j = 0; j < col; ++j)
        {
            placeRandomPieceFromCollection(i, j);
        }
    }
}

void InstanceGenerator::saveOnMemory(unsigned piece, unsigned rotation, unsigned row, unsigned col)
{
    Memory aux =
    {
        piece, rotation, row, col
    };

    this->memory.push_back(aux);
}

string InstanceGenerator::memoryToString()
{
    string result = "";

    for(unsigned i = 0; i < this->memory.size(); ++i)
    {
		result += to_string(this->memory[i].piece) + " " + to_string(this->memory[i].rotation) + " " +
				to_string(this->memory[i].row) + " " + to_string(this->memory[i].col) + "\n";
    }

	return result;
}

std::string InstanceGenerator::memoryPiecesToString()
{
	string result = "";

	for(unsigned i = 0; i < this->memory.size(); ++i)
	{
		result += to_string(this->memory[i].piece) + "\n";
	}

	return result;
}

void InstanceGenerator::instanceToFile(string file)
{
    // Cria arquivo:
    ofstream outfile (file.c_str());

    outfile << to_string(this->board->getRowSize()) + " " + to_string(this->board->getColSize()) + "\n";
    outfile << endl;
    outfile << this->board->memoryWallToString();
    outfile << endl;
	outfile << this->memoryPiecesToString();
    outfile.close();
}

bool InstanceGenerator::placeRandomPiece(unsigned int row, unsigned int col)
{
    Piece* p = new Piece((Pieces)random_at_most(6));
    return this->board->mountPiece(p, row, col);
}

bool InstanceGenerator::placeRandomPieceFromCollection(unsigned int row, unsigned int col)
{
    int options[7] = {0, 1, 2, 3, 4, 5, 6};
    std::random_shuffle(std::begin(options), std::end(options));

    for(int i = 0; i < 7; ++i)
    {
		for(int j = 0; j < 4; j++)
		{
			Piece* p = new Piece((Pieces)options[i]);
			if(j == 1)
			{
				p->rotate90();
			}
			else if(j == 2)
			{
				p->rotate90();
				p->rotate90();
			}
			else if(j == 3)
			{
				p->rotate90();
				p->rotate90();
				p->rotate90();
			}

			if(this->board->mountPiece(p, row, col))
			{
				this->saveOnMemory(options[i], j, row, col);
				return true;
			}
		}
    }

    return false;
}

void InstanceGenerator::fillWithWalls()
{
    unsigned row = this->board->getRowSize();
    unsigned col = this->board->getColSize();

    for(unsigned int i = 0; i < row; ++i)
    {
        for(unsigned int j = 0; j < col; ++j)
        {
            this->board->insertWall(i, j);
        }
    }
}
