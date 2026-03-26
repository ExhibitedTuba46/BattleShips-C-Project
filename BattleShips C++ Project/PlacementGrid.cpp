//https://www.geeksforgeeks.org/cpp/how-to-detect-keypress-in-windows-using-cpp/

#include "PlacementGrid.h"
#include "Grid.h"
#include "BattleShip.h"
#include <iostream>
//Windows.h is only avialable on Windows PCs, this means that if I wanted this program to be useable on Mac for example, this would need to be replaced
//However for the purposes of this assignmemt Windows.h works perfectly
#include <windows.h>
#include<vector>
using namespace std;

int PlacementGrid::DisplayCellPlacement(int x, int y)
{
	if (grid[x][y] < 4)
	{
		return 2;
	}
	else
	{
		previousGridValue = grid[x][y];
		return 3;
	}
}

bool PlacementGrid::PlaceBattleShip(bool isVertical, BattleShip* shipBeingPlaced, int x, int y, bool isPlayer)
{
	BattleShip shipToPlace = *shipBeingPlaced;
	if (isVertical == false)
	{
		bool canPlaceShip = true;

		for (int cell = 0; cell < (shipToPlace.GetSizeInCells()); cell++)
		{

			if (grid[x][shipToPlace.ShipSize(y, cell)] != 2 && grid[x][shipToPlace.ShipSize(y, cell)] != 0)
			{
				canPlaceShip = false;
			}
		}

		if (canPlaceShip == true || isPlayer == false)
		{
			for (int cell = 0; cell < (shipToPlace.GetSizeInCells()); cell++)
			{
				grid[x][shipToPlace.ShipSize(y, cell)] = shipToPlace.GetShipIdentifier();
			}
			//A ship has been placed
			placedShips.push_back(shipBeingPlaced);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		bool canPlaceShip = true;

		for (int cell = 0; cell < (shipToPlace.GetSizeInCells()); cell++)
		{

			if (grid[shipToPlace.ShipSize(x, cell)][y] != 2 && grid[shipToPlace.ShipSize(x, cell)][y] != 0)
			{
				canPlaceShip = false;
			}
		}

		if (canPlaceShip == true || isPlayer == false)
		{
			for (int cell = 0; cell < (shipToPlace.GetSizeInCells()); cell++)
			{
				grid[shipToPlace.ShipSize(x, cell)][y] = shipToPlace.GetShipIdentifier();
			}
			//A ship has been placed
			placedShips.push_back(shipBeingPlaced);
			return true;
		}
		else
		{
			return false;
		}
	}
}

void PlacementGrid::PlaceAIShip(BattleShip* shipToPlace, int x, int y, bool isVertical)
{
	BattleShip& shipBeingPlaced = *shipToPlace;

	if (isVertical == false)
	{
		PlaceBattleShip(false, shipToPlace, x, y, false);
	}
	else
	{
		PlaceBattleShip(true, shipToPlace, x, y, false);
	}
}

/// <summary>
/// Query where the player wishes to place a BattleShip, and provide input to place one
/// </summary>
/// <param name="shipToQuery">A pointer to the ship that the grid should query.</param>
void PlacementGrid::QueryBattleShipInput(BattleShip* shipToQuery)
{
	BattleShip& shipInQuery = *shipToQuery;
	//The default x and y coordinates on the placement grid
	//The constraints that the ship must be contained within to remain on the grid, one for x and one for y
	//Each one is an array so they can be changed at any point
	int xConstraint[2] = { shipInQuery.GetXConstraints(0), shipInQuery.GetXConstraints(1) };
	int yConstraint[2] = { shipInQuery.GetYConstraints(0), shipInQuery.GetYConstraints(1) };
	//As every ship starts horizontally, this is offset from the ship's size in cells to stop the ship from goinf over the edge of the grid
	int x = 0;
	int y = yConstraint[0];
	//Whether the player has rotated the ship veritcally or not
	bool isVertical = false;
	//Whether a ship has been placed 
	bool isShipPlaced = false;
	//Whether an input key has been pressed
	bool isKeyPressed = false;
	//If a ship has not been placed
	while (isShipPlaced == false)
	{
		cout << "Select where you would like to place your " << shipInQuery.GetShipName() << "." << endl;
		cout << "Use the arrow keys to move the ship around the board. Press 'E' to place your ship and 'R' to rotate it." << endl;
		cout << endl;

		//If the ship is being placed horizontally
		if (isVertical == false)
		{
			//Display a pontential ship onto the grid horizontally
			DisplayPotentialBattleShip(x, y, false, shipToQuery);
		}
		//If the ship is being placed vertically
		else
		{
			//Display a pontential ship onto the grid vertically
			DisplayPotentialBattleShip(x, y, true, shipToQuery);
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
					isShipPlaced = PlaceBattleShip(false, shipToQuery, x, y, true);
				}
				else
				{
					isShipPlaced = PlaceBattleShip(true, shipToQuery, x, y, true);
				}
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
					if (x == xConstraint[0] || x == xConstraint[0] + 1)
					{
						x = yConstraint[0];
					}
					else if (x == xConstraint[1] || x == xConstraint[1] - 1)
					{
						x = yConstraint[1];
					}

					//Flip the x and y constraints
					xConstraint[0] = shipInQuery.GetYConstraints(0);
					xConstraint[1] = shipInQuery.GetYConstraints(1);

					yConstraint[0] = shipInQuery.GetXConstraints(0);
					yConstraint[1] = shipInQuery.GetXConstraints(1);
				}
				//If the ship is currently rotated vertically
				else
				{
					//Rotate the ship horizontally
					isVertical = false;

					//If the ship is currently on the very edge of it's y constraints, move it back 1 cell in the opposite direction (which also happens to be the same as equalling it to the xConstraints)
					//This is to stop the ship from being pushed outside of the grid by rotating it on an edge
					if (y == yConstraint[0] || y == yConstraint[0] + 1)
					{
						y = xConstraint[0];
					}
					else if (y == yConstraint[1] || y == yConstraint[1] - 1)
					{
						y = xConstraint[1];
					}

					//Flip the x and y constraints
					xConstraint[0] = shipInQuery.GetXConstraints(0);
					xConstraint[1] = shipInQuery.GetXConstraints(1);

					yConstraint[0] = shipInQuery.GetYConstraints(0);
					yConstraint[1] = shipInQuery.GetYConstraints(1);
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

void PlacementGrid::DisplayPotentialBattleShip(int x, int y, bool isVerical, BattleShip* shipToDisplay)
{
	BattleShip& shipInDisplay = *shipToDisplay;
	ClearPotentialBattleShips();
	if (isVerical == false)
	{
		for (int cell = 0; cell < (shipInDisplay.GetSizeInCells()); cell++)
		{

			grid[x][shipInDisplay.ShipSize(y, cell)] = DisplayCellPlacement(x, shipInDisplay.ShipSize(y, cell));
		}

	}
	if (isVerical == true)
	{
		for (int cell = 0; cell < (shipInDisplay.GetSizeInCells()); cell++)
		{

			grid[shipInDisplay.ShipSize(x, cell)][y] = DisplayCellPlacement(shipInDisplay.ShipSize(x, cell), y);
		}
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
				grid[row][cell] = previousGridValue;
			}
		}
	}
}

int PlacementGrid::QueryHitInput(int x, int y)
{
	if (grid[x][y] > 3)
	{
		for (BattleShip* shipPointer : placedShips)
		{
			BattleShip& ship = *shipPointer;
			if (ship.GetShipIdentifier() == grid[x][y])
			{
				ship.DamageShip();
			}
		}
		grid[x][y] = 1;
		return 1;
	}
	else
	{
		grid[x][y] = 2;
		return 2;
	}
}

void PlacementGrid::DisplayGrid()
{
	cout << "\033[0m";
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
				cout << "\033[31mX ";
				cout << "\033[0m";
				break;
			case 2:
				cout << "\033[0mO ";
				break;
			case 1:
				cout << "\033[31mX ";
				cout << "\033[0m";
				break;
			case 0:
				cout << "\033[36m~ ";
				cout << "\033[0m";
				break;
			default:
				cout << "\033[1;90m# ";
				cout << "\033[0m";
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
}