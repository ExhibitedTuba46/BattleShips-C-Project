#include "AIopponent.h"
#include <iostream>
#include <random>
#include <vector>
#include "BattleShip.h"
#include "PlacementGrid.h"
#include "StrikingGrid.h"
#include "Grid.h"
using namespace std;

int AIOpponent::GetRandomValue(int min, int max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}

bool AIOpponent::GetRandomRotation()
{
	int rotation = GetRandomValue(0, 2);

	if (rotation == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void AIOpponent::UpdateHeatMap(StrikingGrid gridToStrike)
{
	for (int i = 0; i < 10; i++)
	{
		GenerateHeatMap(gridToStrike);
	}
}

int AIOpponent::SetHeatMapCell(int x, int y, int xOffset, int yOffset)
{
	int neighbourCell = heatMap[x + xOffset][y + yOffset];
	if (neighbourCell == 9)
	{
		return 7;
	}
	else if (neighbourCell == 8)
	{
		return -1;
	}
	else if (neighbourCell > 2)
	{
		return neighbourCell - 1;
	}
	else if (neighbourCell < 2)
	{
		return neighbourCell + 1;
	}
}

void AIOpponent::GenerateHeatMap(StrikingGrid gridToStrike)
{
	CopyGrid(gridToStrike);
	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			if (copiedGrid[row][cell] == 1)
			{
				heatMap[row][cell] = 9;
			}
			else if (copiedGrid[row][cell] == 2)
			{
				heatMap[row][cell] = 8;
			}

			if (heatMap[row][cell] < 8)
			{
				int neighbour1 = 0;
				int neighbour2 = 0;
				int neighbour3 = 0;
				int neighbour4 = 0;

				for (int dir = 0; dir < 4; dir++)
				{
					switch (dir)
					{
					case 0:
						if (row != 0)
						{
							neighbour1 = SetHeatMapCell(row, cell, -1, 0);
						}
						break;
					case 1:
						if (cell != 9)
						{
							neighbour2 = SetHeatMapCell(row, cell, 0, 1);
						}
						break;
					case 2:
						if (row != 9)
						{
							neighbour3 = SetHeatMapCell(row, cell, 1, 0);
						}
						break;
					case 3:
						if (cell != 0)
						{
							neighbour4 = SetHeatMapCell(row, cell, 0, -1);
						}
						break;

					default:
						break;
					}
				}
				int totalValue = neighbour1 + neighbour2 + neighbour3 + neighbour4;
				totalValue = totalValue / 3;
				heatMap[row][cell] = totalValue;
			}
		}
	}
}

void AIOpponent::DisplayHeatMap()
{
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

pair<int, int> AIOpponent::ChooseRandomCell(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical)
{
	CopyGrid(gridToPlaceOn);

	int minX;
	int maxX;

	int minY;
	int maxY;

	if (isVertical == false)
	{
		minX = shipToPlace.GetXConstraints(0);
		maxX = shipToPlace.GetXConstraints(1);

		minY = shipToPlace.GetYConstraints(0);
		maxY = shipToPlace.GetYConstraints(1);
	}
	else
	{
		minX = shipToPlace.GetYConstraints(0);
		maxX = shipToPlace.GetYConstraints(1);

		minY = shipToPlace.GetXConstraints(0);
		maxY = shipToPlace.GetXConstraints(1);
	}

	bool hasFoundCell = false;

	int randomX = 0;
	int randomY = 0;

	while (hasFoundCell == false)
	{
		randomX = GetRandomValue(minX, maxX);
		randomY = GetRandomValue(minY, maxY);

		bool isCellValid = true;
		for (int cell = 0; cell < (shipToPlace.GetSizeInCells()); cell++)
		{
			if (isVertical == false)
			{
				if (copiedGrid[randomX][shipToPlace.ShipSize(randomY, cell)] != 0)
				{
					isCellValid = false;
				}
			}
			else
			{
				if (copiedGrid[shipToPlace.ShipSize(randomX, cell)][randomY] != 0)
				{
					isCellValid = false;
				}
			}
		}
		if (isCellValid == true)
		{
			hasFoundCell = true;
		}
	}

	pair<int, int> chosenCell = { randomX, randomY };

	return chosenCell;
}

pair<int, int> AIOpponent::GetBestCell()
{
	int highestValue = 0;

	int lowestValue = 7;

	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			if (heatMap[row][cell] < 8)
			{
				if (heatMap[row][cell] > highestValue)
				{
					highestValue = heatMap[row][cell];
				}

				if (heatMap[row][cell] < lowestValue)
				{
					lowestValue = heatMap[row][cell];
				}
			}
		}
	}

	vector<pair<int, int>> highestCells;

	vector<pair<int, int>> lowestCells;

	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
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

	if (nonOptimalHits < 3)
	{
		randomChoice = GetRandomValue(0, 6);
	}
	else
	{
		randomChoice = 1;
	}

	if (randomChoice < 6)
	{
		pair<int, int> chosenCell = highestCells[GetRandomValue(0, highestCells.size() - 1)];
		nonOptimalHits = 0;
		return chosenCell;
	}
	else
	{
		pair<int, int> chosenCell = lowestCells[GetRandomValue(0, lowestCells.size() - 1)];
		nonOptimalHits += 1;
		return chosenCell;
	}


}

void AIOpponent::CopyGrid(Grid gridToCopy)
{
	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			copiedGrid[row][cell] = gridToCopy.GetCell(row, cell);
		}
	}
}