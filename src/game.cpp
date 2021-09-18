#include "game.h"
#include "utils.h"
#include "input.h"
#include "image.h"
#include "mapWorld.h"
#include "camera.h"
#include "sprite.h"
#include "playStage.h"
#include "menuStage.h"
#include "endStage.h"
#include "winStage.h"
#include "tutorialStage.h"
#include "getOutStage.h"
#include "titleStage.h"

#include <cmath>

Game* Game::instance = NULL;

Stage* Stage::currentStage = NULL;
std::map<std::string, Stage*> Stage::stages;


Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;

	//create all stages of the game
	Stage::currentStage = new TitleStage();
	new MenuStage();
	new PlayStage();
	new EndStage();
	new WinStage();
	new TutorialStage();
	new GetOutStage();

	enableAudio();//enable the audio
	synth.playSample("data/mainMusic.wav", 1, true);

}

void Game::render(void)
{
	//call the render of the current stage
	showFramebuffer(Stage::currentStage->render(time));
}

void Game::update(double seconds_elapsed)
{
	//call the update of the current stage
	Stage::currentStage->update(seconds_elapsed);
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
	}
}


void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onMouseMove(SDL_MouseMotionEvent event)
{
}

void Game::onMouseButtonDown(SDL_MouseButtonEvent event)
{
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
}


void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	window_width = width;
	window_height = height;
}

//sends the image to the framebuffer of the GPU
void Game::showFramebuffer(Image* img)
{
	static Image finalframe;

	if (window_width < img->width * 4 || window_height < img->height * 4)
	{
		finalframe = *img;
		finalframe.scale( window_width, window_height );
	}
	else
	{
		if (finalframe.width != window_width || finalframe.height != window_height)
		{
			finalframe.resize(window_width, window_height);
			finalframe.fill(Color::BLACK);
		}
		finalframe.drawImage(*img, (window_width - img->width * 4) * 0.5, (window_height - img->height * 4) * 0.5, img->width * 4, img->height * 4);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (1) //flip
	{
		glRasterPos2f(-1, 1);
		glPixelZoom(1, -1);
	}

	glDrawPixels(finalframe.width, finalframe.height, GL_RGBA, GL_UNSIGNED_BYTE, finalframe.pixels);
}

//AUDIO STUFF ********************

SDL_AudioSpec audio_spec;

void AudioCallback(void*  userdata,
	Uint8* stream,
	int    len)
{
	static double audio_time = 0;

	memset(stream, 0, len);//clear
	if (!Game::instance)
		return;

	Game::instance->onAudio((float*)stream, len / sizeof(float), audio_time, audio_spec);
	audio_time += len / (double)audio_spec.freq;
}

void Game::enableAudio()
{
	SDL_memset(&audio_spec, 0, sizeof(audio_spec)); /* or SDL_zero(want) */
	audio_spec.freq = 48000;
	audio_spec.format = AUDIO_F32;
	audio_spec.channels = 1;
	audio_spec.samples = 1024;
	audio_spec.callback = AudioCallback; /* you wrote this function elsewhere. */
	if (SDL_OpenAudio(&audio_spec, &audio_spec) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_PauseAudio(0);
}

void Game::onAudio(float *buffer, unsigned int len, double time, SDL_AudioSpec& audio_spec)
{
	//fill the audio buffer using our custom retro synth
	synth.generateAudio(buffer, len, audio_spec);
}
