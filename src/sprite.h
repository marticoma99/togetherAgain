#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <iostream>
#include "image.h"
#include "camera.h"
#include "mapWorld.h"

//class sprite that represents the player
class Sprite {
public:
	double realX, realY; //position of the player int the map
	double windowX, windowY; //position of the player in the window
	int pixelsX, pixelsY; //size of the player
	int cellX, cellY; //cell where the player is
	Image* image;

	Sprite(double rX, double rY, double wX, double wY, int pX, int pY);
	//set the player image
	void setImage(Image* i);
	//update the cell where is the player
	void updateCell(int pixelsPerCell);

	//update the position of the player for the four directions
	void updatePosXLeft(Camera * camera, float playerSpeed, double seconds_elapsed, MapWorld* mapWorld);
	void updatePosXRight(Camera* camera, float playerSpeed, double seconds_elapsed, MapWorld* mapWorld);
	void updatePosYDown(Camera* camera, float playerSpeed, double seconds_elapsed, MapWorld* mapWorld);
	void updatePosYUp(Camera* camera, float playerSpeed, double seconds_elapsed, MapWorld* mapWorld);

	//update the position of the sprite according to the camera position
	void setPlayerPos(double camX, double camY, double offSetX, double offSetY);
};

#endif