#pragma once
#include <set>
#include "Board.h"

class UI
{
private:
	Board gameBoard;
	std::string currentCommand;
	std::set<std::string> commands;
	std::vector<std::string> newBoard;
	std::vector<std::string> readInputCanSomebodyWin();
	bool checkCanWinInMove();

public:
	UI(); // constructor
	void run();
	void inputBoard();
	void processingCurrentCommand();
};
