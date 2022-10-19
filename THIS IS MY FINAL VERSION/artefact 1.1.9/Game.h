#pragma once
#include "gameBoard.h"
class Game
{
public:
	gameBoard* activeGameBoard;
	bool winCondition;
	bool* winConditionPointer;
	Game();
	void clearGamePointers();
	void playGame();
	void playConnect4();
};