#include "UI.h"
#include <iostream>

UI::UI() : commands({"BOARD_SIZE",
					 "PAWNS_NUMBER",
					 "IS_BOARD_CORRECT",
					 "IS_GAME_OVER",
					 "IS_BOARD_POSSIBLE",
					 "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT",
					 "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT",
					 "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT",
					 "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT"})
{
}

void UI::run()
{
	inputBoard();
	processingCurrentCommand();
}

void UI::inputBoard()
{
	std::string buffer;
	while (std::cin >> buffer)
	{
		if (commands.find(buffer) != commands.end())
		{
			currentCommand = buffer;
			gameBoard.setBoard(newBoard);
			processingCurrentCommand();
		}
		else
		{
			newBoard.push_back(buffer);
		}
	}
	newBoard.push_back(" ");
	gameBoard.setBoard(newBoard);
}

void UI::processingCurrentCommand()
{
	if (currentCommand == "BOARD_SIZE")
	{
		if (gameBoard.getBoardSize() != 0)
		{
			std::cout << gameBoard.getBoardSize() << std::endl
					  << std::endl;
		}
		newBoard.clear();
		currentCommand.clear();
	}
	if (currentCommand == "PAWNS_NUMBER")
	{
		std::cout << gameBoard.getPawnsNumber() << std::endl
				  << std::endl;
		newBoard.clear();
		currentCommand.clear();
	}
	if (currentCommand == "IS_BOARD_CORRECT")
	{
		// bool result = const_cast<Board &>(gameBoard).isBoardCorrect();
		bool result = gameBoard.isBoardCorrect();
		if (result)
		{
			std::cout << "YES" << std::endl
					  << std::endl;
		}
		else
		{
			std::cout << "NO" << std::endl
					  << std::endl;
		}
		newBoard.clear();
		currentCommand.clear();
	}
	if (currentCommand == "IS_GAME_OVER")
	{
		// int result = const_cast<Board &>(gameBoard).isGameOver();
		int result = gameBoard.isGameOver();
		if (result == 0)
		{
			std::cout << "NO" << std::endl
					  << std::endl;
		}
		else if (result == 1)
		{
			std::cout << "YES RED" << std::endl
					  << std::endl;
		}
		else if (result == 2)
		{
			std::cout << "YES BLUE" << std::endl
					  << std::endl;
		}
		newBoard.clear();
		currentCommand.clear();
	}

	if (currentCommand == "IS_BOARD_POSSIBLE")
	{
		bool result = gameBoard.isBoardPossible();
		if (result)
		{
			std::cout << "YES" << std::endl
					  << std::endl;
		}
		else
		{
			std::cout << "NO" << std::endl
					  << std::endl;
		}
		newBoard.clear();
		currentCommand.clear();
	}
	if (currentCommand == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
	{
		bool result = gameBoard.canWinInMove(true, true);
		if (result)
		{
			std::cout << "YES" << std::endl;
		}
		else
		{
			std::cout << "NO" << std::endl;
		}
		// currentCommand.clear();
	}
	if (currentCommand == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
	{
		bool result = gameBoard.canWinInMove(false, true);
		if (result)
		{
			std::cout << "YES" << std::endl;
		}
		else
		{
			std::cout << "NO" << std::endl;
		}
		// currentCommand.clear();
	}
	if (currentCommand == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT")
	{
		bool result = gameBoard.canWinInMove(true, false);
		if (result)
		{
			std::cout << "YES" << std::endl;
		}
		else
		{
			std::cout << "NO" << std::endl
					  << std::endl;
		}
		// currentCommand.clear();
	}
	if (currentCommand == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT")
	{
		bool result = gameBoard.canWinInMove(false, false);
		if (result)
		{
			std::cout << "YES" << std::endl
					  << std::endl;
		}
		else
		{
			std::cout << "NO" << std::endl
					  << std::endl;
		}
		newBoard.clear();
		currentCommand.clear();
	}
}
