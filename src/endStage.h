#ifndef END_STAGE_H
#define END_STAGE_H
#include "stage.h"

//the stage for the Game Over
class EndStage : public Stage {
public:
	EndStage();
	Image* render(float time);
	void update(double seconds_elapsed);
};

#endif