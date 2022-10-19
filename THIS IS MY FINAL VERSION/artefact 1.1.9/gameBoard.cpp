#include "gameBoard.h"
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

gameBoard::gameBoard()
{
	activeGamePiece = new gamePiece;

	activeArea = new int* [9];
	for (int i = 0; i < 9; i++)
	{
		activeArea[i] = new int[9];
	}

	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			activeArea[i][j] = 0;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gameBoard::printBoard()
{
	string printable;
	string* printablePointer = &printable;
	cout << "______________________________________________________________________________" << endl;
	for (int i = 0; i <= 7; i++)
	{
		cout << "|          |          |          |          |          |          |          |" << endl;
		for (int l = 0; l <= 2; l++)
		{
			for (int j = 1; j <= 7; j++)
			{
				switch (activeArea[i][j])
				{
				case 0:
					printablePointer[0] = "|  \033[0;37m      \033[0m  |";
					break;
				case 1:
					printablePointer[0] = "|  \033[34;44mXXXXXX\033[0m  |";
					break;
				case 2:
					printablePointer[0] = "|  \033[31;41m000000\033[0m  |";
					break;
				}

				if (j != 1)
				{
					printablePointer[0].erase(0, 1);
				}

				cout << printablePointer[0];

			}
			cout << endl;
		}
		cout << "|__________|__________|__________|__________|__________|__________|__________|" << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int gameBoard::checkSquare(int y, int x)
{
	if (((activeGamePiece->y) + y > 9) || ((activeGamePiece->y) + y < 1) || ((activeGamePiece->x) + x > 8) || ((activeGamePiece->x) + x < 1))
	{
		return false;
	}
	else
	{
		if (activeArea[(activeGamePiece->y) + y][(activeGamePiece->x) + x] != activeGamePiece->Team)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int gameBoard::checkAllSquares(int y, int x)
{
	if (checkSquare((2 * y), (2 * x)) == true)
	{
		if (checkSquare((3 * y), (3 * x)) == true)
		{
			return true;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gameBoard::clearGameBoardPointers()
{
	for (int i = 0; i < 9; i++)
	{
		delete[] activeArea[i];
		activeArea[i] = NULL;
	}
	delete[] activeArea;
	activeArea = NULL;

	delete activeGamePiece;
	activeGamePiece = NULL;
}