#pragma once
#include "Grid.h"
#include "StrikingGrid.h"
#include "PlacementGrid.h"
class StrikingGrid : public Grid
{
public: void DisplayGrid() override;

public: void QuerySrikeInput(PlacementGrid gridToStrike);
};
	
