#pragma once
#include <string>
using namespace std;

class BattleShip
{
	//The smallest ship in BattleShips is only 2 cells in size, so the parameters for that ship will be the default
	
	//The size of the ship in cells
private: int sizeInCells = 2;
	   //The constraints of the ship on the grid, thsi stops it from being placed over the edge of the grid and causing errors
private: int xConstraints[2] = { 0, 9 };
private: int yConstraints[2] = { 0, 8 };
	   //The name of this ship to be displayed
private: string shipName = "Ship";
	   //The identifier this ship uses to be identified on a placement grid
private: int shipIdentifier = 4;
	   //Times this ship has been hit
private: int timesHit = 0;
	   //Whether this ship was placed by the AI
private: bool isAI = false;
	   //Whether this ship has sunk
private: bool hasSunk = false;


	   //Getter methods to enforce encapsulation
public: int GetSizeInCells();
public: int GetXConstraints(int index);
public: int GetYConstraints(int index);
public: int GetShipIdentifier();
public: string GetShipName();
public: bool GetShipStatus();

public: void DamageShip();

public: int ShipSize(int x, int cellNumber);

public: BattleShip(int sizeOfShip, int xConstraint1, int xConstraint2, int yConstraint1, int yConstraint2, int identifier, string name, bool _isAI);
};

