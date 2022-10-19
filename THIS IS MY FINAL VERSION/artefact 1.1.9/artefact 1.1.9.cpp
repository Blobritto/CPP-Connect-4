#include <iostream>
#include <string>
using namespace std;

// BRING IN THE CLASSES
#include "Game.h"

// PLAYS THE GAME
int main()
{
	Game* game1;
	game1 = new Game;
	game1->playConnect4();

	game1->clearGamePointers();
	delete game1;
	game1 = NULL;
}