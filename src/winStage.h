#ifndef WIN_STAGE_H
#define WIN_STAGE_H
#include "stage.h"

//the stage for the win
class WinStage : public Stage {
public:
	WinStage();
	Image* render(float time);
	void update(double seconds_elapsed);
};

#endif