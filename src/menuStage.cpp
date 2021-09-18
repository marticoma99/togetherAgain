#include "menuStage.h"

//load the menu image
MenuStage::MenuStage() : Stage::Stage("menuStage") {
	framebuffer->loadTGA("data/menuImage.tga");
}
//render the image of the menu
Image* MenuStage::render(float time) {
	
	return framebuffer;
}

void MenuStage::update(double seconds_elapsed) {
	//go to play stage
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		Game::instance->synth.playSample("data/click.wav", 1, false);
		stages["playStage"]->init();
		changeStage("playStage");
	}
	//go to tutorial stage
	if (Input::wasKeyPressed(SDL_SCANCODE_X)) //if key X was pressed
	{
		Game::instance->synth.playSample("data/click.wav", 1, false);
		stages["tutorialStage"]->init();
		changeStage("tutorialStage");
	}
}