#pragma once
#include "checkML.h"
#include "GameState.h"
#include "MainCharacter.h"
#include "ColisionableObject.h"
#include "ItemInventario.h"
#include "Entity.h"
#include "ImageRenderer.h"
#include "KeyboardComponent.h"
#include "MovementComponent.h"
#include "Resources.h"
#include "ShortCut.h"
#include "Scene.h"
#include "json.hpp"
#include "MainCharacter.h"
#include "puzzle1State.h"
#include "inGameMenu.h"


//estado de prueba, con Alena moviendose por pantalla
class PlayState: public GameState
{
private:
	MainCharacter* alena;//personaje del juego
	ObjectList* list;
	ShortCut* shortcut;
	std::list<GameObject*> collision;
	const Resources* resources = app->getResources();//recursos del juego
	vector<Scene*> scenes;
	int currentScene = 0;
	std::list<GameObject*> Zbuffer;
	int alenaZ;
	void sortZbuffer();
	bool enConversacion = false;
	vector<std::list<GameObject*>::iterator*> getOverlapping();
	void finishGame(SDLApp* app_);
	bool timeToClose = false;
public:
	PlayState() {}
	virtual ~PlayState();
	virtual void render();

	virtual void SetZBuffer();
	PlayState(SDLApp* app, bool load = false);
	MainCharacter* getMainPj() { return alena; }
	ShortCut* getShortCut(){ return shortcut; }
	void creaInventario() { app->getStateMachine()->pushState(new Inventory(app, list, this, shortcut)); }
	ObjectList* getList() { return list; };
	vector<Scene*> getScenes(){ return scenes; };
	void swapScene(int nextScene);
	Scene* getCurrentScene() { return scenes[currentScene]; }
	void pauseMenu() { app->getStateMachine()->pushState(new inGameMenu(app,app->getStateMachine()->currentState())); };
	int getNumCurrentScene() const { return this->currentScene; };
	virtual void handleEvent(SDL_Event &e);
	void setEnConversacion(bool conv);

	virtual void receive(Mensaje* msg);
};

