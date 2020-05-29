#pragma once
#include <vector>
#include <SDL.h>
#include "checkML.h"
#include "GameStateMachine.h"
#include "Resources.h"
#include "SoundManager.h"

using namespace std;

class SDLApp
{
private:
	GameStateMachine* maquinaEstados;
	//-------------------------------SDL----------------------------

	SDL_Window* window;

	Resources* resources;
	SDL_Color color;
	SDL_Event event; //maneja eventos
	SDL_Renderer* renderer;
	GameState* introState_;
	int winWidth;
	int winHeight;

	bool exit = false;
	SoundManager soundManager;

	bool resourInitiated = false;

	void loadCarga();

	Entity* carga;

	Texture* tx;

	bool introDone_ = false;
public:
	SDLApp(int w, int h);
	~SDLApp() {};
	GameStateMachine* getStateMachine(); //return de la maquina de estados
	void update(); //invoca el update del currentState
	void render(); //invoca el render del currentState
	void handleEvent();
	void run() { while (!this->exit) { handleEvent(); update(); render(); } }
	void closeSDL();
	void setExit(bool b) { exit = b; }
	void updatePantallaCarga();
	SDL_Window* SDLApp::getWindow() const;
	SDL_Renderer* SDLApp::getRenderer() const;
	int SDLApp::getWindowWidth() const;
	int SDLApp::getWindowHeight() const;
	const Resources* getResources() const{ return resources; }
	void initResources() { if (!resourInitiated) { resources = new Resources(this); resourInitiated = true; } }
	void closeResources(){ delete resources; }
	void exitGame() { exit = true; };
	SoundManager* getSoundManager() { return &soundManager; }
	void setSoundManager(SoundManager s) { soundManager = s; };
	void introDone() { introDone_ = true; };
};

