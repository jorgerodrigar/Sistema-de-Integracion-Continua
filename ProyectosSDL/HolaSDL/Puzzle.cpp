#include "Puzzle.h"
#include <Tracker.h>

int Puzzle::numPuzzle = 0;

Puzzle::~Puzzle()
{
	delete timingSalida;
}

void Puzzle::handleEvent(SDL_Event& e)
{
	GameState::handleEvent(e);
	if (e.type == SDL_MOUSEBUTTONDOWN) { 
		// USABILIDAD
		ClickPuzzleEvent* trackEvent = Tracker::GetInstance().createClickPuzzleEvent();
		trackEvent->setParameters(numPuzzle_, { e.button.x, e.button.y }); // TO DO numPuzle (dos eventos click?)
		Tracker::GetInstance().trackEvent(trackEvent);
	}
}
