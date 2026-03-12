#pragma once
#include "BattleShip.h"
#include "PlacementGrid.h"
class AIOpponent
{
protected: int copiedGrid[10][10];

public: int ChooseRandomStartingCellX(PlacementGrid gridToPlaceOn, BattleShip shipToPlace);

protected: void CopyGrid(PlacementGrid gridToCopy);
};

