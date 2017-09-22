#ifndef PAINTBOARD_H
#define PAINTBOARD_H


class PaintBoard
{
public:
	PaintBoard(unsigned int row, unsigned int col);

private:
	int** board;
	Dicionary* dicionary;

	struct Dicionary
	{
		int type;
		int valor;
	};
};

#endif // PAINTBOARD_H
