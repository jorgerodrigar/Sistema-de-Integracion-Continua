#include "ActEndingScreen.h"
#include "SDLApp.h"
#include "TransitionScreen.h"


void ActEndingScreen::endState(SDLApp * app_)
{
	app_->getStateMachine()->popState();
	app_->getStateMachine()->pushState(new TransitionScreen(app_, app_->getStateMachine()->currentState(), 600));
}

ActEndingScreen::ActEndingScreen(SDLApp * app, int acto, string _header, float time):GameState(app),act(acto),headers(_header), MaxTime(time)
{
	initTime = SDL_GetTicks();
	title = "Acto: " + to_string(act);
	fnt = new Font("..//images/Dialogos/Moonace-Regular.ttf", TAMANYO_TITLE);
	fnts = new Font("..//images/Dialogos/Moonace-Regular.ttf", TAMANYO_HEADER);
	fuente = Texture(app->getRenderer(), title, *fnt, col);
}

ActEndingScreen::~ActEndingScreen()
{
	delete fnt;
	delete fnts;
}

void ActEndingScreen::update()
{
	float currentTime = SDL_GetTicks();
	if (initTime + MaxTime < currentTime) {
		endState(app);
	}
}

void ActEndingScreen::render()
{
	fuente.loadFromText(app->getRenderer(), title, *fnt, col);
	fuente.render(app->getRenderer(), app->getWindowWidth() / 2 - fuente.getWidth() / 2, app->getWindowHeight() / 4);

	fuente.loadFromText(app->getRenderer(), headers, *fnts, col);
	fuente.render(app->getRenderer(), app->getWindowWidth()/2 - fuente.getWidth()/2, 2 * app->getWindowHeight() / 5);
}

