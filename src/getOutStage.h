#ifndef GET_OUT_STAGE_H
#define GET_OUT_STAGE_H
#include "stage.h"

//the stage for the get out message
class GetOutStage : public Stage {
public:
	GetOutStage();
	Image* render(float time);
	void update(double seconds_elapsed);
};

#endif