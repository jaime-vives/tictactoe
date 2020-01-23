// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#define BOARD_DIMENSIONS 3

/*
 * Basic Enums and Data Structures
 * ===============================================================================
 */
enum Player {
	PLAYER1 = 1,
	PLAYER2 = 2,
};

struct Move {
	int x;
	int y;
};

/*
 * Helper functions
 * ===============================================================================
 */

std::string enumToString(Player player)
{
	if (player == PLAYER1) {
		return "Player 1";
	}
	else if (player == PLAYER2) {
		return "Player 2";
	}
	else {
		return "";
	}
}

/*
 * Display the board
 * Input: board[][]
 * Output: None
*/
void drawBoard(int board[][BOARD_DIMENSIONS])
{
	for (int i = 0; i < BOARD_DIMENSIONS; i++) {
		for (int j = 0; j < BOARD_DIMENSIONS; j++) {
			std::cout << *(*(board + i) + j);
			if (j < BOARD_DIMENSIONS - 1) {
				std::cout << " | ";
			}
		}
		std::cout << "\n";
	}
}

/*
 * Determine if there is a winner based on the board config
 * Input: int board[][]
 * Output: bool
*/
bool isThereAWinner(int board[][BOARD_DIMENSIONS])
{
	// Check each row
	for (int i = 0; i < BOARD_DIMENSIONS; i++) {
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != 0) {
			return true;
		}
	}

	// Check each column
	for (int i = 0; i < BOARD_DIMENSIONS; i++) {
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i]!= 0) {
			return true;
		}
	}

	// Check Diagonals!
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0)
	{
		return true;
	}

	if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[0][2] != 0)
	{
		return true;
	}

	return false;
}

void updateBoard(Move move, int board[][BOARD_DIMENSIONS], Player player)
{
	board[move.x][move.y] = player;
}

Move requestMove(std::string name)
{
	Move move;
	std::cout << name << " select row (0-2): ";
	std::cin >> move.x;
	std::cout << name << " select col(0-2): ";
	std::cin >> move.y;
	return move;
}

bool isMoveValid(Move move, int board[][BOARD_DIMENSIONS])
{
	if (board[move.x][move.y] == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool takeTurn(Player player, int board[][BOARD_DIMENSIONS])
{
	Move move = requestMove(enumToString(player));
	if (isMoveValid(move,board) == true) {
		updateBoard(move, board, player);
	}
	else {
		while (isMoveValid(move,board) != true) {
			std::cout << "Move is invalid, try again!" << "\n";
			move = requestMove(enumToString(player));
		}
		updateBoard(move, board, player);
	}
	
	return isThereAWinner(board);
}

void congratulateWinner(Player player)
{
	std::cout << "Congratulations " << enumToString(player) << ", you won!\n";
}


/*
 * MAIN
 * ===============================================================================
 */
int main() {

	// Game loop end condition
	bool someoneWon = false;

	// Game Board
	int board[BOARD_DIMENSIONS][BOARD_DIMENSIONS] = { };

	// Main Game Loop
	while (!someoneWon) {

		drawBoard(board);

		// Ask Player 1 to make a move
		someoneWon = takeTurn(PLAYER1, board);
		if (someoneWon) {
			congratulateWinner(PLAYER1);
			break;
		}

		drawBoard(board);

		// Ask Player 2 to make a move
		someoneWon = takeTurn(PLAYER2, board);
		if (someoneWon) {
			congratulateWinner(PLAYER2);
			break;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
