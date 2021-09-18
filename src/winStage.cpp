#include "winStage.h"

//load the win image
WinStage::WinStage() : Stage::Stage("winStage") {
	framebuffer->loadTGA("data/winImage.tga");
	minifont.loadTGA("data/mini-font-black-4x6.tga");
}

//render the win image
Image* WinStage::render(float time) {
	return framebuffer;
}

//go to the start menu
void WinStage::update(double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		Game::instance->synth.playSample("data/click.wav", 1, false);
		changeStage("menuStage");
	}
}