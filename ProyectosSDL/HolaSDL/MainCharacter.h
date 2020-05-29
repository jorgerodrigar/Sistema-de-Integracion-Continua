#pragma once
#include "checkML.h"
#include "Entity.h"
#include "ImageRenderer.h"
#include "AnimationRenderer.h"
#include "MovementComponent.h"
#include "ItemInventario.h" // Para cargar 
#include "ShortCut.h"
#include "MouseMovement.h"
#include "ComponentSwitcher.h"

class PlayState;
class KeyboardComponent;
class MainCharacter:
	public Entity
{
public:
	MainCharacter() {};
	MainCharacter(SDLApp* game, json& j, ObjectList* list, std::list<GameObject*>* coll, ShortCut* shortcut_, double vel, PlayState* playState);
	virtual ~MainCharacter();
	void addInventoryObject(GameObject* o);
	string getCurrentTag() { return this->currentTag; };
	ShortCut* getShortcut() { return shortCut; }
	void setCurrenTag(string newTag) { this->currentTag = newTag; };
	void marcaOut() { shortCut->marcaOut(); }
	ObjectList* getList() { return list; };
	virtual void saveToJson(json& j);
	virtual void handleInput(Uint32 time, const SDL_Event& event) { switcher.handleInput(time, event); Entity::handleInput(time, event); }
	void clearCollisions() { colisionables->clear(); };
	void setNewCollision(GameObject* o) { colisionables->push_back(o); }
	void collisionListWasModified() { mouseMovement->generaMatriz(this); } //m�todo auxiliar, es llamado cuando sales de una escena, para generar de nuevo la matriz de colisionables
	MouseMovement* getMouseComponent() const { return mouseMovement; }
	//establece el tamaño de la escena para el mouse y las colisiones del movimiento
	void setSceneTam(double w, double h, double x, double y) {
		mouseMovement->setSceneTam(w, h, x, y);
		movement->setSceneTam(w, h, x, y);
	}
	int getPass() const { return pass_; };
	void activePass() { pass_++; };
	inline int getCurrentScene() const { return this->currentScene; };
	inline void setCurrentScene(int nScene_) { this->currentScene = nScene_; };
	void setPosIni();
	void setTam();
	void cleanKeys();
	//tamaño por defecto de alena (se establece al entrar en cada escena si esta no tiene un tamaño especifico)
	const double defaultW = 84;
	const double defaultH = 201.6;
	virtual void receive(Mensaje* msg);
private:
	Texture * _texture;
	ShortCut * shortCut;
	string currentTag = "";
	AnimationRenderer* render;
	KeyboardComponent* keyboard;
	MovementComponent* movement;
	MouseMovement* mouseMovement;
	ObjectList* list;
	std::list<GameObject*>* colisionables;
	ComponentSwitcher switcher = ComponentSwitcher(app, this);
	int currentScene = 0; //para guardar la ultima escena
	int pass_ = 0;
	PlayState* mainState; //puntero para acceder al estado
};

