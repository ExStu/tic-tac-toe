#include <iostream>
#include <vector>

enum class PlayerTurn {
	X,
	O
};

void print_board(const std::vector<std::vector<char>>& board, const int boardSize) {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

char getPlayerSymbol(const PlayerTurn turn) {
	return turn == PlayerTurn::X ? 'X' : 'O';
}

void player_turn(const PlayerTurn turn, std::vector<std::vector<char>> &board, const int boardSize) {
	int cords[2];
	std::cout << "Player " << getPlayerSymbol(turn) << " turn" << std::endl;
	while (true) {
		std::cout << "Enter X coordinate: ";
		std::cin >> cords[0];
		std::cout << "Enter Y coordinate: ";
		std::cin >> cords[1];

		if (cords[0] >= 0 &&
			cords[0] < boardSize &&
			cords[1] >= 0 &&
			cords[1] < boardSize &&
			board[cords[0]][cords[1]] == '*') {
			board[cords[0]][cords[1]] = getPlayerSymbol(turn);
			break;
		}
		std::cout << "Invalid coordinates or cell in use" << std::endl;
	}
}

bool check_vertical(const std::vector<std::vector<char>>& board, const int position, const int boardSize) {
	const char firstFound = board[0][position];
	for (int i = 0; i < boardSize; i++) {
		if (board[i][position] != firstFound || board[i][position] == '*') {
			return false;
		}
	}
	return true;
}

bool check_horizontal(const std::vector<std::vector<char>>& board, const int position, const int boardSize) {
	const char firstFound = board[position][0];
	for (int i = 0; i < boardSize; i++) {
		if (board[position][i] != firstFound || board[position][i] == '*') {
			return false;
		}
	}
	return true;
}

bool check_main_diagonal(const std::vector<std::vector<char>>& board, const int boardSize) {
	for (int i = 0; i < boardSize; i++) {
		if (board[i][i] != board[0][0] || board[i][i] == '*') {
			return false;
		}
	}
	return true;
}

bool check_anti_diagonal(const std::vector<std::vector<char>>& board, const int boardSize) {
	for (int i = 0; i < boardSize; i++) {
		if (board[i][boardSize - 1 - i] != board[boardSize - 1][0] || board[i][boardSize - 1 - i] == '*') {
			return false;
		}
	}
	return true;
}

bool check_for_win(const std::vector<std::vector<char>>& board, const int boardSize) {
	for (int i = 0; i < boardSize; i++) {
		if (check_vertical(board, i, boardSize) ||
			check_horizontal(board, i, boardSize) ||
			check_main_diagonal(board, boardSize) ||
			check_anti_diagonal(board, boardSize)) {
			return true;
		}
	}
	return false;
}

int main() {
	int boardSize;
	std::cout << "Enter board size (>=3): ";
	std::cin >> boardSize;

	while (boardSize < 3) {
		std::cout << "Minimum board size is 3" << std::endl;
		std::cout << "Enter board size (>=3): ";
		std::cin >> boardSize;
	}

	bool gameOver = false;
	PlayerTurn turn = PlayerTurn::X;
	int count = 0;
	std::vector board(boardSize, std::vector(boardSize, '*'));

	print_board(board, boardSize);
	while (!gameOver) {
		player_turn(turn, board, boardSize);
		if (check_for_win(board, boardSize)) {
			print_board(board, boardSize);
			std::cout << "Player " << getPlayerSymbol(turn) << " wins" << std::endl;
			break;
		}
		if (turn == PlayerTurn::X) {
			turn = PlayerTurn::O;
		} else {
			turn = PlayerTurn::X;
		}
		count++;
		print_board(board, boardSize);

		if (count == boardSize * boardSize) {
			std::cout << "Game over, draw" << std::endl;
			gameOver = true;
		}
	}
}
