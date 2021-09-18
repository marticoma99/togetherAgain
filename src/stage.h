#ifndef STAGE_H
#define STAGE_H
#include "game.h"
#include "utils.h"
#include "input.h"
#include "image.h"
#include "mapWorld.h"
#include "camera.h"
#include "sprite.h"
#include "framework.h"

//the basic class for the stages
class Stage {
public:
	//variables that can use all stages
	Image minifont;
	Color bgcolor = Color(255, 255, 255);
	Image* framebuffer = new Image(160, 120);

	//map to all stages
	static std::map<std::string, Stage*> stages;
	//pointer to the current stage
	static Stage* currentStage;

	//constructor, save the stage into the map
	Stage(const char* name) { stages[name] = this; }
	//change the current stage
	static void changeStage(const char* name) { currentStage = stages[name]; }

	//init (only used in some stages)
	virtual void init() {};
	//render for all stages
	virtual Image* render(float time) = 0;
	//update for all stages
	virtual void update(double seconds_elapsed) {};
};

#endif