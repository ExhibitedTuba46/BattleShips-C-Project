#pragma once
#include "Grid.h"
#include "PlacementGrid.h"
class StrikingGrid : public Grid
{
public: void DisplayGrid() override;

public: void AIStrike(PlacementGrid gridToStrike, pair<int, int> chosenCell);

public: void QuerySrikeInput(PlacementGrid gridToStrike);
};
	
