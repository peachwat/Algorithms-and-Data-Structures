#include "board.h"
#include <iostream>
#include <cctype>

int Board::calculateSize()
{
	bool start = false;
	int size = 1;
	for (const auto &line : board)
	{
		if (line == "<")
		{
			start = true;
		}
		if (start && line == ">-<")
		{
			size++;
		}
		if (line == ">")
		{
			start = false;
			break;
		}
	}
	return size;
}

bool Board::isVictoryDFS(const std::string &color, int row, int col)
{
	if (color == "r")
	{
		return isRedVictoryDFS(row, col);
	}
	if (color == "b")
	{
		return isBlueVictoryDFS(row, col);
	}
	return false;
}

bool Board::isRedVictoryDFS(int row, int col)
{
	if (row < 0 || col < 0 || row >= size || col >= size || boardData[row][col].color != "r" || boardData[row][col].visited)
	{
		return false;
	}

	boardData[row][col].visited = true;

	if (col == size - 1)
	{
		return true;
	}

	if (isRedVictoryDFS(row + 1, col + 1) || isRedVictoryDFS(row + 1, col) || isRedVictoryDFS(row, col + 1) ||
		isRedVictoryDFS(row, col - 1) || isRedVictoryDFS(row - 1, col) || isRedVictoryDFS(row - 1, col - 1))
	{
		return true;
	}

	return false;
}

bool Board::isBlueVictoryDFS(int row, int col) // row - wiersz col - kolumna
{
	if (row < 0 || col < 0 || row >= size || col >= size || boardData[row][col].color != "b" || boardData[row][col].visited)
	{
		return false;
	}

	boardData[row][col].visited = true;

	if (row == size - 1)
	{
		return true;
	}

	if (isBlueVictoryDFS(row + 1, col + 1) || isBlueVictoryDFS(row + 1, col) || isBlueVictoryDFS(row, col + 1) ||
		isBlueVictoryDFS(row, col - 1) || isBlueVictoryDFS(row - 1, col) || isBlueVictoryDFS(row - 1, col - 1))
	{
		return true;
	}

	return false;
}

void Board::setBoard(const std::vector<std::string> &newBoard)
{
	this->board = newBoard;
	this->size = calculateSize();
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{

			while (index < board.size() && board.at(index).find('<') == std::string::npos)
			{
				index++;
			}

			if (index + 1 < board.size() && std::isalpha(board.at(index + 1)[0]))
			{
				boardData[i - j][j].color = board.at(index + 1);
			}
			else
			{
				boardData[i - j][j].color = " ";
			}
			index++;
		}
	}

	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < size - i; j++)
		{
			while (index < board.size() && board.at(index).find('<') == std::string::npos)
			{
				index++;
			}
			if (index + 1 < board.size() && std::isalpha(board.at(index + 1)[0]))
			{
				boardData[size - j - 1][i + j].color = board.at(index + 1);
			}
			else
			{
				boardData[size - j - 1][i + j].color = " ";
			}
			index++;
		}
	}
	// for (int i = 0; i < size; i++)
	// {
	// 	for (int j = 0; j < size; j++)
	// 	{
	// 		std::cout << boardData[i][j].color << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
}

void Board::clearVisited()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			boardData[i][j].visited = false;
		}
	}
}

int Board::isGameOver()
{
	clearVisited();
	if (!isBoardCorrect())
	{
		return 0;
	}

	for (int i = 0; i < size; ++i)
	{
		if (boardData[i][0].color == "r")
		{

			if (isVictoryDFS("r", i, 0))
			{
				return 1;
			}
		}
	}
	for (int i = 0; i < size; ++i)
	{
		if (boardData[0][i].color == "b")
		{

			if (isVictoryDFS("b", 0, i))
			{
				return 2;
			}
		}
	}
	return 0;
}

bool Board::isBoardPossible()
{
	clearVisited();
	if (!isBoardCorrect())
	{
		return false;
	}

	if (isGameOver() == 1)
	{ // red wins
		if (redPawns - 1 != bluePawns)
		{
			return false;
		}
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (boardData[i][j].color == "r")
				{
					boardData[i][j].color = " ";
					if (isGameOver() != 1)
					{
						boardData[i][j].color = "r";
						return true;
					}
					boardData[i][j].color = "r";
				}
			}
		}
		return false;
	}
	if (isGameOver() == 2)
	{ // blue wins
		if (redPawns != bluePawns)
		{
			return false;
		}
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (boardData[i][j].color == "b")
				{
					boardData[i][j].color = " ";
					if (isGameOver() != 2)
					{
						boardData[i][j].color = "b";
						return true;
					}
					boardData[i][j].color = "b";
				}
			}
		}
		return false;
	}
	return true;
}

bool Board::canWinInOneMove(const std::string &color)
{
	int isGameOverValue;
	if (color == "r")
	{
		isGameOverValue = 1;
	}
	else
	{
		isGameOverValue = 2;
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (boardData[i][j].color == " ")
			{
				boardData[i][j].color = color;
				if (isGameOver() == isGameOverValue)
				{
					boardData[i][j].color = " ";
					return true;
				}
				boardData[i][j].color = " ";
			}
		}
	}
	return false;
}

bool Board::canWinInTwoMoves(const std::string &color)
{
	int isGameOverValue;
	if (color == "r")
	{
		isGameOverValue = 1;
	}
	else
	{
		isGameOverValue = 2;
	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (boardData[i][j].color == " ")
			{
				boardData[i][j].color = color;
				if (isGameOver() != isGameOverValue)
				{
					for (int k = 0; k < size; ++k)
					{
						for (int l = 0; l < size; ++l)
						{
							if (boardData[k][l].color == " ")
							{
								boardData[k][l].color = color;
								if (isGameOver() == isGameOverValue)
								{
									boardData[k][l].color = " ";
									boardData[i][j].color = " ";
									return true;
								}
								boardData[k][l].color = " ";
							}
						}
					}
				}

				boardData[i][j].color = " ";
			}
		}
	}
	return false;
}

int Board::countEmptyCells()
{
	int count = 0;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (boardData[i][j].color != "r" && boardData[i][j].color != "b")
			{
				++count;
			}
		}
	}
	return count;
}

void Board::determineTurn()
{
	if (redPawns == bluePawns)
	{
		redTurn = true;
	}
	else if (redPawns - 1 == bluePawns)
	{
		redTurn = false;
	}
}

bool Board::canWinInMove(bool isRed, bool inOneMove)
{
	determineTurn();
	int neededMoves = 0;
	clearVisited();

	if (!isBoardPossible())
	{
		return false;
	}

	if (isGameOver() == 1 || isGameOver() == 2)
	{
		return false;
	}

	if ((redTurn && !isRed && inOneMove) || (!redTurn && isRed && inOneMove))
	{
		neededMoves = 2;
	}
	else if ((redTurn && !isRed && !inOneMove) || (!redTurn && isRed && !inOneMove))
	{
		neededMoves = 4;
	}
	else if ((redTurn && isRed && inOneMove) || (!redTurn && !isRed && inOneMove))
	{
		neededMoves = 1;
	}
	else if ((redTurn && isRed && !inOneMove) || (!redTurn && !isRed && !inOneMove))
	{
		neededMoves = 3;
	}

	if (neededMoves > countEmptyCells())
	{
		return false;
	}

	if (isRed && inOneMove)
	{
		if (canWinInOneMove("r"))
		{
			return true;
		}
	}

	if (!isRed && inOneMove)
	{
		if (canWinInOneMove("b"))
		{
			return true;
		}
	}
	if (isRed && !inOneMove)
	{
		if (canWinInTwoMoves("r"))
		{
			return true;
		}
	}
	if (!isRed && !inOneMove)
	{
		if (canWinInTwoMoves("b"))
		{
			return true;
		}
	}

	return false;
}

int Board::getBoardSize() const
{
	return size;
}

int Board::getPawnsNumber() const
{
	int pawns = 0;
	for (const auto &line : board)
	{
		if (line.find('r') != std::string::npos || line.find('b') != std::string::npos)
		{
			pawns++;
		}
	}
	return pawns;
}

bool Board::isBoardCorrect()
{
	redPawns = 0;
	bluePawns = 0;

	for (const auto &line : board)
	{
		for (const auto &ch : line)
		{
			if (ch == 'r')
			{
				redPawns++;
			}
			if (ch == 'b')
			{
				bluePawns++;
			}
		}
	}

	return (redPawns == bluePawns || redPawns - 1 == bluePawns);
}
