#include "IntroState.h"
#include "Entity.h"
#include "TransitionScreen.h"

IntroState::IntroState()
{
}


IntroState::~IntroState()
{
}

void IntroState::checkAnimDone()
{
	if (done_) { app->getStateMachine()->popState(false); app->getStateMachine()->pushState(new TransitionScreen(app, prevState, 1000)); app->introDone(); }
}

IntroState::IntroState(SDLApp * app) : GameState(app), logo(new Entity(app))
{
	prevState = app->getStateMachine()->currentState();

	logo->addAnim("Intro", { 24,24,24,0,1,2,3,4,5,6,7,8,9,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,13,14,15,16,17,18,19,20,21,22,23,24,24,24,24,24,24,25,26,27,28,29,30,31,32,33,34,35,35,35,35,35,35,35,35,35,35,35,35,35,35,36,37,38,39,40,41,42,43,44,24,24,24,24,24,24,24,24,24,24,24,24,24,24 }, false, -1, 100);
	logo->addRenderComponent(new AnimationRenderer(app->getResources()->getImageTexture(Resources::LogosAnim), logo->getAnimations(), 6, 8, 640, 480, this));

	logo->setWidth(480);
	logo->setHeight(271);
	logo->setPosition(Vector2D(app->getWindowWidth()/2 - logo->getWidth()/2, app->getWindowHeight()/2 - logo->getHeight()/2));

	stage.push_back(logo);
}

void IntroState::update()
{
	GameState::update();
	checkAnimDone();
}

void IntroState::handleEvent(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_RETURN) {
			done_ = true;
		}
	}
}

void IntroState::receive(Mensaje * msg)
{
	switch (msg->id_) {
	case ANIM_DONE:
		done_ = true;
		break;
		//more cases
	}
}

