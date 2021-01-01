/*
* @Author: ayman
* @Date:   2018-01-19 16:51:10
* @Last Modified by:   ayman
* @Last Modified time: 2018-01-20 18:37:26
*/
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>

using namespace std;

class sudokuMap
{
private:
	int grid[9][9];
	int level;
	int solution[9][9];

public:
	sudokuMap(int l)
	{
		level = l;
		for (int x = 0; x < 9; ++x)
		{
			for (int y = 0; y < 9; ++y)
			{
				grid[x][y] = 0;
			}
		}
	}

	bool fillGrid()
	{
		int row, col;
		if (!findEmpty(row, col))
			return true;
		int values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		for (int itr = 0; itr < 9; ++itr)
		{
			int index = (rand() % (9 - itr)) + itr;
			int val = values[index];
			swap(values[index], values[itr]);
			if (!isInBox(row, col, val) && !isInRow(row, val) && !isInCol(col, val))
			{
				grid[row][col] = val;
				if (fillGrid())
					return true;
				grid[row][col] = 0;
			}
		}
		return false;
	}

	void hideSquares()
	{
		int mapRandNum;
		switch (level)
		{
		case 1:
			mapRandNum = (rand() % 3) + 44;
			break;
		case 2:
			mapRandNum = (rand() % 3) + 50;
			break;
		case 3:
			mapRandNum = (rand() % 3) + 55;
			break;
		case 4:
			mapRandNum = (rand() % 3) + 60;
			break;
		default:
			mapRandNum = (rand() % 3) + 44;
			break;
		}
		for (int sqr = 0; sqr < mapRandNum;)
		{
			int x = genRandPos();
			int y = genRandPos();

			if (grid[x][y] != 0)
			{
				grid[x][y] = 0;
				++sqr;
			}
		}
	}

	int genRandPos()
	{
		return rand() % 9;
	}

	int genRandVal()
	{
		return (rand() % 9) + 1;
	}

	bool findEmpty(int &row, int &col)
	{
		for (row = 0; row < 9; row++)
		{
			for (col = 0; col < 9; col++)
			{
				if (grid[row][col] == 0)
					return true;
			}
		}
		return false;
	}

	bool isInBox(int row, int col, int value)
	{
		int tempRow, tempCol;
		if (grid[row][col] == 0)
		{
			if (row >= 0 && row < 3)
				tempRow = 0;
			else if (row >= 3 && row < 6)
				tempRow = 3;
			else
				tempRow = 6;

			if (col >= 0 && col < 3)
				tempCol = 0;
			else if (col >= 3 && col < 6)
				tempCol = 3;
			else
				tempCol = 6;

			for (int x = tempRow; x < tempRow + 3; x++)
			{
				for (int y = tempCol; y < tempCol + 3; y++)
				{
					if (grid[x][y] == value)
						return true;
				}
			}
			return false;
		}
	}

	bool isInRow(int row, int value)
	{
		for (int y = 0; y < 9; y++)
		{
			if (grid[row][y] == value)
				return true;
		}
		return false;
	}

	bool isInCol(int col, int value)
	{
		for (int x = 0; x < 9; x++)
		{
			if (grid[x][col] == value)
				return true;
		}
		return false;
	}

	void printMap()
	{
		cout << endl;
		cout << "    1  2  3   4  5  6   7  8  9 \n";
		cout << "------------------------------------" << endl;
		for (int i = 0; i < 9; i++)
		{
			cout << i + 1 << "- ";
			for (int j = 0; j < 9; j++)
			{
				if (grid[i][j] != 0)
					cout << " " << grid[i][j] << " ";
				else
					cout << "   ";
				if ((j + 1) % 3 == 0 && j != 8)
					cout << "|";
			}
			cout << endl;
			if ((i + 1) % 3 == 0 && i != 8)
			{
				cout << "   ";
				cout << "------------------------------------";
			}
			cout << endl;
		}
	}

	void input()
	{
		int x, y, val;
		while (true)
		{
			cout << endl
				 << "To see solution enter 0" << endl;
			cout << endl
				 << "Enter Coordinates";
			cout << endl
				 << "x :";
			cin >> x;
			if (x == 0)
			{
				cout << endl
					 << "Solution :-" << endl;
				break;
			}
			--x;
			cout << endl
				 << "y :";
			cin >> y;
			if (y == 0)
			{
				cout << endl
					 << "Solution :-" << endl;
				break;
			}
			--y;
			cout << endl
				 << "Enter Value";
			cout << endl
				 << "Value :";
			cin >> val;
			if (val == 0)
			{
				cout << endl
					 << "Solution :-" << endl;
				break;
			}
			if (grid[x][y] == 0 && val < 10 && val > 0)
			{
				if (!isInBox(x, y, val) && !isInRow(x, val) && !isInCol(y, val))
				{
					grid[x][y] = val;
					printMap();
				}
				else
					cout << " Are you sure!!!,,, No can do.";
			}
			else
				cout << "Please, Enter a valid value.";
		}
		if (solve())
		{
			printMap();
		}
		else
			cout << "This Sudoku is Unsolvable!!" << endl;
	}

	bool solve()
	{
		int row, col;
		if (!findEmpty(row, col))
			return true;
		int values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		for (int itr = 0; itr < 9; ++itr)
		{
			int index = (rand() % (9 - itr)) + itr;
			int val = values[index];
			swap(values[index], values[itr]);
			if (!isInBox(row, col, val) && !isInRow(row, val) && !isInCol(col, val))
			{
				grid[row][col] = val;
				if (solve())
					return true;
				grid[row][col] = 0;
			}
		}
		return false;
	}
};

void swap(int *x, int *y)
{
	int temp = *y;
	*y = *x;
	*x = temp;
}

int main(int argc, char const *argv[])
{
	srand(time(0));
	sudokuMap sudMap = sudokuMap(2);
	sudMap.fillGrid();
	sudMap.hideSquares();
	sudMap.printMap();
	sudMap.input();
	return 0;
}