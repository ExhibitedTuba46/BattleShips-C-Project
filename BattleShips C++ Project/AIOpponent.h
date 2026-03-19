#pragma once
#include "BattleShip.h"
#include "PlacementGrid.h"
class AIOpponent
{
protected: int copiedGrid[10][10];

public: int ChooseRandomStartingCellX(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical);
public: int ChooseRandomStartingCellY(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical);

protected: int GetRandomValue(int min, int max);

public: int GetBestCell(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical, bool returnXAxis);

protected: void CopyGrid(PlacementGrid gridToCopy);

public: bool GetRandomRotation();
};

