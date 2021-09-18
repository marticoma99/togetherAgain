#include "playStage.h"
#include "gameState.h"

GameState gameState;

//load the font
PlayStage::PlayStage() : Stage::Stage("playStage"){	
	minifont.loadTGA("data/mini-font-black-4x6.tga");
}

//init a new game
void PlayStage::init() {
	
	gameState.init();
}

Image* PlayStage::render(float time) {
	
	//paint the map to the framebuffer
	gameState.mapWorld.paintMap(*framebuffer, gameState.camera.getX(), gameState.camera.getY());

	//paint de player moving
	if (gameState.isPlayerMoving) {
		framebuffer->drawImage(gameState.spriteImage, gameState.player.windowX, gameState.player.windowY,
			Area((int(time * 10) % 4) * gameState.player.pixelsX, gameState.facing * gameState.player.pixelsY, gameState.player.pixelsX, gameState.player.pixelsY));
	}//paint de player static
	else framebuffer->drawImage(gameState.spriteImage, gameState.player.windowX, gameState.player.windowY,
		Area(0, gameState.facing * gameState.player.pixelsY, gameState.player.pixelsX, gameState.player.pixelsY));

		
	framebuffer->drawText(gameState.msg, 4, 4, minifont, 4, 6);	//draws some text using a bitmap font in an image (assuming every char is 4x6)
	
	//send image to screen
	return framebuffer;
}
void PlayStage::update(double seconds_elapsed) {
	float playerSpeed = 3.5;
	gameState.isPlayerMoving = true;

	//update the laser
	gameState.prevTime += seconds_elapsed;

	gameState.updateLaser(seconds_elapsed);

	//change the player and the camera position to go up
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		gameState.player.updatePosYUp(&gameState.camera, playerSpeed, seconds_elapsed, &gameState.mapWorld);
		gameState.facing = gameState.PLAYER_UP;
		if ((Game::instance->frame % 40) == 0)Game::instance->synth.playSample("data/steps.wav", 5, false);
	}
	//change the player and the camera position to go down
	else if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		gameState.player.updatePosYDown(&gameState.camera, playerSpeed, seconds_elapsed, &gameState.mapWorld);
		gameState.facing = gameState.PLAYER_DOWN;
		if ((Game::instance->frame % 40) == 0)Game::instance->synth.playSample("data/steps.wav", 5, false);
	}
	//change the player and the camera position to go right
	else if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key right
	{
		gameState.player.updatePosXRight(&gameState.camera, playerSpeed, seconds_elapsed, &gameState.mapWorld);
		gameState.facing = gameState.PLAYER_RIGHT;
		if ((Game::instance->frame % 40) == 0)Game::instance->synth.playSample("data/steps.wav", 5, false);
	}
	//change the player and the camera position to go left
	else if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key left
	{
		gameState.player.updatePosXLeft(&gameState.camera, playerSpeed, seconds_elapsed, &gameState.mapWorld);
		gameState.facing = gameState.PLAYER_LEFT;
		if ((Game::instance->frame % 40) == 0)Game::instance->synth.playSample("data/steps.wav", 5, false);
	}
	//el player no se a movido
	else gameState.isPlayerMoving = false;
	
	//if the player is on a end game cell
	if (gameState.mapWorld.isCellFin(gameState.player.cellX, gameState.player.cellY)) {
		Game::instance->synth.playSample("data/gameOver.wav", 4, false);
		changeStage("endStage");

	}
	//if the player is on a win cell
	if (gameState.mapWorld.isCellWin(gameState.player.cellX, gameState.player.cellY)&&gameState.numObjects==4) {
		Game::instance->synth.playSample("data/win.wav", 4, false);
		changeStage("winStage");
	}
	
	if (Input::isKeyPressed(SDL_SCANCODE_Z)) {
		//if the player have the four pieces
		if (gameState.updateObjects()) {
			changeStage("getOutStage");
		}
		gameState.updateBox();
	}
	if (Input::isKeyPressed(SDL_SCANCODE_X)) {
		//if the door is closed
		if (gameState.openDoor()) {
			gameState.msg = "THIS DOOR SEEMS TO BE CLOSED";
		}
	}
}