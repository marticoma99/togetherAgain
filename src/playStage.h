#ifndef PLAY_STAGE_H
#define PLAY_STAGE_H
#include "stage.h"

//the class for play Stage
class PlayStage: public Stage{
public:
	PlayStage();
	//init a new game
	void init();
	Image* render(float time);
	void update(double seconds_elapsed);
};

#endif