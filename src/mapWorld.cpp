#include "mapWorld.h"
#include "utils.h"

MapWorld::MapWorld() {
	world = NULL;
}

//set de cell x,y the value num
void MapWorld::setNumPos(int x, int y, int num) {
	cells[y * width + x].type = num;
}

//return the number of the cell x,y
mapCell MapWorld::getNumPos(int x, int y) {
	return cells[y * width + x];
}

//paint the map to the frammbufer (x,y is the top right cell to be painted)
void MapWorld::paintMap(Image& framebuffer, double x, double y) {
	int widthAux = width;
	int heightAux = height;
	//if the camera is out of the map
	if (floor(x) >= width - cellsPerWindow || floor(y) >= height - cellsPerWindow) {
		widthAux = cellsPerWindow + 1 + floor(x);
		heightAux = cellsPerWindow + 1 + floor(y);
	}
	for (int i = floor(x); i <= widthAux; i++) {
		for (int j = floor(y); j <= heightAux; j++) {
			//the cells out the map are painted with the tail 8
			if (i < 0 || j < 0 || i >= width || j >= height) {
				framebuffer.drawImage(*world, (i - x) * cellSize, (j - y) * cellSize, 8 * cellSize, 0, cellSize, cellSize);
			}
			else {
				int pos = cells[j * width + i].type;
				pos = laserPos(pos, i, j);
				
				//calculate the position of the cell to be painted
				int posX = (pos % cellColum) * cellSize;
				int posY = floor(pos / cellColum) * cellSize;
				if ((i - x) < -1 || (i - x) * cellSize >= framebuffer.width || (j - y) < -1 || (j - y) * cellSize >= framebuffer.height) continue;
				framebuffer.drawImage(*world, (i - x) * cellSize, (j - y) * cellSize, posX, posY, cellSize, cellSize);
			}
		}
	}
}

//set the image of the world
void MapWorld::setWorld(Image* w) {
	world = w;
}

//change between the two lasers on and off
int MapWorld::laserPos(int pos, int i, int j) {
	//horitzontal laser
	if (pos == 17 || pos == 22) {
		if (isLaserOn) {
			pos = 17;
			setNumPos(i, j, 17);
		}
		else {
			pos = 22;
			setNumPos(i, j, 22);
		}
	}
	//vertical laser
	else if (pos == 23 || pos == 24) {
		if (isLaserOn) {
			pos = 23;
			setNumPos(i, j, 23);
		}
		else {
			pos = 24;
			setNumPos(i, j, 24);
		}
	}
	return pos;
}

//load the map to the program
bool MapWorld::loadMap(const char* fileName) {
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) //not found
	{
		return false;
	}
	mapHeader header;
	fread(&header, sizeof(mapHeader), 1, file);

	assert(header.bytes == 1);

	unsigned char* auxCells = new unsigned char[header.w * header.h];
	fread(auxCells, header.bytes, header.w * header.h, file);

	width = header.w;
	height = header.h;

	delete[] cells;
	cells = new mapCell[width* height];

	//put the information of the cells into the array of cells
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			setNumPos(i, j, auxCells[j * width + i]);
		}
	}
	delete[] auxCells;
	return true;
}

//find if the cell the player is moving is a valid position
bool MapWorld::isCellPermited(int x, int y) {
	int aux = getNumPos(x, y).type;
	if (x < 0 || y < 0 || x >= width || y >= height || aux ==2 || (aux > 3 && aux < 16 && aux != 8) ||
		(aux > 24 && aux <= 33) || (aux <= 21 && aux >=18) || (aux >= 34 && aux <= 40)) return false;
	return true;
}

//update the laser
void MapWorld::updateLaser() {
	if (isLaserOn) isLaserOn = false;
	else isLaserOn = true;
}

//true if the cell is near of a piece
bool MapWorld::isOnObject(int x, int y) {
	if (getNumPos(x, y).type == 20) return true;
	return false;
}

//true if the cell is near a box
bool MapWorld::isOnBox(int x, int y) {
	if (serchRound(34, x, y)) return true;
	return false;
}

//true if the cell is near an openable door
bool MapWorld::isOnOpenableDoor(int x, int y) {
	if (serchRound(19, x, y) || serchRound(33, x, y) || serchRound(31, x, y)) return true;
	return false;
}

//change around cell x,y for cell type num
bool MapWorld::serchRound(int num, int x, int y) {
	if (getNumPos(x, y).type == num || getNumPos(x + 1, y).type == num || getNumPos(x - 1, y).type == num ||
		getNumPos(x, y + 1).type == num || getNumPos(x, y - 1).type == num || getNumPos(x - 1, y + 1).type == num ||
		getNumPos(x + 1, y + 1).type == num || getNumPos(x - 1, y - 1).type == num || getNumPos(x + 1, y - 1).type == num)
		return true;
	return false;
}

//true if the player is near from closed door
bool MapWorld::isOnClosedDoor(int x, int y) {
	if (serchRound(32, x, y) || serchRound(18, x, y)) return true;
	return false;
}

//true if the player is in a laser or ina pressure plate
bool MapWorld::isCellFin(int x, int y) {
	int aux = getNumPos(x, y).type;
	if (aux == 17 || aux == 16 || aux == 24) {
		return true;
	} 
	return false;
}

//true if the cell x,y is an exterior cell (type 8)
bool MapWorld::isCellWin(int x, int y) {
	if (getNumPos(x, y).type == 8)return true;
	else return false;
}

//change the cell type actBlock to newBlock around a range of the position x,y
void MapWorld::changeCell(int x, int y, int actBlock, int newBlock, int range) {
	//all the cells of the range
	for (int i = -range; i <= range; i++) {
		for (int j = -range; j <= range; j++) {
			if (getNumPos(x + i, y + j).type == actBlock) {
				setNumPos(x + i, y + j, newBlock);
			}
		}
	}
}