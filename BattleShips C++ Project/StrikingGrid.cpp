#include "StrikingGrid.h"
#include "Grid.h"
#include <iostream>
using namespace std;

void StrikingGrid::DisplayGrid()
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
			case 1:
				cout << "O ";
				break;
			case 2:
				cout << "X ";
				break;
			default:
				cout << "~ ";
				break;
			}
		}
		cout << endl;
	}
}
