#pragma once
#include "checkML.h"
#include "ClickeableGO.h"
#include "Puzzle.h"


class GOstates :
	public ClickeableGO, public Observer
{
public:
	GOstates(SDLApp* game, int x, int y, int w, int h, Texture* texture, GameState* state, json j, Observer* playState);
	virtual ~GOstates();
	void act();
	virtual void saveToJson(json& j);
	virtual void receive(Mensaje* msg);
	bool added = false;
private:
	Puzzle* state_;
	json jAux_; //saber los datos para guardarlos luego. Guardamos el objeto json que tiene tooodo dentro. Facilita maaazo las cosas
	bool done = false;
};
