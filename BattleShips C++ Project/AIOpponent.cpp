#include "AIOpponent.h"
#include <iostream>
#include <random>
#include "BattleShip.h"
#include "PlacementGrid.h"
using namespace std;

int AIOpponent::ChooseRandomStartingCellX(PlacementGrid gridToPlaceOn, BattleShip shipToPlace)
{
	CopyGrid(gridToPlaceOn);

	int min = 0;
	int max = 10;

	int randomX = -1;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min, max);
	randomX = distrib(gen);
	
	cout << randomX;
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