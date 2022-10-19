#pragma once
#include "gamePiece.h"
class gameBoard
{
public:
	int** activeArea;
	gamePiece* activeGamePiece;
	gameBoard();
	void printBoard();
	int checkSquare(int x, int y);
	int checkAllSquares(int x, int y);
	void clearGameBoardPointers();
};