#include "TransitionScreen.h"
#include "SDLApp.h"


TransitionScreen::TransitionScreen(SDLApp * app, GameState* previousState , Uint32 timeLimit) :GameState(app),MaxTime(timeLimit),prevState(previousState)
{
	timeStart = SDL_GetTicks();
	txt = app->getResources()->getImageTexture(Resources::Transicion);
	a = 255;
	x = 1;
	alphaTime = (x*MaxTime) / 255;
	completed = false;
}

TransitionScreen::~TransitionScreen()
{
}

void TransitionScreen::update()
{
	time = SDL_GetTicks();
	while (a >0 && timeStart + alphaTime < time) {
		alphaTime = (x*MaxTime) / 255;
		x++;
		a--;
	}
	
	if (a == 0)
		app->getStateMachine()->popState();
}

void TransitionScreen::render()
{
	if (prevState != nullptr)
		prevState->render();
	txt->changeAlpha(a);
	SDL_Rect rct = RECT(0, 0, app->getWindowWidth(), app->getWindowHeight());
	txt->render(app->getRenderer(),rct,nullptr);
	
}
