#pragma once
#include "GameState.h"
#include "sdl_includes.h"
#include "Texture.h"

class TransitionScreen :
	public GameState
{
public:
	TransitionScreen(){};
	TransitionScreen(SDLApp* app,GameState* previousState = nullptr, Uint32 timeLimit = 1500);
	~TransitionScreen();
	virtual void update();
	virtual void render();

private:
	bool completed;
	GameState * prevState;
	Uint32 time,timeStart, MaxTime;
	double alphaTime;
	Uint8 a , x;
	Texture* txt;
};

