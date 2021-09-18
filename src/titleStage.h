#ifndef TITLE_STAGE_H
#define TITLE_STAGE_H
#include "stage.h"

//the stage for the tittle screen
class TitleStage : public Stage {
public:
	TitleStage();
	Image* render(float time);
	void update(double seconds_elapsed);
};

#endif