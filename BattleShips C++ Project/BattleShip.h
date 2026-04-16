#pragma once
#include <string>
using namespace std;

class BattleShip
{
	//The smallest ship in BattleShips is only 2 cells in size, so the parameters for that ship will be the default
private: int sizeInCells = 2;
private: int xConstraints[2] = { 0, 9 };
private: int yConstraints[2] = { 0, 8 };
private: string shipName = "Ship";
private: int shipIdentifier = 4;
private: int timesHit = 0;
private: bool isAI = false;
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

