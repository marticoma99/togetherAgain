#ifndef TUTORIAL_STAGE_H
#define TUTORIAL_STAGE_H
#include "stage.h"

//the stage for the tutorial
class TutorialStage : public Stage {
	int tutorialNum;
	//all the tutorial images
	Image* tutorial1 = new Image();
	Image* tutorial2 = new Image();
	Image* tutorial3 = new Image();
	Image* tutorial4 = new Image();
	Image* tutorial5 = new Image();
	Image* tutorial6 = new Image();
	Image* tutorial7 = new Image();
	//map the tutorial images to a string
	std::map<std::string, Image*> tutorialImages;
public:
	TutorialStage();
	Image* render(float time);
	void update(double seconds_elapsed);
	//init the tutorial
	void init();
};

#endif