#pragma once
#include "GameState.h"
#include "Boton.h"

class CreditosState :
	public GameState
{
private:
	Entity* creditos;
	Boton* exit_;
	void endCredits();
	const int END_DELAY = 50;
	function<void()> exitFun_;
	void createButtons();
	void exit(SDLApp* app);
public:
	CreditosState();
	virtual ~CreditosState();
	CreditosState(SDLApp* app);
	virtual void update();
};

