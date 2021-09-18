#include "titleStage.h"

//load the tittle image
TitleStage::TitleStage() : Stage::Stage("titleStage") {
	framebuffer->loadTGA("data/titleScreen.tga");
}
//render the image of the tittle screen
Image* TitleStage::render(float time) {

	return framebuffer;
}

void TitleStage::update(double seconds_elapsed) {
	//go to menu stage
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		Game::instance->synth.playSample("data/click.wav", 1, false);
		changeStage("menuStage");
	}
}