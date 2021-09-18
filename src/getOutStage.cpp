#include "getOutStage.h"

//image with the get out message
GetOutStage::GetOutStage() : Stage::Stage("getOutStage") {
	framebuffer->loadTGA("data/getOut.tga");
}

//render the image with the get out message
Image* GetOutStage::render(float time) {

	return framebuffer;
}
//returns to the game stage
void GetOutStage::update(double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		Game::instance->synth.playSample("data/click.wav", 1, false);
		changeStage("playStage");
	}
}