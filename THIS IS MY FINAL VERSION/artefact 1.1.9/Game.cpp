#include "Game.h"
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Game::Game()
{
	winConditionPointer = &winCondition;
	*winConditionPointer = false;
	activeGameBoard = new gameBoard;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Game::clearGamePointers()
{
	activeGameBoard->clearGameBoardPointers();
	delete activeGameBoard;
	activeGameBoard = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::playGame()
{
	// DYNAMICALLY STORED ARRAYS ARE CREATED TO MAKE CODE FOR EFFICIENT FOR STORING DIRECTIONS AND BOOLEAN VALUES
	int** placesToGo = new int* [7];
	for (int i = 0; i < 7; i++)
	{
		placesToGo[i] = new int[2];
	}

	for (int i = 0; i < 1; i++)
	{
		// TEMPORARY ARRAY IS CREATED IN ORDER TO EFFICIENTLY POPULATE THE PLACESTOGO, IT IS DELETED ALMOST IMMEDIATELY AS ITS SCOPE IS MINIMAL, AND ONLY SERVES THE PURPOSE OF POPULATING THE PLACESTOGO
		int tempArray[7][2] = { {-1, -1}, {1, 1}, {0, -1}, {0, 1}, {-1, 1}, {1, -1}, {1, 0} };
		for (int l = 0; l <= 6; l++)
		{
			for (int j = 0; j <= 1; j++)
			{
				placesToGo[l][j] = tempArray[l][j];
			}
		}
	}

	activeGameBoard->printBoard();

	while (*winConditionPointer != true)
	{
		int* theBooleans = new int[7];
		for (int i = 0; i < 7; i++)
		{
			theBooleans[i] = 0;
		}

		if (activeGameBoard->activeGamePiece->Team == 2)
		{
			activeGameBoard->activeGamePiece->Team = 1;
		}
		else
		{
			activeGameBoard->activeGamePiece->Team = 2;
		}

		// INITIALISES THE PLAYERS CHOICE OF COLUMN
		int playerChoice;
		int* playerChoicePointer = &playerChoice;

		// VALIDATES THAT I DON'T EXCEED THE VERTICAL HEIGHT OF THE GAME BOARD
		bool validSpace = false;
		bool* validSpacePointer = &validSpace;

		while (*validSpacePointer != true)
		{
			// CHECKS TO MAKE SURE THE CHOSEN COLUMN IS WITHIN THE GAME BOARD BOUNDARIES, WILL FORCE YOU TO PICK AGAIN IF IT IS NOT
			bool validColumn = false;
			bool* validColumnPointer = &validColumn;

			while (*validColumnPointer != true)
			{
				cout << "Player " << activeGameBoard->activeGamePiece->Team << ", where do you want to place your counter, please enter a column from 1-7. ";
				cin >> *playerChoicePointer;
				cin.clear();
				cin.ignore();
				if (*playerChoicePointer < 1 || *playerChoicePointer > 7 || (typeid(*playerChoicePointer) != typeid(int)))
				{
					cout << "That is not a valid column, please pick again." << endl;
				}
				else
				{
					*validColumnPointer = true;
				}
			}
			// DECRAMENTS, CHECKING FROM THE BOTTOM UPWARDS TO FIND THE LOWEST AVAILABLE SPACE FOR A COUNTER TO BE PLACES WITHIN A COLUMN
			// ISPLACEABLE MAKES SURE THAT A 0 OCCUPIES THE SPACE, AND ISVALID MAKES SURE IT IS WITHIN BOUNDARIES
			bool isPlaceable = false;
			bool* isPlaceablePointer = &isPlaceable;

			int i = 7;
			int* iPointer = &i;

			while (*isPlaceablePointer != true)
			{
				// IF THE COLUMN IS FULL, THE PLAYER WILL HAVE TO PICK AGAIN, AND THE GAME BOARD IS NOT OUTPUTTED, AS THEY FILL DIFFERENT CONDITIONS
				// ONLY IF THE SPACE IS TRULY VALID WILL THE BOARD BE PRINTED OUT
				if (*iPointer < 0)
				{
					cout << "This column is full, please pick another." << endl;
					*validSpacePointer = false;
					*isPlaceablePointer = true;
					*iPointer = 7;
				}
				else
				{
					if (activeGameBoard->activeArea[*iPointer][*playerChoicePointer] == 0)
					{
						*isPlaceablePointer = true;
						activeGameBoard->activeArea[*iPointer][*playerChoicePointer] = activeGameBoard->activeGamePiece->Team;
						activeGameBoard->activeGamePiece->x = (*playerChoicePointer);
						activeGameBoard->activeGamePiece->y = *iPointer;
						*validSpacePointer = true;
					}
					else
					{
						*iPointer = *iPointer - 1;
					}
				}
			}
		}
		// THIS LINE CLEARS THE OUTPUT WINDOW BEFORE PRINTING THE NEW ONE
		system("CLS");
		activeGameBoard->printBoard();

		// CHECKS THE DIRECT CONTACT SQUARES TO RECORD MATCHING PIECES
		for (int i = 0; i <= 6; i++)
		{
			theBooleans[i] = activeGameBoard->checkSquare(placesToGo[i][0], placesToGo[i][1]);
		}
		
		// IF THE PLACED COUNTER EXISTS WITHIN THE MIDDLE OF TWO OTHERS ON THEIR TEAM, THE NEXT COUNTER OUTWARDS ON EACH SIDE WILL BE CHECKED, IF EITHER IS POSITIVE, THE WIN CONDITION HAS BEEN MET
		for (int i = 0; i <= 4; i = i + 2)
		{
			if (theBooleans[i] == true && theBooleans[i + 1] == true && *winConditionPointer == false)
			{
				if ((activeGameBoard->checkSquare((2 * placesToGo[i][0]), (2 * placesToGo[i][1])) == true) || (activeGameBoard->checkSquare((2 * placesToGo[i + 1][0]), (2 * placesToGo[i + 1][1])) == true))
				{
					*winConditionPointer = true;
				}
			}
		}
		
		// FOR ALL OF THE ORIGINAL 7 THAT WERE POSITIVE, THIS EXTENDS FURTHER OUT UNTIL EITHER THE LINE ENDS OR THE WIN CONDITION IS MET
		for (int i = 0; i <= 6; i++)
		{
			if (theBooleans[i] == true && *winConditionPointer != true)
			{
				*winConditionPointer = activeGameBoard->checkAllSquares(placesToGo[i][0], placesToGo[i][1]);
			}
		}
		
		// CLEARS THE BOOLEAN LIST FOR REUSE
		delete[] theBooleans;
		theBooleans = NULL;
	}
	
	// PLAYS AT THE END OF THE GAME
	cout << "Player " << activeGameBoard->activeGamePiece->Team << " wins the game, congratulations!" << endl;

	*winConditionPointer = false;
	activeGameBoard->activeGamePiece->Team = 2;

	// RESETS THE ACTIVE AREA
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			activeGameBoard->activeArea[i][j] = 0;
		}
	}

	// CLEARS THE PLACES TO GO
	for (int i = 0; i < 7; i++)
	{
		delete[] placesToGo[i];
		placesToGo[i] = NULL;
	}
	delete[] placesToGo;
	placesToGo = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::playConnect4()
{
	int play;
	bool playing = true;

	while (playing == true)
	{
		cout << "Do you want to play Connect 4? 0 = NO; 1 = YES:  ";
		cin >> play;
		if (play == 1)
		{
			system("CLS");
			playGame();
			playing = true;
		}
		else if (play == 0)
		{
			playing = false;
		}
		else
		{
			cout << "That was not a valid answer. " << endl;
			playing = true;
		}
	}
}