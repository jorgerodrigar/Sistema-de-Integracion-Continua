#pragma once
#include "checkML.h"
#include <SDL.h>
#include "GameObject.h"

class ComponenteClickeable
{
private:
	bool firstClickDown = false;
public:
	ComponenteClickeable();
	virtual ~ComponenteClickeable();

	bool handleInput(GameObject* o, const SDL_Event& event);//Obtiene el rect del GO
	bool handleInput(SDL_Rect* rect, const SDL_Event& event);//recive un rectangulo destino
};

