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
		max = shipToPlace.GetXConstraints(1) + 1;
	}
	else
	{
		min = shipToPlace.GetYConstraints(0);
	    max = shipToPlace.GetYConstraints(1) + 1;
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
		max = shipToPlace.GetYConstraints(1) + 1;
	}
	else
	{
		min = shipToPlace.GetXConstraints(0);
		max = shipToPlace.GetXConstraints(1) + 1;
	}
	

	int randomY = GetRandomValue(min, max);

	return randomY;
}

int AIOpponent::GetBestCell(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical)
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

	int bestCell;
	for (int row = 0; row < 10; row++)
	{
		if (yConstraints[0] < row && row < yConstraints[1])
		{
			for (int cell = 0; cell < 10; cell++)
			{
				if (xConstraints[0] < cell && cell < xConstraints[1])
				{

				}
			}
		}
	}
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