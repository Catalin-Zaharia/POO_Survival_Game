#include "Game.h"
#include <cstdlib> 
#include <iostream>
#include <ctime> 

Game::Game()
{
	this->gameTime = 0;
	this->mapSize = 20;
	this->unitsNum = 0;
	this->itemsNum = 0;
	for (int i = 0; i < this->mapSize; i++) {
		for (int j = 0; j < this->mapSize; j++) {
			map[i][j] = "-";
		}
	}
	this->roundsToBePlayed = 0;
	this->unitsToBeSpawned = 0;
	this->itemsToBeSpawned = 0;
}

Game::Game(std::vector<unit*> unitArray, std::vector<item*> itemArray, int arrSize, int mapSize, int gameTime)
{
	this->gameTime = gameTime;
	this->mapSize = mapSize;
	this->unitArray = unitArray;
	this->unitsNum = arrSize;
	this->itemArray = itemArray;
	for (int i = 0; i < this->mapSize; i++) {
		for (int j = 0; j < this->mapSize; j++) {
			map[i][j] = "-";
		}
	}
	this->roundsToBePlayed = 0;
	this->unitsToBeSpawned = 0;
	this->itemsToBeSpawned = 0;
}

Game::Game(const Game& obj)
{
	this->gameTime = obj.gameTime;
	this->mapSize = obj.mapSize;
	this->unitArray = obj.unitArray;
	this->unitsNum = obj.unitsNum;
	this->itemArray = obj.itemArray;
	for (int i = 0; i < this->mapSize; i++) {
		for (int j = 0; j < this->mapSize; j++) {
			map[i][j] = "-";
		}
	}
	this->roundsToBePlayed = obj.roundsToBePlayed;
	this->unitsToBeSpawned = obj.unitsToBeSpawned;
	this->itemsToBeSpawned = obj.itemsToBeSpawned;
}

Game::~Game()
{

}

void Game::setSize(int mapSize)
{
	this->mapSize = mapSize;
}

int Game::Size()
{
	return this->mapSize;
}

void Game::setTime(int time)
{
	this->gameTime = time;
}

void Game::shrink()
{
	for (int i = 0; i < this->unitsNum; i++) {
		int x = getLocation(this->unitArray[i]).locX;
		int y = getLocation(this->unitArray[i]).locY;
		if (x==1 or x==this->mapSize or y==1 or y==this->mapSize)
		{
			this->unitArray[i]->remove();
		}
		else
		{
			setLocation(this->unitArray[i], x - 1, y - 1);
		}
	}
	for (int i = 0; i < this->itemsNum; i++) {
		int x = getLocation(this->itemArray[i]).locX;
		int y = getLocation(this->itemArray[i]).locY;
		if (x == 1 or x == this->mapSize or y == 1 or y == this->mapSize)
		{
			this->itemArray[i]->remove();
		}
		else
		{
			setLocation(this->itemArray[i], x - 1, y - 1);
		}
	}
	this->setSize(this->mapSize - 2);
}

void Game::showMap()
{
	for (int i = 0; i < this->mapSize; i++) {
		for (int j = 0; j < this->mapSize; j++) {
			map[i][j] = '-';
		}
	}
	for (int i = 0; i < this->itemsNum; i++) {
		int x = getLocation(this->itemArray[i]).locX;
		int y = getLocation(this->itemArray[i]).locY;
		if (x>=0 and y>=0)
		map[x][y] = 'i';
	}
	for (int i = 0; i < this->unitsNum; i++) {
		int x = getLocation(this->unitArray[i]).locX;
		int y = getLocation(this->unitArray[i]).locY;
		if (x >= 0 and y >= 0)
		map[x][y] = 'u';
	}
	for (int i = 0; i < this->mapSize; i++) {
		std::cout << '\n';
		for (int j = 0; j < this->mapSize; j++) {
			std::cout << map[i][j] << " ";
		}
	}
	std::cout << "\n\n";
}

void Game::run()
{
	srand(unsigned(time(0)));
	spawnUnits(this->unitsToBeSpawned);
	spawnItems(this->itemsToBeSpawned);
	bool endFlag = false;
	while (!endFlag)
	{
		this->gameTime++;
		std::cout << "Round " << this->gameTime << " begins" << "\n";
		showMap();
		if (this->gameTime % 3 == 1 and this->gameTime != 1) {
			this->shrink();
		}
		moveUnits();
		pickItems();
		combat();
		endFlag = endCheck();
		std::cout << "\n\n";
	}
	showMap();
	showWinner();
	postGame();
}

void Game::setParams(int unitsToBeSpawned, int itemsToBeSpawned, int roundsToBePlayed, int mapSize)
{
	this->roundsToBePlayed = roundsToBePlayed;
	this->itemsToBeSpawned = itemsToBeSpawned;
	this->unitsToBeSpawned = unitsToBeSpawned;
	this->mapSize = mapSize;
}

void Game::spawnUnit(int type)
{
	switch (type) {
	case 1:
		this->unitArray.push_back(new fighter);
		break;
	case 2:
		this->unitArray.push_back(new thief);
		break;
	case 3:
		this->unitArray.push_back(new archer);
		break;
	}
}

void Game::spawnUnits(int numberOfSpawns, int locX, int locY)
{
	if (this->unitsNum + numberOfSpawns <= 30)
	{
		bool randCheck = false;
		if (locX == 0 and locY == 0)
			randCheck = true;
		int i = this->unitsNum;
		this->unitsNum += numberOfSpawns;
		for (i; i < this->unitsNum; i++) {
			this->spawnUnit(randNum(1,3));
			this->unitArray[i]->setName();
			if (randCheck) {
				setLocation(this->unitArray[i], randNum(0, this->mapSize-1), randNum(0, this->mapSize-1));
			}
			else {
				setLocation(this->unitArray[i], locX, locY);
			}
		}
	}
}

void Game::moveUnits()
{
	for (int i = 0; i < this->unitsNum; i++) 
	{
		if (this->unitArray[i]->isAlive()) {
			this->unitArray[i]->move();
			int x = getLocation(this->unitArray[i]).locX;
			int y = getLocation(this->unitArray[i]).locY;
			x = minim(x, this->mapSize - 1);
			y = minim(y, this->mapSize - 1);
			x = maxim(x, 0);
			y = maxim(y, 0);
			setLocation(this->unitArray[i], x, y);
			std::cout << this->unitArray[i]->Name() << " moved to " << x + 1 << ":" << y + 1 << '\n';
		}
	}
}

void Game::spawnItem(int type)
{
	switch (type) {
	case 1:
		this->itemArray.push_back(new healthPotion);
		break;
	case 2:
		this->itemArray.push_back(new damagePotion);
		break;
	case 3:
		this->itemArray.push_back(new speedPotion);
		break;
	}
}

void Game::spawnItems(int numberOfSpawns, int locX, int locY)
{
	if (this->itemsNum + numberOfSpawns <= 35)
	{
		bool randCheck = false;
		if (locX == 0 and locY == 0)
			randCheck = true;
		int i = this->itemsNum;
		this->itemsNum += numberOfSpawns;
		for (i; i < this->itemsNum; i++) {
			this->spawnItem(randNum(1, 3));
			this->itemArray[i]->setName();
			if (randCheck) {
				setLocation(this->itemArray[i], randNum(0, this->mapSize-1), randNum(0, this->mapSize-1));
			}
			else {
				setLocation(this->itemArray[i], locX, locY);
			}
		}
	}
}

void Game::pickItems()
{
	for (int i = 0; i < this->itemsNum; i++) {
		for (int j = 0; j < this->unitsNum; j++) {
			if (getLocation(this->unitArray[j]) == getLocation(this->itemArray[i])) {
				this->itemArray[i]->effect(this->unitArray[j]);
			}
		}
	}
	return;
}

void Game::combat()
{
	for (int i = 0; i < this->unitsNum-1; i++){
		for (int j = i+1; j < this->unitsNum; j++) {
			if (getLocation(this->unitArray[i]) == getLocation(this->unitArray[j])) {
				this->unitArray[i]->engage(*this->unitArray[j]);
			}
		}
	}
}

bool Game::endCheck()
{
	if (this->gameTime == this->roundsToBePlayed)
		return true;
	int offset = 0;
	for (int i = 0; i < this->unitsNum; i++) {
		this->unitArray[i - offset] = this->unitArray[i];
		if (!this->unitArray[i]->isAlive()) {
			offset++;
		}
	}
	this->unitsNum -= offset;
	if (this->unitsNum > 1)
		return false;
	return true;
}

void Game::showWinner()
{
	for (int i = 0; i < this->unitsNum; i++) {
		if (this->unitArray[i]->isAlive()) {
			std::cout << this->unitArray[i]->Name() << " wins ";
		}
	}
}

void Game::postGame()
{
	for (int i = 0; i < this->unitsNum; i++) {
		this->unitArray[i]->setUsing(true);
	}
}

