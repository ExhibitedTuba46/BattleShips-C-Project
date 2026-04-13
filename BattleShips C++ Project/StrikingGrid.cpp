#include "StrikingGrid.h"
#include "PlacementGrid.h"
#include "Grid.h"
#include <iostream>
#include <windows.h>
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
			case 5:
				cout << "\033[33mX ";
				cout << "\033[0m";
				break;
			case 4:
				cout << "\033[33mO ";
				cout << "\033[0m";
				break;
			case 3:
				cout << "\033[33m+ ";
				cout << "\033[0m";
				break;
			case 2:
				cout << "\033[0mO ";
				break;
			case 1:
				cout << "\033[31mX ";
				cout << "\033[0m";
				break;
			default:
				cout << "\033[36m~ ";
				cout << "\033[0m";
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
}

void StrikingGrid::AIStrike(PlacementGrid gridToStrike, pair<int, int> chosenCell)
{
	grid[chosenCell.first][chosenCell.second] = gridToStrike.QueryHitInput(chosenCell.first, chosenCell.second);
	if (grid[chosenCell.first][chosenCell.second] != 1)
	{
		system("cls");
		cout << "You missed!" << endl;
		cout << endl;
	}
}

void StrikingGrid::QuerySrikeInput(PlacementGrid gridToStrike)
{
	int x = 0;
	int y = 0;

	bool hasStruck = false;

	bool isKeyPressed = false;

	cout << "Choose a place on the board to strike." << endl;
	cout << "Use the arrow keys to aim around the board. Press 'E' to strike." << endl;
	cout << endl;

	grid[x][y] = 3;
	while (hasStruck == false)
	{
		DisplayGrid();
		gridToStrike.DisplayGrid();
		//Whilst an input key has not yet been pressed
		while (isKeyPressed == false)
		{
			//If the down key is pressed
			if (GetKeyState(VK_DOWN) & 0x8000)
			{
				if (x < 9)
				{
					x++;
				}
				else
				{
					x = 0;
				}
				//An input key has been pressed
				isKeyPressed = true;
			}
			//If the up key is pressed
			else if (GetKeyState(VK_UP) & 0x8000)
			{
				if (x > 0)
				{
					x--;
				}
				else
				{
					x = 9;
				}
				isKeyPressed = true;
			}
			//If the right key is pressed
			else if (GetKeyState(VK_RIGHT) & 0x8000)
			{
				if (y < 9)
				{
					y++;
				}
				else
				{
					y = 0;
				}
				isKeyPressed = true;
			}
			//If the left key is pressed 
			else if (GetKeyState(VK_LEFT) & 0x8000)
			{
				if (y > 0)
				{
					y--;
				}
				else
				{
					y = 9;
				}
				isKeyPressed = true;
			}
			//If the E key is pressed
			else if (GetKeyState('E') & 0x8000)
			{
				if (grid[x][y] == 3)
				{
					grid[x][y] = gridToStrike.QueryHitInput(x, y);
					if (grid[x][y] != 1)
					{
						system("cls");
						cout << "You missed!" << endl;
						cout << endl;
					}
					isKeyPressed = true;
					hasStruck = true;
				}
			}
		}
		//After a key has been pressed
		while (isKeyPressed == true)
		{
			//Wait until none of the input keys are currently down
			//Each key is tested to ensure it is not -127 or -128, as testing for the key being down using GetKeyDown can return either of these values
			if ((GetKeyState(VK_DOWN) != -127 && GetKeyState(VK_DOWN) != -128) && (GetKeyState(VK_UP) != -127 && GetKeyState(VK_UP) != -128) &&
				(GetKeyState(VK_RIGHT) != -127 && GetKeyState(VK_RIGHT) != -128) && (GetKeyState(VK_LEFT) != -127 && GetKeyState(VK_LEFT) != -128) &&
				(GetKeyState('E') != -127 && GetKeyState('E') != -128))
			{
				isKeyPressed = false;
			}
		}
		for (int row = 0; row < 10; row++)
		{

			for (int cell = 0; cell < 10; cell++)
			{
				if (grid[row][cell] == 3)
				{
					grid[row][cell] = 0;
				}
				else if (grid[row][cell] == 4)
				{
					grid[row][cell] = 2;
				}
				else if (grid[row][cell] == 5)
				{
					grid[row][cell] = 1;
				}
			}
		}
		if (grid[x][y] < 1)
		{
			grid[x][y] = 3;
		}
		else if (grid[x][y] == 2)
		{
			grid[x][y] = 4;
		}
		else
		{
			grid[x][y] = 5;
		}

		if (hasStruck == false)
		{
			system("cls");
			cout << "Choose a place on the board to strike." << endl;
			cout << "Use the arrow keys to aim around the board. Press 'E' to strike." << endl;
			cout << endl;
		}
	}
}
