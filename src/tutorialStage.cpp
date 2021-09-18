#include "tutorialStage.h"

//put all the images to the map with a simpleast name
TutorialStage::TutorialStage() : Stage::Stage("tutorialStage") {
	minifont.loadTGA("data/mini-font-black-4x6.tga");
	tutorial1->loadTGA("data/tutorial1.tga");
	tutorialImages["tut1"] = tutorial1;
	tutorial2->loadTGA("data/tutorial2.tga");
	tutorialImages["tut2"] = tutorial2;
	tutorial3->loadTGA("data/tutorial3.tga");
	tutorialImages["tut3"] = tutorial3;
	tutorial4->loadTGA("data/tutorial4.tga");
	tutorialImages["tut4"] = tutorial4;
	tutorial5->loadTGA("data/tutorial5.tga");
	tutorialImages["tut5"] = tutorial5;
	tutorial6->loadTGA("data/tutorial6.tga");
	tutorialImages["tut6"] = tutorial6;
	tutorial7->loadTGA("data/tutorial7.tga");
	tutorialImages["tut7"] = tutorial7;
	//set to the first tutorial image
	tutorialNum = 1;
	framebuffer = tutorialImages["tut1"];
}

//init the tutorial with the first image
void TutorialStage::init() {
	//set to the first tutorial image
	tutorialNum = 1;
	framebuffer = tutorialImages["tut1"];
}
//render the tutorial image
Image* TutorialStage::render(float time) {

	return framebuffer;
}

void TutorialStage::update(double seconds_elapsed) {

	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		//set to play stage
		if (tutorialNum == 7) {
			Game::instance->synth.playSample("data/click.wav", 2, false);
			stages["playStage"]->init();
			changeStage("playStage");
		}
		//set to next tutorial image
		else {
			Game::instance->synth.playSample("data/click.wav", 1, false);
			tutorialNum++;
			framebuffer = tutorialImages["tut" + toString(tutorialNum)];
		}
	}
}