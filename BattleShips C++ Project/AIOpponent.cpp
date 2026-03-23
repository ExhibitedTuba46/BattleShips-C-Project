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

auto AIOpponent::ChooseRandomCell(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical)
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

	bool isCellValid = false;

	int randomX;
	int randomY;

	while (false)
	{
		randomX = GetRandomValue(minX, maxX);
		randomY = GetRandomValue(minY, maxY);

		for (int cell = 0; cell < (shipToPlace.GetSizeInCells()); cell++)
		{
			if (isVertical == false)
			{
				if (copiedGrid[randomX][shipToPlace.ShipSize(randomY, cell)] != 2 && copiedGrid[randomX][shipToPlace.ShipSize(randomY, cell)] != 0)
				{
					isCellValid = true;
				}
			}
			else
			{
				if (copiedGrid[shipToPlace.ShipSize(randomX, cell)][randomY] != 2 && copiedGrid[shipToPlace.ShipSize(randomX, cell)][randomY] != 0)
				{
					isCellValid = true;
				}
			}
		}
	}

	struct randomCell
	{
		int x;
		int y;
	};
	return randomCell{ randomX, randomY };
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