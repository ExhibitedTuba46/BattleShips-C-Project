#include "Grid.h"
#include <iostream>
using namespace std;

/// <summary>
/// Returns the value of the cell at the requested coordinates
/// </summary>
/// <param name="x">The X coordinate</param>
/// <param name="y">The Y coordinate</param>
/// <returns></returns>
int Grid::GetCell(int x, int y)
{
	return grid[x][y];
}

/// <summary>
/// Sets the value of the cell at the requested coordinates
/// </summary>
/// <param name="x">The X coordinate</param>
/// <param name="y">The Y coordinate</param>
/// <param name="value">The value the cell should be given</param>
void Grid::SetCell(int x, int y, int value)
{
	grid[x][y] = value;
}

/// <summary>
/// Abstract function to allow grid subclasses to use custom displays
/// </summary>
void Grid::DisplayGrid() 
{
}

/// <summary>
/// Display each cell on the grid's value without masking them
/// </summary>
void Grid::DisplayGridRaw()
{
	for (int row = 0; row < 10; row++)
	{
		cout << "  ";
		for (int cell = 0; cell < 10; cell++)
		{
			cout << grid[row][cell] << " ";
		}
		cout << endl;
	}
}

