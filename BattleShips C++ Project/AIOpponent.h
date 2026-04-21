#pragma once
#include "BattleShip.h"
#include "PlacementGrid.h"
#include "StrikingGrid.h"
class AIOpponent
{
	//A variable to store a duplicate of the AI's striking grid that it can build a heatmap from
private: int copiedGrid[10][10];

		 //A variable to store the built heatmap
private: int heatMap[10][10];

		 //The number of times the AI has rolled to hit a lower heatmap value
private: int nonOptimalHits = 0;

public: pair<int, int> ChooseRandomCell(PlacementGrid gridToPlaceOn, BattleShip shipToPlace, bool isVertical);

public: void UpdateHeatMap(StrikingGrid gridToStrike);

private: void GenerateHeatMap(StrikingGrid gridToStrike);

private: int SetHeatMapCell(int x, int y, int xOffset, int yOffset);

public: void DisplayHeatMap();

private: int GetRandomValue(int min, int max);

public: pair<int, int> GetBestCell();

private: void CopyGrid(Grid gridToCopy);

public: bool GetRandomRotation();
};

