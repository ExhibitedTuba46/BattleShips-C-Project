#pragma once
#include "Grid.h"
#include "PlacementGrid.h"
class StrikingGrid : public Grid
{
	//The coordinates of the previously struck cell
private: int x = 0;
private: int y = 0;

public: void DisplayGrid() override;

public: void AIStrike(PlacementGrid* pointerToStrike, pair<int, int> chosenCell);

public: void QuerySrikeInput(PlacementGrid* pointerToStrike, PlacementGrid playerPlacementGrid);
};
	
