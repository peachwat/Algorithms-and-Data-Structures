#pragma once
#include <string>
#include <vector>

struct Cell
{
	std::string color;
	bool visited;
};

class Board
{
private:
	std::vector<std::string> board;
	int redPawns = 0;
	int bluePawns = 0;
	bool redTurn = false;
	Cell boardData[11][11];
	int size;
	int calculateSize();
	bool isVictoryDFS(const std::string &color, int row, int col);
	bool isRedVictoryDFS(int row, int col);
	bool isBlueVictoryDFS(int row, int col);
	void clearVisited();
	int countEmptyCells();
	void determineTurn();
	bool canWinInOneMove(const std::string &color);
	bool canWinInTwoMoves(const std::string &color);

public:
	void setBoard(const std::vector<std::string> &board);
	int getBoardSize() const;
	int getPawnsNumber() const;
	bool isBoardCorrect();
	int isGameOver();
	bool isBoardPossible();
	bool canWinInMove(bool isRed, bool inOneMove);
};
