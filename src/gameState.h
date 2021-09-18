#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "image.h"
#include "mapworld.h"
#include "camera.h"
#include "sprite.h"
#include "framework.h"
#include "utils.h"
#include "game.h"

//class for storing all data of the game
class GameState {
public:
	Image spriteImage;
	Image world;
	MapWorld mapWorld;
	Camera camera = Camera(10, 2);
	Sprite player = Sprite(0, 0, 0, 0, 14, 18);
	double prevTime = 0;
	std::string msg;

	//variables for the player position and items
	enum { PLAYER_DOWN, PLAYER_RIGHT, PLAYER_LEFT, PLAYER_UP };
	int facing = PLAYER_DOWN; //where the character is looking
	bool isPlayerMoving = false;
	int numObjects = 0;
	int numKeys = 0;

	GameState();
	//init a new game
	void init();
	//update the laser to green or read
	void updateLaser(double seconds_elapsed);
	//update the number of recolected pieces
	bool updateObjects();
	//update the number of keys if the player is near a box
	void updateBox();
	//open a door if is possible
	bool openDoor();
};

#endif
