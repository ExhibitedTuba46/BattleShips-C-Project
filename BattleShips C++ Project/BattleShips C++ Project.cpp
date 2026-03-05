#include <iostream>
#include "Grid.h"
#include "BattleShip.h"
#include "StrikingGrid.h"
#include "PlacementGrid.h"
using namespace std;

StrikingGrid playerStrikingGrid;
PlacementGrid playerPlacementGrid;
BattleShip destroyer(2, 0, 9, 0, 8);
BattleShip submarine(3, 0, 9, 1, 8);
BattleShip cruiser(3, 0, 9, 1, 8);
BattleShip battleShip(4, 0, 9, 1, 7);
BattleShip carrier(5, 0, 9, 2, 7);

int main()
{
	/*
	playerPlacementGrid.QueryBattleShipInput(destroyer);
	playerPlacementGrid.QueryBattleShipInput(submarine);
	playerPlacementGrid.QueryBattleShipInput(cruiser);
	playerPlacementGrid.QueryBattleShipInput(battleShip);
	*/
	playerPlacementGrid.QueryBattleShipInput(carrier);
	playerPlacementGrid.DisplayGrid();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
