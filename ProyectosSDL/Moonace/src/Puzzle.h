#pragma once
#include "GameState.h"
#include "GOUnlockeable.h"
#include "TransitionScreen.h"
#include "GOTimer.h"

class Puzzle: public GameState
{
protected:
	vector<GOUnlockeable*> unlockeables;
	GOTimer* timingSalida;
	bool hasWon = false;
	bool swapScene;
	virtual void win() {
		hasWon = true;
		timingSalida->startTimer();
	}
	
	bool guarro = false;

	int numPuzzle_;

public:
	Puzzle() {};
	Puzzle(SDLApp* app, int id = -4, bool swapScene = false) : GameState(app), id(id), swapScene(swapScene) { function<void()> fun = [this]()mutable {this->winner(); }; timingSalida = new GOTimer(800, fun); this->stage.push_back(timingSalida); 
	numPuzzle_ = numPuzzle; numPuzzle++; };
	~Puzzle();

	static int numPuzzle;

	virtual void handleEvent(SDL_Event& e);

	int id;
	virtual void searchId() {
		if (id != -4) {
			GameState* _previousState = app->getStateMachine()->currentState(); //nos devuelve siempre el anterior antes de pushearlo
			list<GameObject*>::iterator aux;
			for (aux = _previousState->getStage()->begin(); aux != _previousState->getStage()->end(); aux++) {
				if ((*aux)->_id == id) unlockeables.push_back(static_cast<GOUnlockeable*>((*aux))); //este static no se me ocurre otra forma de identificar el tipo
			}
		}
	};

	virtual void unlockObjects() {
		vector<GOUnlockeable*>::iterator it;
		for (it = unlockeables.begin(); it != unlockeables.end(); it++) (*it)->secondAct();
	};

	virtual void exit() {
		app->getStateMachine()->popState(false);
		app->getStateMachine()->pushState(new TransitionScreen(app, app->getStateMachine()->currentState(), 1000));
	}

	virtual void enter() {
		app->getStateMachine()->pushState(new TransitionScreen(app, app->getStateMachine()->currentState(), 1000));
	}

	void winner() {
		playSoundEffect(Resources::CorrectPuzle);
		app->getStateMachine()->popState(false);
		unlockObjects();
		app->getStateMachine()->currentState()->SetZBuffer();
		send(&SwapScenePuzzle(swapScene));
		app->getStateMachine()->pushState(new TransitionScreen(app, app->getStateMachine()->currentState(), 1000));
	}
};

