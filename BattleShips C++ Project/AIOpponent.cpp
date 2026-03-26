#include "AIOpponent.h"
#include <iostream>
#include <random>
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
		return 1;
	}
	else if (neighbourCell > 3)
	{
		return neighbourCell - 1;
	}
	else if (neighbourCell < 3)
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

			if (heatMap[row][cell] != 8 && heatMap[row][cell] != 9)
			{
				int highestValue = 0;

				for (int dir = 0; dir < 4; dir++)
				{
					switch (dir)
					{
					case 0:
						if (row != 0)
						{
							int neighbour = SetHeatMapCell(row, cell, -1, 0);
							if (neighbour > highestValue)
							{
								highestValue = neighbour;
							}
						}
						break;
					case 1:
						if (cell != 9)
						{
							int neighbour = SetHeatMapCell(row, cell, 0, 1);
							if (neighbour > highestValue)
							{
								highestValue = neighbour;
							}
						}
						break;
					case 2:
						if (row != 9)
						{
							int neighbour = SetHeatMapCell(row, cell, 1, 0);
							if (neighbour > highestValue)
							{
								highestValue = neighbour;
							}
						}
						break;
					case 3:
						if (cell != 0)
						{
							int neighbour = SetHeatMapCell(row, cell, 0, -1);
							if (neighbour > highestValue)
							{
								highestValue = neighbour;
							}
						}
						break;

					default:
						break;
					}
				}
				heatMap[row][cell] = highestValue;
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

int AIOpponent::GetBestCell(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical, bool returnXAxis)
{
	CopyGrid(gridToPlaceOn);

	int xConstraints[2] = { 0 , 10 };
	int yConstraints[2] = { 0, 10 };

	if (isVertical == false)
	{
		xConstraints[0] = shipToPlace.GetXConstraints(0);
		xConstraints[1] = shipToPlace.GetXConstraints(1);

		yConstraints[0] = shipToPlace.GetYConstraints(0);
		yConstraints[1] = shipToPlace.GetYConstraints(1);
	}
	else
	{
		xConstraints[0] = shipToPlace.GetYConstraints(0);
		xConstraints[1] = shipToPlace.GetYConstraints(1);

		yConstraints[0] = shipToPlace.GetXConstraints(0);
		yConstraints[1] = shipToPlace.GetXConstraints(1);
	}


	/*
	* DO NOT USE
	int bestCell[] = { xConstraints[0], yConstraints[0] };
	int bestCellSpace = 0;
	for (int row = 0; row < 10; row++)
	{
		if (xConstraints[0] < row && row < xConstraints[1])
		{
			for (int cell = 0; cell < 10; cell++)
			{
				if (yConstraints[0] < cell && cell < yConstraints[1])
				{
					if (copiedGrid[row][cell] == 0)
					{
						int distance = 1;

						int spaceAround = 0;
						bool hasHitObstacle = false;
						while (hasHitObstacle == false)
						{
							for (int dir = 0; dir < 8; dir++)
							{
								int x = row;
								int y = cell;

								switch (dir)
								{
								case 7:
									x -= distance;
									y += distance;
									break;
								case 6:
									x -= distance;
									y -= distance;
									break;
								case 5:
									x += distance;
									y -= distance;
									break;
								case 4:
									x += distance;
									y += distance;
									break;
								case 3:
									y -= distance;
									break;
								case 2:
									x -= distance;
									break;
								case 1:
									y += distance;
									break;
								case 0:
									x += distance;
									break;
								default:
									break;
								}
								if ((y != yConstraints[0] && y != yConstraints[1])
									&& (x != xConstraints[0] && x != xConstraints[1]))
								{
									if (copiedGrid[x][y] == 0)
									{
										spaceAround++;
									}
									else
									{
										hasHitObstacle = true;
									}
								}
								else
								{
									hasHitObstacle = true;
								}
							}
							distance++;

						}
						if (spaceAround > bestCellSpace)
						{
							bestCellSpace = spaceAround;
							bestCell[0] = row;
							bestCell[1] = cell;
						}
					}

				}
			}
		}
	}

	cout << bestCell[0] << " " << bestCell[1] << endl;

	if (returnXAxis == true)
	{
		return bestCell[0];
	}
	else
	{
		return bestCell[1];
	}
	*/
	return 0;
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