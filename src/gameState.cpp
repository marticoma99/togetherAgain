#include "gameState.h"


GameState::GameState() {

	spriteImage.loadTGA("data/spritesheet.tga");
	world.loadTGA("data/worldsheet.tga");
	world.flipY();

	mapWorld.setWorld(&world);
	if (mapWorld.loadMap("data/worldMap.map")) std::cout << " + Map loaded: /worldMap1.map";
	else std::cout << " + Error loading map: /worldMap1.map";

	msg = "OBJECTS RECOLECTED: " + toString(numObjects) + "/4";
	player.setPlayerPos(camera.getX(), camera.getY(), 0, 0);
	player.updateCell(mapWorld.cellSize);
}

//initialize a new game
void GameState::init() {
	//reinitialize the map
	mapWorld.setWorld(&world);
	if (mapWorld.loadMap("data/worldMap.map")) std::cout << " + Map loaded: /worldMap1.map";
	else std::cout << " + Error loading map: /worldMap1.map";

	//init camera position
	camera.updateCamera(10, 2);

	//set the variables to 0
	prevTime = 0;
	numObjects = 0;
	numKeys = 0;

	msg = "OBJECTS RECOLECTED: " + toString(numObjects) + "/4";

	//init player position
	player.setPlayerPos(camera.getX(), camera.getY(), 0, 0);
	player.updateCell(mapWorld.cellSize);
}

//update the laser green or read
void GameState::updateLaser(double seconds_elapsed) {
	//every 1.5 seconds the laser change its state
	if (prevTime > 1.5) {
		mapWorld.updateLaser();
		Game::instance->synth.playSample("data/laser.wav", 0.5, false);
		prevTime = seconds_elapsed;
	}
}

//if the player is near a object they can collect it
bool GameState::updateObjects() {
	if (mapWorld.serchRound(20,player.cellX, player.cellY)) {
		numObjects++;
		mapWorld.changeCell(player.cellX, player.cellY, 20, 1, 1);
		msg = "OBJECTS RECOLECTED: " + toString(numObjects) + "/4";
		Game::instance->synth.playSample("data/grab.wav", 2, false);
		//if the player have the four pieces
		if (numObjects == 4) {
			return true;
		}
	}
	return false;
}

//update the number of keys if the player is neara box
void GameState::updateBox() {
	if (mapWorld.isOnBox(player.cellX, player.cellY)) {
		mapWorld.changeCell(player.cellX, player.cellY, 34, 40, 1);
		Game::instance->synth.playSample("data/keys.wav", 3, false);
		numKeys++;
	}
}

//open a door if the player is near one door and have a key if is necesary
bool GameState::openDoor() {
	if (mapWorld.isOnOpenableDoor(player.cellX, player.cellY)) {
		mapWorld.changeCell(player.cellX, player.cellY, 19, 1, 2);
		mapWorld.changeCell(player.cellX, player.cellY, 33, 1, 2);
		mapWorld.changeCell(player.cellX, player.cellY, 31, 3, 2);
		Game::instance->synth.playSample("data/openDoor1.wav", 8, false);
	}
	if (mapWorld.isOnClosedDoor(player.cellX, player.cellY)) {
		if (numKeys > 0) {
			mapWorld.changeCell(player.cellX, player.cellY, 18, 1, 2);
			mapWorld.changeCell(player.cellX, player.cellY, 32, 3, 2);
			numKeys--;
			Game::instance->synth.playSample("data/openDoor1.wav", 8, false);
		}
		//the player is trying to open a closed door without a key
		else {
			return true;
		}
	}
	//the door have been opened
	return false;
}