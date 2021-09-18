#ifndef MAPWORLD_H
#define MAPWORLD_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "framework.h"
#include "image.h"

struct mapCell {
	unsigned int type;
};

struct mapHeader {
	int w;
	int h;
	unsigned char bytes;
	unsigned char extra[7];
};

//Class MapWorld: to store the information of a map
class MapWorld {
	Image* world;
public:
	int width;
	int height;
	int cellSize = 16;
	int cellColum = 16;
	int cellsPerWindow = 10;
	mapCell* cells;
	bool isLaserOn = true;

	MapWorld();

	//set the cell x,y the position num
	void setNumPos(int x, int y, int num);
	//return the num of the cell x,y
	mapCell getNumPos(int x, int y);

	//paint the map to the framebuffer
	void paintMap(Image& framebuffer, double x, double y);
	//set the image of the tiles
	void setWorld(Image* w);
	//load the map to the cells
	bool loadMap(const char* fileName);

	//true if the cell x,y is a valid position for moving
	bool isCellPermited(int x, int y);
	//put the laser on or off
	void updateLaser();
	//true if the player is in a cell that have a collectable object
	bool isOnObject(int x, int y);
	//true if the player is in a cell that have a active laser o a pressure plate
	bool isCellFin(int x, int y);
	//change the posotion if the laser is on or off
	int laserPos(int pos, int i, int j);
	//true if the player is near a box
	bool isOnBox(int x, int y);
	//true if the player is near openable door
	bool isOnOpenableDoor(int x, int y);
	//true if the player is near a closed door
	bool isOnClosedDoor(int x, int y);
	//search around pos x,y for the cell type num
	bool serchRound(int num, int x, int y);
	//change the cell type actBlock to newBlock around a range of the position x,y
	void changeCell(int x, int y, int actBlock, int newBlock, int range);
	//true if is an exterior cell
	bool isCellWin(int x, int y);
};

#endif