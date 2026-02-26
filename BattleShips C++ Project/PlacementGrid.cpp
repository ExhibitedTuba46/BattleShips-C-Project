#include "PlacementGrid.h"
#include "Grid.h"
#include <iostream>
using namespace std;

int PlacementGrid::DisplayCellPlacement(int x, int y) 
{
	if (grid[x][y] != 1)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

void PlacementGrid::PlaceBattleShip(int x, int y)
{
	if (grid[x][y] != 1)
	{
		grid[x][y] = 2;
	}
	else
	{
		grid[x][y] = 3;
	}
	if (grid[x][y - 1] != 1)
	{
		grid[x][y - 1] = 2;
	}
	else
	{
		grid[x][y - 1] = 3;
	}
	if (grid[x][y + 1] != 1)
	{
		grid[x][y + 1] = 2;
	}
	else
	{
		grid[x][y + 1] = 3;
	}
}

void PlacementGrid::DisplayGrid()
{
	char rowLetter[10] = { 'A', 'B', 'C', 'D','E', 'F', 'G', 'H', 'I', 'J' };
	cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
	for (int row = 0; row < 10; row++)
	{
		cout << rowLetter[row] << " ";
		for (int cell = 0; cell < 10; cell++)
		{
			switch (grid[row][cell])
			{
			case 3:
				cout << "X ";
				break;
			case 2:
				cout << "O ";
				break;
			case 1:
				cout << "# ";
				break;
			default:
				cout << "~ ";
				break;
			}
		}
		cout << endl;
	}
}