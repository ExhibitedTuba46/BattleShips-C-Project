//https://www.geeksforgeeks.org/cpp/how-to-detect-keypress-in-windows-using-cpp/

#include "PlacementGrid.h"
#include "Grid.h"
#include <iostream>
#include <windows.h>
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

/// <summary>
/// Query where the player wishes to place a BattleShip, and provide input to place one 
/// </summary>
void PlacementGrid::QueryBattleShipInput()
{
	//The default x and y coordinates on the placement grid
	//As every ship starts horizontally, this is offset 1 from the right to stop the ship from goinf over the edge of the grid
	int x = 0;
	int y = 1;
	//The constraints that the ship must be contained within to remain on the grid, one for x and one for y
	//Each one is an array so they can be changed at any point
	int xConstraint[] = { 0,9 };
	int yConstraint[] = { 1,8 };
	//Whether the player has rotated the ship veritcally or not
	bool isVertical = false;
	//Whether a ship has been placed 
	bool isShipPlaced = false;
	//Whether an input key has been pressed
	bool isKeyPressed = false;
	//If a ship has not been placed
	while (isShipPlaced == false)
	{
		//If the ship is being placed horizontally
		if (isVertical == false)
		{
			//Display a pontential ship onto the grid horizontally
			DisplayPotentialBattleShip(x, y, false);
		}
		//If the ship is being placed vertically
		else
		{
			//Display a pontential ship onto the grid vertically
			DisplayPotentialBattleShip(x, y, true);
		}
		//Display the grid in it's current state
		DisplayGrid();
		//Whilst an input key has not yet been pressed
		while (isKeyPressed == false)
		{
			//If the down key is pressed
			if (GetKeyState(VK_DOWN) & 0x8000)
			{
				//Move the ship downward one cell on the grid staying within the current x constraints
				if (x < xConstraint[1])
				{
					x++;
				}
				else
				{
					x = xConstraint[0];
				}
				//An input key has been pressed
				isKeyPressed = true;
			}
			//If the up key is pressed
			else if (GetKeyState(VK_UP) & 0x8000)
			{
				//Move the ship upward one cell on the grid staying within the current x constraints
				if (x > xConstraint[0])
				{
					x--;
				}
				else
				{
					x = xConstraint[1];
				}
				isKeyPressed = true;
			}
			//If the right key is pressed
			else if (GetKeyState(VK_RIGHT) & 0x8000)
			{
				//Move the ship right one cell on the grid staying within the current y constraints
				if (y < yConstraint[1])
				{
					y++;
				}
				else
				{
					y = yConstraint[0];
				}
				isKeyPressed = true;
			}
			//If the left key is pressed 
			else if (GetKeyState(VK_LEFT) & 0x8000)
			{
				//Move the ship left one cell on the grid staying within the current y constraints
				if (y > yConstraint[0])
				{
					y--;
				}
				else
				{
					y = yConstraint[1];
				}
				isKeyPressed = true;
			}
			//If the E key is pressed
			else if (GetKeyState('E') & 0x8000)
			{
				//If the ship is not rotated vertically
				if (isVertical == false)
				{
					//Check that the cells immediately to the left and right have a value of 2, meaning they are not currently occupied by another ship
					if (grid[x][y] == 2 && grid[x][y - 1] == 2 && grid[x][y + 1] == 2)
					{
						//Set the cells immediately to the left and right to a value of 1, meaning they are occupied by a ship
						grid[x][y] = 1;
						grid[x][y - 1] = 1;
						grid[x][y + 1] = 1;
					}
				}
				else
				{
					//Check that the cells immediately up and down have a value of 2, meaning they are not currently occupied by another ship
					if (grid[x][y] == 2 && grid[x - 1][y] == 2 && grid[x + 1][y] == 2)
					{
						//Set the cells immediately up and down to a value of 1, meaning they are occupied by a ship
						grid[x][y] = 1;
						grid[x - 1][y] = 1;
						grid[x + 1][y] = 1;
					}
				}
				//A ship has been placed
				//isShipPlaced = true;
				isKeyPressed = true;
			}
			//If the R key is pressed
			else if (GetKeyState('R') & 0x8000)
			{
				//If the ship is not currently rotated vertically
				if (isVertical == false)
				{
					//Rotate the ship vertically
					isVertical = true;

					//If the ship is currently on the very edge of it's x constraints, move it back 1 cell in the opposite direction (which also happens to be the same as equalling it to the yConstraints)
					//This is to stop the ship from being pushed outside of the grid by rotating it on an edge
					if (x == xConstraint[0])
					{
						x = yConstraint[0];
					}
					else if (x == xConstraint[1])
					{
						x = yConstraint[1];
					}

					//Flip the x and y constraints
					xConstraint[0] = 1;
					xConstraint[1] = 8;

					yConstraint[0] = 0;
					yConstraint[1] = 9;
				}
				//If the ship is currently rotated vertically
				else
				{
					//Rotate the ship horizontally
					isVertical = false;

					//If the ship is currently on the very edge of it's y constraints, move it back 1 cell in the opposite direction (which also happens to be the same as equalling it to the xConstraints)
					//This is to stop the ship from being pushed outside of the grid by rotating it on an edge
					if (y == yConstraint[0])
					{
						y = 1;
					}
					else if (y == yConstraint[1])
					{
						y = 8;
					}

					//Flip the x and y constraints
					xConstraint[0] = 0;
					xConstraint[1] = 9;

					yConstraint[0] = 1;
					yConstraint[1] = 8;
				}
				isKeyPressed = true;
			}
		}
		//After a key has been pressed
		while (isKeyPressed == true)
		{
			//Wait until none of the input keys are currently down
			//Each key is tested to ensure it is not -127 or -128, as testing for the key being down using GetKeyDown can return either of these values
			if ((GetKeyState(VK_DOWN) != -127 && GetKeyState(VK_DOWN) != -128) && (GetKeyState(VK_UP) != -127 && GetKeyState(VK_UP) != -128) &&
				(GetKeyState(VK_RIGHT) != -127 && GetKeyState(VK_RIGHT) != -128) && (GetKeyState(VK_LEFT) != -127 && GetKeyState(VK_LEFT) != -128) &&
				(GetKeyState('E') != -127 && GetKeyState('E') != -128) && (GetKeyState('R') != -127 && GetKeyState('R') != -128))
			{
				isKeyPressed = false;
			}
		}
		system("cls");

	}
}

void PlacementGrid::DisplayPotentialBattleShip(int x, int y, bool isVerical)
{
	ClearPotentialBattleShips();
	if (isVerical == false)
	{
		grid[x][y] = DisplayCellPlacement(x, y);
		grid[x][y - 1] = DisplayCellPlacement(x, y - 1);
		grid[x][y + 1] = DisplayCellPlacement(x, y + 1);
	}
	if (isVerical == true)
	{
		grid[x][y] = DisplayCellPlacement(x, y);
		grid[x - 1][y] = DisplayCellPlacement(x - 1, y);
		grid[x + 1][y] = DisplayCellPlacement(x + 1, y);
	}

}

void PlacementGrid::ClearPotentialBattleShips()
{
	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			if (grid[row][cell] == 2)
			{
				grid[row][cell] = 0;
			}
			else if (grid[row][cell] == 3)
			{
				grid[row][cell] = 1;
			}
		}
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