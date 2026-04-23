#include "AIopponent.h"
#include <iostream>
#include <random>
#include <vector>
#include "BattleShip.h"
#include "PlacementGrid.h"
#include "StrikingGrid.h"
#include "Grid.h"
using namespace std;

/// <summary>
/// Get a random value between the given minimum and maximum values
/// </summary>
/// <param name="min">The minimum value to choose from</param>
/// <param name="max">The maximum value to choose from</param>
/// <returns></returns>
int AIOpponent::GetRandomValue(int min, int max)
{
	//Generate a random number using random distribution
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}

/// <summary>
/// Get a random rotation between horizontal and vertical for placing ships autonomously
/// </summary>
/// <returns></returns>
bool AIOpponent::GetRandomRotation()
{
	
	int rotation = GetRandomValue(0, 2);

	//If the random roll chose 0 then return false (horizontal) or true (vertical)
	if (rotation == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/// <summary>
/// Update the AI's targeting heatmap
/// </summary>
/// <param name="gridToStrike">The striking grid the AI should be updating from</param>
void AIOpponent::UpdateHeatMap(StrikingGrid gridToStrike)
{
	//The generate heatmap function is called multiple times
	//It must be called more than once to have a full coverage of the grid but I found that around 10 times gives the best results
	for (int i = 0; i < 10; i++)
	{
		GenerateHeatMap(gridToStrike);
	}
}

int AIOpponent::CheckHeatMapNeighbours(int x, int y, int xOffset, int yOffset)
{
	//Get the value of the given cell's neighbour
	int neighbourCell = heatMap[x + xOffset][y + yOffset];
	//If the neighbouring cell is a hit, return a value of 7, the highest the heatmap is allowed to go, essentially guaranteeing the next strike will be on this cell
	if (neighbourCell == 9)
	{
		return 7;
	}
	//If the neighbouring cell is a miss, then return a value of -1, the lowest the heatmap is allowed to go, essentially guaranteeing that the AI will not strike here
	else if (neighbourCell == 8)
	{
		return -1;
	}
	//The heatmap is balanced around a medium value of 2
	//If the neighbouring cell is less than 2 then increase the value of this cell to bring the grid back to 2
	//Or if the neighbouring cell is over 2 then decrease the value of this cell to bring the grid back to 2
	//This ensures that high and low values are only around areas that the AI has already struck
	else if (neighbourCell > 2)
	{
		return neighbourCell - 1;
	}
	else if (neighbourCell < 2)
	{
		return neighbourCell + 1;
	}
}

/// <summary>
/// Pass over every cell on the heatmap and generate it's value
/// </summary>
/// <param name="gridToStrike">The grid to generate heatmap values from</param>
void AIOpponent::GenerateHeatMap(StrikingGrid gridToStrike)
{
	//Copy the grid given an store it locally
	CopyGrid(gridToStrike);
	//For each cell on the heatmap grid
	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			//If the current cell is equal to 1 (a hit) then set the heatmap cell to 9
			if (copiedGrid[row][cell] == 1)
			{
				heatMap[row][cell] = 9;
			}
			//If the current cell is equal to 2 (a hit) then set the heatmap cell to 8
			else if (copiedGrid[row][cell] == 2)
			{
				heatMap[row][cell] = 8;
			}

			//Check that the cell is not a miss or a hit (less than 8)
			if (heatMap[row][cell] < 8)
			{
				//The values this cell would be if it were only next to one neighbour in each direction
				//These will be used to work out an average
				int neighbour1 = 0;
				int neighbour2 = 0;
				int neighbour3 = 0;
				int neighbour4 = 0;

				//For each cardinal direction
				for (int dir = 0; dir < 4; dir++)
				{
					switch (dir)
					{
						//North
					case 0:
						//If the cell chosen is not on an edge of the grid(which would not have valid neighbours in this direction)
						if (row != 0)
						{
							//Set the corresponding neighbour variable to the value given by the CheckHeatMapNeighbours function
							neighbour1 = CheckHeatMapNeighbours(row, cell, -1, 0);
						}
						break;
						//East
					case 1:
						//If the cell chosen is not on an edge of the grid(which would not have valid neighbours in this direction)
						if (cell != 9)
						{
							neighbour2 = CheckHeatMapNeighbours(row, cell, 0, 1);
						}
						break;
						//South
					case 2:
						//If the cell chosen is not on an edge of the grid(which would not have valid neighbours in this direction)
						if (row != 9)
						{
							neighbour3 = CheckHeatMapNeighbours(row, cell, 1, 0);
						}
						break;
						//West
					case 3:
						//If the cell chosen is not on an edge of the grid(which would not have valid neighbours in this direction)
						if (cell != 0)
						{
							neighbour4 = CheckHeatMapNeighbours(row, cell, 0, -1);
						}
						break;

					default:
						break;
					}
				}
				//To work out an average value for this cell, add all neighbour values together, and then divide this by 3
				//This is not an exact average, but it produces more desirable results than dividing by 4 instead
				int totalValue = neighbour1 + neighbour2 + neighbour3 + neighbour4;
				totalValue = totalValue / 3;
				//Set this heatmap cell to the average value 
				heatMap[row][cell] = totalValue;
			}
		}
	}
}

/// <summary>
/// Display the AI's heatmap values on a grid
/// </summary>
void AIOpponent::DisplayHeatMap()
{
	//Display each cell on the heatmap without masking their values
	for (int row = 0; row < 10; row++)
	{
		cout << "  ";
		for (int cell = 0; cell < 10; cell++)
		{
			cout << heatMap[row][cell] << " ";
		}
		cout << endl;
	}
}

/// <summary>
/// Chooses a random cell on the placement grid for the AI to place a ship
/// </summary>
/// <param name="gridToPlaceOn">The placement grid the AI should try to place a ship on</param>
/// <param name="shipToPlace">The ship type that the AI should place</param>
/// <param name="isVertical">Whether the ship is vertical or not</param>
/// <returns></returns>
pair<int, int> AIOpponent::ChooseRandomCell(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical)
{
	//Copy the placement grid and store it locally
	CopyGrid(gridToPlaceOn);

	//Variables to store the placement constraints that the AI is given
	int minX;
	int maxX;

	int minY;
	int maxY;

	//If the ship is horizontal then it's placement constraints are given as normal
	if (isVertical == false)
	{
		minX = shipToPlace.GetXConstraints(0);
		maxX = shipToPlace.GetXConstraints(1);

		minY = shipToPlace.GetYConstraints(0);
		maxY = shipToPlace.GetYConstraints(1);
	}
	//If the ship is vertical then it's placement constraints are flipped
	else
	{
		minX = shipToPlace.GetYConstraints(0);
		maxX = shipToPlace.GetYConstraints(1);

		minY = shipToPlace.GetXConstraints(0);
		maxY = shipToPlace.GetXConstraints(1);
	}

	//Whether the AI has found a valid cell to place the ship on
	bool hasFoundCell = false;

	int randomX = 0;
	int randomY = 0;

	//While looking for a cell
	while (hasFoundCell == false)
	{
		//Choose a random cell from within the ships placement constraints
		randomX = GetRandomValue(minX, maxX);
		randomY = GetRandomValue(minY, maxY);

		
		bool isCellValid = true;
		//For each cell that the ship would cover
		for (int cell = 0; cell < (shipToPlace.GetSizeInCells()); cell++)
		{
			//If horizontal then check along the X axis
			if (isVertical == false)
			{
				//If the selected cell is not empty then this fucntion has not found a valid ship position
				if (copiedGrid[randomX][shipToPlace.ShipSize(randomY, cell)] != 0)
				{
					isCellValid = false;
				}
			}
			//If vertical then check along the Y axis
			else
			{
				//If the selected cell is not empty then this fucntion has not found a valid ship position
				if (copiedGrid[shipToPlace.ShipSize(randomX, cell)][randomY] != 0)
				{
					isCellValid = false;
				}
			}
		}
		//If the function has found a valid ship position then mark that the AI has found a valid cell
		if (isCellValid == true)
		{
			hasFoundCell = true;
		}
	}

	//Return the cell found in a pair of ints
	//A coordinate on the grid needs both the X and Y values to be used, so returning them both here is neccessary
	pair<int, int> chosenCell = { randomX, randomY };

	return chosenCell;
}

/// <summary>
/// Choose a cell on the heatmap to strike on
/// </summary>
/// <returns></returns>
pair<int, int> AIOpponent::TargetHeatmapCell()
{
	//These two variables store both the highest and lowest cell values that the function finds
	//The highest value is 0 by default, meaning anything that is found should be higher than this
	//The lowest value is 7 by defalut, meaning anything that is found should be lower than this
	int highestValue = 0;

	int lowestValue = 7;

	//For each cell on the heatmap
	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			//If the cell is not a miss or hit (less than 8)
			if (heatMap[row][cell] < 8)
			{
				//If the cell value is higher than the highest found value, set that as the new highest value
				if (heatMap[row][cell] > highestValue)
				{
					highestValue = heatMap[row][cell];
				}

				//If the cell value is lower than the lowest found value, set that as the new lowest value
				if (heatMap[row][cell] < lowestValue)
				{
					lowestValue = heatMap[row][cell];
				}
			}
		}
	}

	//A vector of cells that match the lowest or highest value

	vector<pair<int, int>> highestCells;

	vector<pair<int, int>> lowestCells;

	//For each cell on the heatmap
	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			//If the cell's value matches either the highest or lowest value, add it to the corresponding cell vector
			if (heatMap[row][cell] == highestValue)
			{
				highestCells.push_back({ row, cell });
			}

			if (heatMap[row][cell] == lowestValue)
			{
				lowestCells.push_back({ row, cell });
			}
		}
	}

	int randomChoice;

	//If the AI has not already rolled 3 non optimal hits 
	if (nonOptimalHits < 3)
	{
		//Roll between 1 and 6
		randomChoice = GetRandomValue(0, 6);
	}
	else
	{
		//Otherwise guarantee this hit will be optimal
		randomChoice = 1;
	}

	//If the roll chooses 1 - 5, randomly choose between the highest cells (optimal hit)
	if (randomChoice < 6)
	{
		pair<int, int> chosenCell = highestCells[GetRandomValue(0, highestCells.size() - 1)];
		//Reset the non optimal hit counter to 0
		nonOptimalHits = 0;
		return chosenCell;
	}
	//Otherwuse if it rolls a 6 randomly choose between the lowest cells (non optimal hit)
	//This keeps the AI unpredictable, and may set it free if it becomes stuck trying to hit one area repeatedly
	else
	{
		pair<int, int> chosenCell = lowestCells[GetRandomValue(0, lowestCells.size() - 1)];
		//Add to the counter of non optimal hits
		nonOptimalHits += 1;
		return chosenCell;
	}
}

/// <summary>
/// Copy the grid given and store it locally
/// </summary>
/// <param name="gridToCopy">The grid the AI should copy</param>
void AIOpponent::CopyGrid(Grid gridToCopy)
{
	//Create a duplicate of the given grid in the copiedGrid variable
	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			copiedGrid[row][cell] = gridToCopy.GetCell(row, cell);
		}
	}
}