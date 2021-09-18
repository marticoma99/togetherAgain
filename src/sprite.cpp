#include "sprite.h"

Sprite::Sprite(double rX, double rY, double wX, double wY, int pX, int pY) {
	realX = rX;
	realY = rY;
	windowX = wX;
	windowY = wY;
	pixelsX = pX;
	pixelsY = pY;
}
//set the sprite image
void Sprite::setImage(Image* i) {
	image = i;
}
//update the cell position
void Sprite::updateCell(int pixelsPerCell) {
	cellX = floor((realX + pixelsX / 2) / pixelsPerCell);
	cellY = floor((realY + pixelsY / 2 + 6) / pixelsPerCell);
}

//update the player position x to go left
void Sprite::updatePosXLeft(Camera* camera, float playerSpeed, double seconds_elapsed, MapWorld* mapWorld) {
	double prevX = realX;
	double auxX = realX - seconds_elapsed * playerSpeed * mapWorld->cellSize;
	realX = auxX;
	updateCell(mapWorld->cellSize);
	//only move if the cell is permited to move
	if (!mapWorld->isCellPermited(cellX, cellY)) {
		realX = prevX;
		updateCell(mapWorld->cellSize);
	}
	else camera->updateCameraX(camera->getX() - seconds_elapsed * playerSpeed);
}

//update the player position x to go right
void Sprite::updatePosXRight(Camera* camera, float playerSpeed, double seconds_elapsed, MapWorld* mapWorld) {
	double prevX = realX;
	double auxX = realX + seconds_elapsed * playerSpeed * mapWorld->cellSize;
	realX = auxX;
	updateCell(mapWorld->cellSize);
	//only move if the cell is permited to move
	if (!mapWorld->isCellPermited(cellX, cellY)) {
		realX = prevX;
		updateCell(mapWorld->cellSize);
	}
	else camera->updateCameraX(camera->getX() + seconds_elapsed * playerSpeed);
}

//update the player position y to go down
void Sprite::updatePosYDown(Camera* camera, float playerSpeed, double seconds_elapsed, MapWorld* mapWorld) {
	double prevY = realY;
	double auxY = realY + seconds_elapsed * playerSpeed * mapWorld->cellSize;
	realY = auxY;
	updateCell(mapWorld->cellSize);
	//only move if the cell is permited to move
	if (!mapWorld->isCellPermited(cellX, cellY)) {
		realY = prevY;
		updateCell(mapWorld->cellSize);
	}
	else camera->updateCameraY(camera->getY() + seconds_elapsed * playerSpeed);
}

//update the player position y to go up
void Sprite::updatePosYUp(Camera* camera, float playerSpeed, double seconds_elapsed, MapWorld* mapWorld) {
	
	double prevY = realY;
	double auxY = realY - seconds_elapsed * playerSpeed * mapWorld->cellSize;
	realY = auxY;
	updateCell(mapWorld->cellSize);
	//only move if the cell is permited to move
	if (!mapWorld->isCellPermited(cellX, cellY)) {
		realY = prevY;
		updateCell(mapWorld->cellSize);
	}
	else camera->updateCameraY(camera->getY() - seconds_elapsed * playerSpeed);
	
}
//set player position according to the camera position and an offset
void Sprite::setPlayerPos(double camX, double camY, double offSetX, double offSetY) {

	realX = camX * 16 + 80 - pixelsX / 2 + offSetX;
	realY = camY * 16 + 64 - pixelsY / 2 + offSetY;

	windowX = 80 - pixelsX / 2 + offSetX;
	windowY = 64 - pixelsY / 2 + offSetY;
}