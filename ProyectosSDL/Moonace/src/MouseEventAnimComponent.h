#pragma once
#include "InputComponent.h"
class MouseEventAnimComponent :
	public InputComponent
{
private:
	SDL_EventType event_;
	string anim_; //animacion que se aplica cuando ocurre el evento "eve
	string defaultAnim_; //animacion si no ocurre nada
	int button_; //id del boton del raton, en caso de que haya

public:
	MouseEventAnimComponent() : anim_("") {};
	virtual ~MouseEventAnimComponent();
	MouseEventAnimComponent(SDL_EventType evento, string anim, string defaultAnim, int button = -1) : event_(evento), anim_(anim), defaultAnim_(defaultAnim), button_(button) {}
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};

