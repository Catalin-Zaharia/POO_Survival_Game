#include "Game.h"
#include <iostream>

int main() {
	Game game;
	game.setParams(20, 10);//setParams(int unitsToBeSpawned, int itemsToBeSpawned, int roundsToBePlayed = 0, int mapSize=15)
	game.run();
}