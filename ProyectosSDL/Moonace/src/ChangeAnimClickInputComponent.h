#pragma once
#include "InputComponent.h"
class ChangeAnimClickInputComponent :
	public InputComponent
{
private:
	SDL_EventType event_;
	string anim1_; //animacion que se aplica cuando ocurre el evento "eve
	string anim2_; //animacion si no ocurre nada
	int button_; //id del boton del raton, en caso de que haya
public:
	ChangeAnimClickInputComponent();
	ChangeAnimClickInputComponent(SDL_EventType evento, string anim, string defaultAnim, int button);
	virtual ~ChangeAnimClickInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
	inline void setAnim1(string a) { anim1_ = a; };
	inline void setAnim2(string a) { anim2_ = a; };
};

