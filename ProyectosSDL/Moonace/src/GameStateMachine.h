#pragma once
#include "checkML.h"
#include "GameState.h"
#include <stack>

class GameStateMachine
{
private:
	stack <GameState*> states;
	list <GameState*> actualStates; //lista auxiliar que sirve para ver si un estado esta dentro de la pila a la hora de borrar
	void deleteAndPopState();
public:
	GameStateMachine();
	~GameStateMachine();
	void popState(bool b = true);
	void pushState(GameState* newState);
	GameState* currentState();
	bool checkElement(GameState* state);
	void libera();
};

