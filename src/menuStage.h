#ifndef MENU_STAGE_H
#define MENU_STAGE_H
#include "stage.h"

//the stage for the menu
class MenuStage : public Stage {
public:
	MenuStage();
	Image* render(float time);
	void update(double seconds_elapsed);
};

#endif