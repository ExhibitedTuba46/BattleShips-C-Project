#include "AIOpponent.h"
#include <iostream>
#include <random>
#include "BattleShip.h"
#include "PlacementGrid.h"
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

int AIOpponent::ChooseRandomStartingCellX(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical)
{
	int min;
	int max;

	if (isVertical == false)
	{
		min = shipToPlace.GetXConstraints(0);
		max = shipToPlace.GetXConstraints(1);
	}
	else
	{
		min = shipToPlace.GetYConstraints(0);
		max = shipToPlace.GetYConstraints(1);
	}

	int randomX = GetRandomValue(min, max);

	return randomX;
}

int AIOpponent::ChooseRandomStartingCellY(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical)
{
	int min;
	int max;

	if (isVertical == false)
	{
		min = shipToPlace.GetYConstraints(0);
		max = shipToPlace.GetYConstraints(1);
	}
	else
	{
		min = shipToPlace.GetXConstraints(0);
		max = shipToPlace.GetXConstraints(1);
	}


	int randomY = GetRandomValue(min, max);

	return randomY;
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
	int partitions[5][4];
	int min = 0;
	int max = 9;

	int partitionY = GetRandomValue(min, max);

	partitions[0][0] = min;
	partitions[0][1] = min;
	partitions[0][2] = max;
	partitions[0][3] = partitionY - 1;

	partitions[0][0] = min;
	partitions[0][1] = partitionY + 1;
	partitions[0][2] = max;
	partitions[0][3] = max;

	
		
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
}

void AIOpponent::CopyGrid(PlacementGrid gridToCopy)
{
	for (int row = 0; row < 10; row++)
	{
		for (int cell = 0; cell < 10; cell++)
		{
			copiedGrid[row][cell] = gridToCopy.GetCell(row, cell);
		}
	}
}