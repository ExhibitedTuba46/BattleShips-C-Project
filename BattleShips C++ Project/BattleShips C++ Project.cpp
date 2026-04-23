#include <iostream>
#include <Windows.h>
#include "Grid.h"
#include "BattleShip.h"
#include "StrikingGrid.h"
#include "PlacementGrid.h"
#include "AIOpponent.h"
using namespace std;

StrikingGrid playerStrikingGrid;
PlacementGrid playerPlacementGrid;
StrikingGrid aitrikingGrid;
PlacementGrid aiPlacementGrid;
AIOpponent opponent;
BattleShip playerDestroyer(2, 0, 9, 0, 8, 4, "Destroyer", false);
BattleShip playerSubmarine(3, 0, 9, 1, 8, 5, "Submarine", false);
BattleShip playerCruiser(3, 0, 9, 1, 8, 6, "Cruiser", false);
BattleShip playerBattleShip(4, 0, 9, 1, 7, 7, "BattleShip", false);
BattleShip playerCarrier(5, 0, 9, 2, 7, 8, "Aircraft Carrier", false);

BattleShip opponentDestroyer(2, 0, 9, 0, 8, 4, "Destroyer", true);
BattleShip opponentSubmarine(3, 0, 9, 1, 8, 5, "Submarine", true);
BattleShip opponentCruiser(3, 0, 9, 1, 8, 6, "Cruiser", true);
BattleShip opponentBattleShip(4, 0, 9, 1, 7, 7, "BattleShip", true);
BattleShip opponentCarrier(5, 0, 9, 2, 7, 8, "Aircraft Carrier", true);

int main()
{
	bool canStart = false;
	cout << "Welcome user!" << endl;
	cout << "Do you already know how to play Battleship?" << endl;
	cout << "'\033[33mY\033[0m' I'm all set!" << endl;
	cout << "'\033[33mN\033[0m' I would like a refresher." << endl;
	while (canStart == false)
	{
		if (GetKeyState('Y') & 0x8000)
		{
			system("cls");
			canStart = true;
		}
		else if (GetKeyState('N') & 0x8000)
		{
			system("cls");
			bool isDoneReading = false;
			cout << "BATTLESHIP RULES:" << endl;
			cout << endl;

			cout << "You and an opponent each have a game board that represents an ocean, and on this board you may place your ships however you please." << endl;
			cout << "There are five ships that you may place on your board: " << endl;
			cout << " *Destroyer - 2 cells" << endl;
			cout << " *Submarine - 3 cells" << endl;
			cout << " *Cruiser - 3 cells" << endl;
			cout << " *Battleship - 4 cells" << endl;
			cout << " *Aircraft Carrier - 5 cells" << endl;
			cout << endl;

			cout << "The goal of the game is to sink each of your opponents ships before they can sink yours." << endl;
			cout << "You may only strike one cell of the opponents board at a time, but you cannot see where their ships are placed, only the result of the strike." << endl;
			cout << "In this program you will be playing against an AI agent." << endl;
			cout << endl;

			cout << "Press '\033[33mEscape\033[0m' to continue." << endl;
			while (isDoneReading == false)
			{
				if (GetKeyState(VK_ESCAPE) & 0x8000)
				{
					system("cls");
					cout << "Welcome user!" << endl;
					cout << "Do you already know how to play Battleship?" << endl;
					cout << "'\033[33mY\033[0m' I'm all set!" << endl;
					cout << "'\033[33mN\033[0m' I would like a refresher." << endl;
					isDoneReading = true;
				}
			}
		}
	}


	bool hasGameFinished = false;

	bool rotation = opponent.GetRandomRotation();
	pair<int, int> shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentDestroyer, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentDestroyer, shipPlacement.first, shipPlacement.second, rotation);

	rotation = opponent.GetRandomRotation();
	shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentCruiser, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentCruiser, shipPlacement.first, shipPlacement.second, rotation);

	rotation = opponent.GetRandomRotation();
	shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentSubmarine, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentSubmarine, shipPlacement.first, shipPlacement.second, rotation);

	rotation = opponent.GetRandomRotation();
	shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentBattleShip, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentBattleShip, shipPlacement.first, shipPlacement.second, rotation);

	rotation = opponent.GetRandomRotation();
	shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentCarrier, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentCarrier, shipPlacement.first, shipPlacement.second, rotation);


	playerPlacementGrid.QueryBattleShipInput(&playerDestroyer);
	playerPlacementGrid.QueryBattleShipInput(&playerSubmarine);
	playerPlacementGrid.QueryBattleShipInput(&playerCruiser);
	playerPlacementGrid.QueryBattleShipInput(&playerBattleShip);
	playerPlacementGrid.QueryBattleShipInput(&playerCarrier);

	system("cls");
	cout << "AI placement phase:" << endl;
	Sleep(1000);
	cout << "AI is placing ships..." << endl;
	Sleep(1000);
	system("cls");

	while (hasGameFinished == false)
	{
		playerStrikingGrid.QuerySrikeInput(&aiPlacementGrid, playerPlacementGrid);
		if (aiPlacementGrid.GetShipsRemaining() == 0)
		{
			hasGameFinished = true;
			system("cls");
			cout << "You win!" << endl;

			cout << "Final boards:" << endl;
			cout << endl;
			cout << "AI's board:" << endl;
			aiPlacementGrid.DisplayGrid();

			cout << "Your board:" << endl;
			playerPlacementGrid.DisplayGrid();
			break;
		}

		Sleep(1000);

		cout << "AI's turn:" << endl;

		Sleep(1000);

		cout << "AI is thinking..." << endl;

		Sleep(1000);

		opponent.UpdateHeatMap(aitrikingGrid);
		pair<int, int> chosenCell = opponent.TargetHeatmapCell();
		aitrikingGrid.AIStrike(&playerPlacementGrid, chosenCell);

		if (playerPlacementGrid.GetShipsRemaining() == 0)
		{
			hasGameFinished = true;
			system("cls");
			cout << "The Ai wins!" << endl;

			cout << "Final boards:" << endl;
			cout << endl;
			cout << "Your board:" << endl;
			playerPlacementGrid.DisplayGrid();

			cout << "AI's board:" << endl;
			aiPlacementGrid.DisplayGrid();
			break;
		}
	}
	bool isExitKeyPressed = false;
	while (isExitKeyPressed == false)
	{
		cout << endl;
		cout << "Press '\033[33mEscape\033[0m' to exit the program." << endl;
		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			isExitKeyPressed = true;
			exit(0);
			return 0;
		}
	}
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
