#pragma once
#include "GameState.h"
#include "AnimationRenderer.h"

class IntroState :
	public GameState
{
private:
	Entity* logo;
	bool done_ = false;
	void checkAnimDone();
	GameState* prevState = nullptr;
public:
	IntroState();
	virtual ~IntroState();
	IntroState(SDLApp* app);
	virtual void receive(Mensaje* msg);
	virtual void update();
	virtual void handleEvent(SDL_Event &e);
};

