#pragma once
#include "BattleShip.h"
#include "PlacementGrid.h"
#include "StrikingGrid.h"
class AIOpponent
{
protected: int copiedGrid[10][10];

protected: int heatMap[10][10];

public: pair<int, int> ChooseRandomCell(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical);

public: void UpdateHeatMap(StrikingGrid gridToStrike);

protected: void GenerateHeatMap(StrikingGrid gridToStrike);

protected: int SetHeatMapCell(int x, int y, int xOffset, int yOffset);

public: void DisplayHeatMap();

protected: int GetRandomValue(int min, int max);

public: int GetBestCell(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical, bool returnXAxis);

protected: void CopyGrid(Grid gridToCopy);

public: bool GetRandomRotation();
};

