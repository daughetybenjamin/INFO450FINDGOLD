#include <iostream>
#include <time.h>
using namespace std;

const int ROW = 8;
const int COLUMN = 8;

void initializeBoard(int *goldX, int *goldY, int &bombX, int &bombY);
void displayBoard(char board[ROW][COLUMN]);
void makeDashedBoard(char gameBoard[ROW][COLUMN]);
void prepRealBoard(int *goldX, int *goldY, int &bombX, int &bombY, char gameBoard[ROW][COLUMN]);
void makeGuess(int &input2, int &input1);
void checkGuess(int *goldX, int *goldY, int &bombX, int &bombY, int &input2, int &input1, bool *goldFound, bool &bombFound, int &attemptsLeft, int &points, char gameBoard[ROW][COLUMN]);

int main()
{
	char gameBoard[ROW][COLUMN];
	char newGame = 'y';
	char blankBoard[ROW][COLUMN];
	int iRow, iCol;
	int goldX[5], goldY[5], bombX, bombY; // coordinates for rewards/bomb in board
	int attemptsLeft;
	int input2, input1;
	bool goldFound[5];
	bool bombFound;
	int points;

	for (iRow = 0; iRow < ROW; iRow++) // This loop fills the blank board with ? marks.
	{
		for (iCol = 0; iCol < COLUMN; iCol++) // This board will be shown to the user at the start.
		{
			blankBoard[iRow][iCol] = '?';
		}
	}

	do // This loop is the game itself, repeating when the player chooses to start a new game.
	{
		cout << "In this game, you have five attempts to search for up to five hidden pieces of gold in the board below." << endl;
		cout << "There is one bomb hidden in the board that will end the game instantly when uncovered." << endl;
		cout << "If you find a piece of gold, you will be awarded with an extra attempt." << endl;
		cout << "To make a guess, enter the horizontal x-coordinate, hit enter, and do the same with the vertical y-coordinate." << endl;

		displayBoard(blankBoard); // These four functions will display a board full of question marks,
		initializeBoard(goldX, goldY, bombX, bombY); // then randomize locations for gold and the bomb,
		makeDashedBoard(gameBoard); // create a full board of - characters,
		prepRealBoard(goldX, goldY, bombX, bombY, gameBoard); // and finally place gold and bomb locations in that board.
		bombFound = false; // These three lines will initialize variables in the case of the player saying "yes" to a new game
		attemptsLeft = 5;
		points = 0;

		for (iRow = 0; iRow < 5; iRow++)
		{
			goldFound[iRow] = false; // Initialize "gold found?" to false
		}

		do // This loop will run as many times as there are guesses,
		{ // for a base of 5 that's increased by 1 each time the player finds the gold.
			makeGuess(input2, input1); // It has the player make a guess, checks the guess for gold or a bomb,
			checkGuess(goldX, goldY, bombX, bombY, input2, input1, goldFound, bombFound, attemptsLeft, points, gameBoard);
			if (bombFound) // subtracts an attempt, and lists the amount of points and attempts remaining.
			{
				cout << "You've uncovered a bomb! Game over." << endl;
				break;
			}

			attemptsLeft--;
			cout << "You currently have " << points << " points and " << attemptsLeft << " attempts remaining." << endl;
		} while (attemptsLeft > 0);

		cout << "The board is shown here:" << endl;
		displayBoard(gameBoard);
		cout << "Your final point total is " << points << "." << endl;
		cout << "Do you want to start a new game? The console will be cleared to make room for the new board. Type y to do so: ";
		cin >> newGame;
		system("cls"); // Clears the console to make room for the new game.
	} while (newGame == 'y' || newGame == 'Y');

	system("pause");
	return 0;
}

void initializeBoard(int *goldX, int *goldY, int &bombX, int &bombY) // This function generates the contents of the board.
{
	int i;
	srand(time(NULL));
	for (i = 0; i < 5; i++)
	{
		goldX[i] = (rand() % ROW); // First, x values are generated for the locations of the gold.
	}

	for (i = 0; i < 5; i++)
	{
		goldY[i] = (rand() % ROW); // Then, y values are generated.
	}

	bombX = (rand() % ROW); // An x and y value are generated for the one bomb.
	bombY = (rand() % ROW);
}

void displayBoard(char board[ROW][COLUMN]) // This function displays the board when the game starts or ends.
{
	int iRow, iCol;
	cout << "    1 2 3 4 5 6 7 8\n   -----------------" << endl; // Creates a horizontal scale to provide coordinates for the user.
	for (iRow = 0; iRow < ROW; iRow++)
	{
		cout << iRow + 1 << " | "; // This and the below cout statement create a vertical scale and print the actual contents of the grid.
		for (iCol = 0; iCol < COLUMN; iCol++)
		{
			cout << board[iRow][iCol] << " ";
		}
		cout << endl;
	}
}

void makeDashedBoard(char gameBoard[ROW][COLUMN]) // This function creates a dummy board full of - marks, to be filled as the game progresses
{ // and displayed when the game ends.
	int iRow, iCol;
	for (iRow = 0; iRow < ROW; iRow++) // This function fills the blank board with ? marks.
	{
		for (iCol = 0; iCol < COLUMN; iCol++) // The board will be shown to the user at the start.
		{
			gameBoard[iRow][iCol] = '-';
		}
	}
}

void makeGuess(int &input2, int &input1)
{
	cout << "Enter an x coordinate: "; // This function prompts the user for their guess
	cin >> input1; // and records it in the corresponding input variables.
	cout << "Enter a y coordinate: ";
	cin >> input2;
}

void checkGuess(int *goldX, int *goldY, int &bombX, int &bombY, int &input2, int &input1, bool *goldFound, bool &bombFound, int &attemptsLeft, int &points, char gameBoard[ROW][COLUMN])
{
	int i; // This function checks whether the player guessed the location of gold or a bomb.
	if (gameBoard[input2 - 1][input1 - 1] == 'G')
	{
		cout << "You've struck gold! This gives you a point and an extra attempt." << endl << endl;
		points++; // If they find gold, the player gets a point and an extra attempt, and the 'G' is changed to 'F.'
		attemptsLeft++;
		gameBoard[input2 - 1][input1 - 1] = 'F';
		return;
	}

	if (gameBoard[input2 - 1][input1 - 1] == 'B')
	{
		bombFound = true; // If they find a bomb, the game-loop is broken, ending the game.
		return;
	}

	cout << "There was nothing in this spot..." << endl << endl; // If they find nothing, game continues.
}

void prepRealBoard(int *goldX, int *goldY, int &bombX, int &bombY, char gameBoard[ROW][COLUMN])
{
	int i; // This function prepares the board that will be shown at the end of the game.
	for (i = 0; i < 5; i++)
	{
		gameBoard[goldY[i]][goldX[i]] = 'G'; // It places 'G' where gold is,
	}

	gameBoard[bombY][bombX] = 'B'; // and 'B' where the bomb is.
}