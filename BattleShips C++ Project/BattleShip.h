#pragma once
class BattleShip
{
	//The smallest ship in BattleShips is only 2 cells in size, so the parameters for that ship will be the default
protected: int sizeInCells = 2;
protected: int xConstraints[2] = { 0, 9 };
protected: int yConstraints[2] = { 0, 8 };
protected: int shipIdentifier = 4;
private: int timesHit = 0;

	   //Getter methods to enforce encapsulation
public: int GetSizeInCells();
public: int GetXConstraints(int index);
public: int GetYConstraints(int index);
public: int GetShipIdentifier();

public: void DamageShip();

public: int ShipSize(int x, int cellNumber);

public: BattleShip(int sizeOfShip, int xConstraint1, int xConstraint2, int yConstraint1, int yConstraint2, int identifier);
};

