#pragma once
#include <vector>
#include "items.h"
class Game
{
	int gameTime, unitsNum, itemsNum;
	std::vector<unit*> unitArray;
	std::vector<item*> itemArray;
	std::string map[20][20];
	int unitsToBeSpawned, itemsToBeSpawned, roundsToBePlayed;
protected:
	int mapSize;
public:
	friend class item;
	friend class unit;
	Game();
	Game(std::vector<unit*> unitArray, std::vector<item*> itemArray, int arrSize, int mapSize=15, int gameTime=0);
	Game(const Game& obj);
	~Game();

	void setSize(int mapSize);
	int Size();
	void setTime(int time);
	void shrink();

	void showMap();
	void run();
	void setParams(int unitsToBeSpawned, int itemsToBeSpawned, int roundsToBePlayed = 0, int mapSize=15);
	void spawnUnit(int type);
	void spawnUnits(int numberOfSpawns=1, int locX=0, int locY=0);
	void moveUnits();
	void spawnItem(int type);
	void spawnItems(int numberOfSpawns = 1, int locX = 0, int locY = 0);
	void pickItems();
	void combat();
	bool endCheck();
	void showWinner();
	void postGame();
};
