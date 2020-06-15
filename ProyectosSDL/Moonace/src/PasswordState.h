#pragma once
#include "Puzzle.h"
#include "GOTimer.h"
#include "Boton.h"
#include "MouseEventAnimComponent.h"

class PasswordState :
	public Puzzle
{
private:
	const SDL_Color colorFuente = { 0, 169, 0, 1 };
	bool checking = false;
	const string password_; //contrasenya a averiguar
	string userPass_;
	bool checkPassword();
	void resetPassword();
	void reset();
	Font* f;
	unsigned int i = 0;
	ImageRenderer img;
	Entity* fondo = nullptr;
	GOTimer* timerFail;
	Boton* botonSalir;
	function<void()> exitFun_;
	MouseEventAnimComponent press;

	int posFontX_;
	int posFontY_;

public:
	PasswordState();
	PasswordState(SDLApp* app, int PosFontX, int PosFontY,string password = "hanzomain", int id = -4, int txt = -1, bool swap = false);
	virtual ~PasswordState();
	virtual void handleEvent(SDL_Event &e);
	virtual void render();

};

