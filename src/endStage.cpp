#include "endStage.h"

//load the game over image
EndStage::EndStage() : Stage::Stage("endStage") {
	framebuffer->loadTGA("data/gameOverImage.tga");
}

//render the game over image
Image* EndStage::render(float time) {
	return framebuffer;
}

//return to the start meu
void EndStage::update(double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		Game::instance->synth.playSample("data/click.wav", 1, false);
		changeStage("menuStage");
	}
}