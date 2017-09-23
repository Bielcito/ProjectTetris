#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include <string>
using std::string;

/** Essa classe será utilizada para ser usada no instance generator, e terá como função identificar quantas árvores de pontos
 * existem no tabuleiro.
 * @brief The PaintBoard class
 */
class PaintBoard
{
public:
	struct TypeIden
	{
		int type;
		int number;
	};

	PaintBoard(unsigned row, unsigned col);
	void paint(int type, int number, unsigned int row, unsigned int col);
	bool isPainted(unsigned int row, unsigned int col);
	int* getNumbers();
	string toString();

private:

	TypeIden** board;
	unsigned row;
	unsigned col;
	int numbers[3] = {};
};

#endif // PAINTBOARD_H
