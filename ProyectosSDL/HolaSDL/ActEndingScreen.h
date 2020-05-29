#pragma once
#include "GameState.h"
#include "sdl_includes.h"
#include "Font.h"
//#include "Texture.h"

class ActEndingScreen :
	public GameState
{
private:
	const unsigned int TAMANYO_TITLE = 70;
	const unsigned int TAMANYO_HEADER = 50;

	float initTime;
	float MaxTime;

	const SDL_Color col = { 0, 169, 0, 1 };
	int act;
	std::string headers;
	Texture fuente;
	std::string title;
	Font* fnt;
	Font* fnts;

	void endState(SDLApp* app_);

public:
	ActEndingScreen(SDLApp* app, int acto, string _header = "",float time = 5000);
	~ActEndingScreen();

	virtual void render();
	virtual void update();
};

