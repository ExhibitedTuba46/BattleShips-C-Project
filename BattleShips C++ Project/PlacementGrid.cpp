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

/// <summary>
/// Determine how to display a potential cell that a ship could be placed on
/// </summary>
/// <param name="x">The X coordinate</param>
/// <param name="y">The Y coordinate</param>
/// <returns></returns>
int PlacementGrid::DisplayCellPlacement(int x, int y)
{
	//If the cell is less than 4, then it has not already been placed on
	if (grid[x][y] < 4)
	{
		//Display a valid ship placement symbol on the cell
		return 2;
	}
	//If this cell is already in use 
	else
	{
		//Display and invalid ship placement symbol on the cell
		return 3;
	}
}

/// <summary>
/// Place a ship at a given position on the grid
/// </summary>
/// <param name="isVertical">Whether this ship is vertical</param>
/// <param name="shipBeingPlaced">The ship to place on the grid</param>
/// <param name="x">The X coordinate</param>
/// <param name="y">The Y coordinate</param>
/// <param name="isPlayer">Whether this function was called by the player</param>
/// <returns></returns>
bool PlacementGrid::PlaceBattleShip(bool isVertical, BattleShip* shipBeingPlaced, int x, int y, bool isPlayer)
{
	BattleShip shipToPlace = *shipBeingPlaced;
	//If this ship is horizontal
	if (isVertical == false)
	{
		bool canPlaceShip = true;

		//Check each cell this ship contains to check it can be placed here
		for (int cell = 0; cell < (shipToPlace.GetSizeInCells()); cell++)
		{
			//If the cell is not empty or currently displaying a valid ship position
			if (grid[x][shipToPlace.ShipSize(y, cell)] != 2 && grid[x][shipToPlace.ShipSize(y, cell)] != 0)
			{
				//Mark this location as not valid
				canPlaceShip = false;
			}
		}

		//If this location is valid
		//If this was placed by AI it can be assumed the AI has already worked out if it can be placed, therefore it can be placed regardless
		if (canPlaceShip == true || isPlayer == false)
		{
			//For each cell in the ship set the corresponding cell on both grids to that ship's identifier
			for (int cell = 0; cell < (shipToPlace.GetSizeInCells()); cell++)
			{
				grid[x][shipToPlace.ShipSize(y, cell)] = shipToPlace.GetShipIdentifier();
				realGridValues[x][shipToPlace.ShipSize(y, cell)] = shipToPlace.GetShipIdentifier();
			}
			//Add this ship to the list of placed ships
			placedShips.push_back(shipBeingPlaced);
			return true;
		}
		//If this position in not valid
		else
		{
			return false;
		}
	}
	//If this ship is vertical then repeat the same steps but on the Y axis instead
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
				realGridValues[shipToPlace.ShipSize(x, cell)][y] = shipToPlace.GetShipIdentifier();
			}
			placedShips.push_back(shipBeingPlaced);
			return true;
		}
		else
		{
			return false;
		}
	}
}

/// <summary>
/// Return the number of ships remaining on the grid that have not been sunk
/// </summary>
/// <returns></returns>
int PlacementGrid::GetShipsRemaining()
{
	int shipsRemaining = 0;
	//For each ship in placed ships check whehther it has been sunk
	for (int ship = 0; ship < placedShips.size(); ship++)
	{
		if (placedShips[ship]->GetShipStatus() == false)
		{
			//If it has not increase the number of ships not sunk
			shipsRemaining++;
		}
	}

	return shipsRemaining;
}

/// <summary>
/// Place a battleship autonamously from an AI
/// </summary>
/// <param name="shipToPlace">The ship the function should place</param>
/// <param name="x">The X coordinate</param>
/// <param name="y">The Y coordinate</param>
/// <param name="isVertical">Whether the ship is vertical or horizontal</param>
void PlacementGrid::PlaceAIShip(BattleShip* shipToPlace, int x, int y, bool isVertical)
{
	BattleShip& shipBeingPlaced = *shipToPlace;

	//If the ship is horizontal place it along the X axis
	if (isVertical == false)
	{
		PlaceBattleShip(false, shipToPlace, x, y, false);
	}
	//If not place it along the Y axis
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
	//The constraints that the ship must be contained within to remain on the grid, one for x and one for y
	//Each one is an array so they can be changed at any point
	int xConstraint[2] = { shipInQuery.GetXConstraints(0), shipInQuery.GetXConstraints(1) };
	int yConstraint[2] = { shipInQuery.GetYConstraints(0), shipInQuery.GetYConstraints(1) };
	//As every ship starts horizontally, this is offset from the ship's size in cells to stop the ship from going over the edge of the grid
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
		//Display to the player that they should place a ship, and inform them of the inputs required to do so
		cout << "Placement phase:" << endl;
		cout << "Select where you would like to place your " << shipInQuery.GetShipName() << "." << endl;
		cout << "Use the \033[33marrow keys\033[0m to move the ship around the board. Press '\033[33mE\033[0m' to place your ship and '\033[33mR\033[0m' to rotate it." << endl;
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
		cout << "Your board:" << endl;
		DisplayGrid();

		//Inform the player of what each symbol on the grid means, so they can understand what is happening
		cout << "BOARD LEGEND:" << endl;
		cout << endl;
		cout << "Valid ship placement - O" << endl;
		cout << "Invalid ship placement - \033[31mX\033[0m" << endl;
		cout << "Empty cell - \033[36m~\033[0m" << endl;
		cout << "Placed ship - \033[1;90m#\033[0m" << endl;

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

/// <summary>
/// Determine how to display a potential ship placement
/// </summary>
/// <param name="x">The x coordinate of the ship</param>
/// <param name="y">The y coordinate of the ship</param>
/// <param name="isVerical">Whether this ship is vertical</param>
/// <param name="shipToDisplay">The ship to display on the grid</param>
void PlacementGrid::DisplayPotentialBattleShip(int x, int y, bool isVerical, BattleShip* shipToDisplay)
{
	BattleShip& shipInDisplay = *shipToDisplay;
	//Reset the grid
	ClearPotentialBattleShips();
	//If the ship is horizontal
	if (isVerical == false)
	{
		//For each cell in the potential ship 
		for (int cell = 0; cell < (shipInDisplay.GetSizeInCells()); cell++)
		{
			//Determine how to display each cell on the grid
			grid[x][shipInDisplay.ShipSize(y, cell)] = DisplayCellPlacement(x, shipInDisplay.ShipSize(y, cell));
		}

	}
	//If the ship is vertical repeat but on the Y axis
	if (isVerical == true)
	{
		for (int cell = 0; cell < (shipInDisplay.GetSizeInCells()); cell++)
		{
			grid[shipInDisplay.ShipSize(x, cell)][y] = DisplayCellPlacement(shipInDisplay.ShipSize(x, cell), y);
		}
	}

}

/// <summary>
/// Reset the grid and remove any displays for potential battleships
/// </summary>
void PlacementGrid::ClearPotentialBattleShips()
{
	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			//If this cell is marked as a potential battleship position reset it to be empty
			if (grid[row][cell] == 2)
			{
				grid[row][cell] = 0;
			}
			//If this cell is marked as an invalid battleship position then reset it to the identifier of the ship that is placed here on the realGridValues coordinate
			//This means that the ship will still be placed in the same place on both grids with the same identifier rather than being reset when this function is called
			else if (grid[row][cell] == 3)
			{
				grid[row][cell] = realGridValues[row][cell];
			}
		}
	}
}

/// <summary>
/// Query whether the given coordinate would be a hit or miss
/// </summary>
/// <param name="x">The X coordinate</param>
/// <param name="y">The Y coordinate</param>
/// <returns></returns>
int PlacementGrid::QueryHitInput(int x, int y)
{
	//If this cell is over 3 then this is a hit
	if (grid[x][y] > 3)
	{
		for (BattleShip* shipPointer : placedShips)
		{
			//Find which ship has the identifier of the current cell and damage it
			BattleShip& ship = *shipPointer;
			if (ship.GetShipIdentifier() == grid[x][y])
			{
				ship.DamageShip();
			}
		}
		//Set the current cell as a hit and return a hit 
		grid[x][y] = 1;
		return 1;
	}
	//If it less or equal to 3 then this is a miss
	else
	{
		//Set the current cell as a miss and return a miss
		grid[x][y] = 2;
		return 2;
	}
}

/// <summary>
/// Display the grid but mask the real values with corresponding symbols
/// </summary>
void PlacementGrid::DisplayGrid()
{
	cout << "\033[0m";
	//This array of characters will allow the function to dislay the letter that each row grid corresponds to
	char rowLetter[10] = { 'A', 'B', 'C', 'D','E', 'F', 'G', 'H', 'I', 'J' };
	//Display the number that each column corresponds to
	cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
	for (int row = 0; row < 10; row++)
	{
		//Display the letter for this row
		cout << rowLetter[row] << " ";
		for (int cell = 0; cell < 10; cell++)
		{
			switch (grid[row][cell])
			{
				//If this cell is marked as 3 then it is temporarily displayed as a red X to show it is an invalid ship position
				//This is separate from a hit which is also marked as a red X, but these two are never used at the same time
			case 3:
				cout << "\033[31mX ";
				cout << "\033[0m";
				break;
				//If this is cell is either a miss or a valid position for a ship to be used then display a white O
			case 2:
				cout << "\033[0mO ";
				break;
				//If this cell is a hit then display a red X
			case 1:
				cout << "\033[31mX ";
				cout << "\033[0m";
				break;
				//If this cell is empty then display a blue ~ to imitate the ocean
			case 0:
				cout << "\033[36m~ ";
				cout << "\033[0m";
				break;
				//If this cell has a ship placed on it (value is higher or equal to 4), display a grey #
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