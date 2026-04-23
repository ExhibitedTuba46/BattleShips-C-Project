#include "StrikingGrid.h"
#include "PlacementGrid.h"
#include "Grid.h"
#include <iostream>
#include <windows.h>
using namespace std;

/// <summary>
/// Display the grid, masking the real values with their corresponding symbols
/// </summary>
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
				//If this cell is a hit but the crosshair is over it, display a yellow X
			case 5:
				cout << "\033[33mX ";
				cout << "\033[0m";
				break;
				//If this cell is a miss but the crosshair is over it, display a yellow O
			case 4:
				cout << "\033[33mO ";
				cout << "\033[0m";
				break;
				//If this cell is where the player is currently aiming display a yellow +
			case 3:
				cout << "\033[33m+ ";
				cout << "\033[0m";
				break;
				//If this cell is a miss display a white O
			case 2:
				cout << "\033[0mO ";
				break;
				//If this cell is a hit display a red X
			case 1:
				cout << "\033[31mX ";
				cout << "\033[0m";
				break;
				//If this cell is empty display a blue ~
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

/// <summary>
/// Strike the grid autonomously from an AI
/// </summary>
/// <param name="pointerToStrike">A pointer to the grid that the AI should target</param>
/// <param name="chosenCell">The cell the AI has chosen to strike</param>
void StrikingGrid::AIStrike(PlacementGrid* pointerToStrike, pair<int, int> chosenCell)
{
	PlacementGrid& gridToStrike = *pointerToStrike;
	//Query whether the cell chosen by the AI is a hit or miss
	grid[chosenCell.first][chosenCell.second] = gridToStrike.QueryHitInput(chosenCell.first, chosenCell.second);
	//If the AI has missed
	if (grid[chosenCell.first][chosenCell.second] != 1)
	{
		//Inform the player that the AI has missed
		system("cls");
		cout << "The AI has missed!" << endl;
		cout << endl;
	}
}

/// <summary>
/// Query where the player wishes to strike, and provide input to do so
/// </summary>
/// <param name="pointerToStrike">A pointer to the grid that the player is targeting</param>
/// <param name="playerPlacementGrid">The placement grid of the player</param>
void StrikingGrid::QuerySrikeInput(PlacementGrid* pointerToStrike, PlacementGrid playerPlacementGrid)
{
	PlacementGrid& gridToStrike = *pointerToStrike;

	bool hasStruck = false;

	bool isKeyPressed = false;

	//If the cell that the player is currently targeting is 0 then display the default crosshair
	if (grid[x][y] == 0)
	{
		grid[x][y] = 3;
	}

	//Whilst the player has not already chosen a place to strike
	while (hasStruck == false)
	{
		//Display to the player that it currently their turn to strike the AI's ships and inform them of the controls
		cout << "Your turn:" << endl;
		cout << "Choose a place on the AI's board to strike." << endl;
		cout << "Use the \033[33marrow keys\033[0m to aim around the board. Press '\033[33mE\033[0m' to strike." << endl;
		cout << "AI ships remaining: " << gridToStrike.GetShipsRemaining() << endl;
		cout << endl;

		//Display the striking grid to the player so they can see where they have hit previously
		cout << "AI's board:" << endl;
		DisplayGrid();
		//Display the player's ships to them so they can see where the AI is striking
		cout << "Your ships:" << endl;
		playerPlacementGrid.DisplayGrid();

		//Inform the player of what each symbol on both their striking grid and placement grid mean so they know what is happening
		cout << "BOARD LEGEND:" << endl;
		cout << endl;
		cout << "Generic:" << endl;
		cout << "Hit - \033[31mX\033[0m" << endl;
		cout << "Miss - O" << endl;
		cout << "Empty cell - \033[36m~\033[0m" << endl;
		cout << endl;
		cout << "Striking board:" << endl;
		cout << "Striking crosshair - \033[33m+\033[0m" << endl;
		cout << "Crosshair over hit - \033[33mX\033[0m" << endl;
		cout << "Crosshair over miss - \033[33mO\033[0m" << endl;
		cout << endl;
		cout << "Ship view:" << endl;
		cout << "Placed ship - \033[1;90m#\033[0m" << endl;

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
				//If the current cell has not already been struck
				if (grid[x][y] == 3)
				{
					//Query whether this cell was a hit or a miss
					grid[x][y] = gridToStrike.QueryHitInput(x, y);
					//If the player missed
					if (grid[x][y] != 1)
					{
						//Display that the player has missed
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
		//For every cell on the grid
		for (int row = 0; row < 10; row++)
		{
			for (int cell = 0; cell < 10; cell++)
			{
				//If the current cell is where the crosshair is, remove it
				if (grid[row][cell] == 3)
				{
					grid[row][cell] = 0;
				}
				//If the crosshair currently over a miss then set it back to the default miss symbol
				else if (grid[row][cell] == 4)
				{
					grid[row][cell] = 2;
				}
				//If the crosshair currently over a hit then set it back to the default hit symbol
				else if (grid[row][cell] == 5)
				{
					grid[row][cell] = 1;
				}
			}
		}
		//If the cell where the crosshair is currently located is empty then set it as a default crosshair symbol
		if (grid[x][y] < 1)
		{
			grid[x][y] = 3;
		}
		//If the cell where the crosshair is currently located is a miss then set it as a yellow miss symbol
		else if (grid[x][y] == 2)
		{
			grid[x][y] = 4;
		}
		//If the cell where the crosshair is currently located is a hit then set it as a yellow hit symbol
		else
		{
			grid[x][y] = 5;
		}

		if (hasStruck == false)
		{
			system("cls");
		}
	}
}
