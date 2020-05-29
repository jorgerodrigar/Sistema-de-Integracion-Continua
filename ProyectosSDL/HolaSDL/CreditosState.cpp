#include "CreditosState.h"
#include "Entity.h"
#include "ImageRenderer.h"
#include "VerticalMovement.h"
#include "TransitionScreen.h"
#include "AnimationRenderer.h"
#include "MouseEventAnimComponent.h"

void CreditosState::endCredits()
{
	if (creditos->getPosition().getY() + creditos->getHeight() + END_DELAY < 0) {
		app->getStateMachine()->popState(false);
		app->getStateMachine()->pushState(new TransitionScreen(app, app->getStateMachine()->currentState(), 1500));
		delete this;
	}
}

CreditosState::CreditosState()
{
}

CreditosState::~CreditosState()
{
	if (creditos != nullptr) { delete creditos; creditos = nullptr; }
	if (exit_ != nullptr) { delete exit_; exit_ = nullptr; }
	stage.clear();
}

CreditosState::CreditosState(SDLApp * app) : GameState(app) {
	creditos = new Entity(app);

	creditos->setHeight(1280);
	creditos->setWidth(1280);
	creditos->setPosition(Vector2D(app->getWindowWidth()/2 - creditos->getWidth()/2, app->getWindowHeight()));

	creditos->addRenderComponent(new ImageRenderer(app->getResources()->getImageTexture(Resources::Creditos)));
	creditos->addPhysicsComponent(new VerticalMovement());

	stage.push_back(creditos);

	exitFun_ = [this]() mutable { this->exit(this->app); };

	createButtons();
	playMusic(Resources::MainThemePro);
}

void CreditosState::update()
{
	GameState::update();

	endCredits();
}


void CreditosState::createButtons() {

	exit_ = new Boton(app, "exitButton", exitFun_, Resources::BotonSonido);
	exit_->setWidth(65); exit_->setHeight(65); exit_->setPosition(Vector2D(40, 40));
	exit_->addAnim("Stop", { 0,0,1,1,2,2,3,3,4,4,5,5,6,6 }, true, -1, 100);
	exit_->addAnim("Feedback", { 7 }, true, -1, 100);
	exit_->addAnim("Pressed", { 8 }, true, -1, 100);
	exit_->addRenderComponent(new AnimationRenderer(app->getResources()->getImageTexture(Resources::SalirControles), exit_->getAnimations(), 3, 3, 65, 65));
	exit_->addInputComponent(new MouseEventAnimComponent(SDL_MOUSEBUTTONDOWN, "Pressed", "Stop", SDL_BUTTON_LEFT));
	exit_->addInputComponent(new MouseEventAnimComponent(SDL_MOUSEMOTION, "Feedback", "Stop"));
	exit_->setAnimated(true);

	stage.push_back(exit_);
}

void CreditosState::exit(SDLApp* app) {

	app->getStateMachine()->popState(); 
	app->getStateMachine()->pushState(new TransitionScreen(app, app->getStateMachine()->currentState(), 500));

}