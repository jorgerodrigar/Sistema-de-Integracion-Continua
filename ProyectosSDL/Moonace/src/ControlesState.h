#pragma once
#include "GameState.h"
#include "Entity.h"
#include "AnimationRenderer.h"
#include "Boton.h"
#include "TransitionScreen.h"

class ControlesState :
	public GameState
{
private:
	void readFromJson();
	Boton* botonSalir;
	function<void()> exitFun_;
public:
	ControlesState();
	virtual ~ControlesState();
	ControlesState(SDLApp* app) : GameState(app) { exitFun_ = [app]() mutable { app->getStateMachine()->popState(); app->getStateMachine()->pushState(new TransitionScreen(app, app->getStateMachine()->currentState(), 500)); };  this->readFromJson(); };
	static vector<Entity*> entities;
};

