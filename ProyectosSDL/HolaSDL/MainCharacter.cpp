#include "MainCharacter.h"
#include "KeyboardComponent.h"


MainCharacter::MainCharacter(SDLApp* game, json& j, ObjectList* list, std::list<GameObject*>* coll, ShortCut* shorcut_, double vel, PlayState* playState):
	Entity(game), list(list), colisionables(coll), shortCut(shorcut_), mainState(playState) {
	// textura
	int n = j["mainPj"]["Texture"];
	_texture = app->getResources()->getImageTexture(Resources::ImageId(n));

	//animaciones
	addAnim("IdleRight", { 20,21,22,23 }, true, -1, 200);//parada a la derecha
	addAnim("IdleLeft", { 16,17,18,19 }, true, -1, 200);//parada a la izquierda
	addAnim("Left", { 0,1,2,3,4,5,6,7 });//caminar a la izquierda 
	addAnim("Right", { 8,9,10,11,12,13,14,15 });//caminar a la derecha
	addAnim("TakeObj", { 24,25,26,25,24 }, false, 0, 100);//coger objetos

	//componentes
	render = new AnimationRenderer(_texture, animations, 4, 7, 60, 144);
	
	this->addRenderComponent(render);//componente de pintado para que aparezca en pantalla
	movement = new MovementComponent(colisionables);//mueve al jugador cuando se usa el teclado
	keyboard = new KeyboardComponent(vel, SDLK_d, SDLK_a, SDLK_w, SDLK_s, SDLK_i, SDLK_ESCAPE, playState);//decide la direccion del jugador cuando se usa el teclado
	mouseMovement = new MouseMovement(colisionables, vel);
	switcher.addMode({ keyboard, movement, nullptr });//si se pulsa alguna tecla se activaran los componentes de teclado
	switcher.addMode({ mouseMovement, mouseMovement, nullptr });//si se pulsa el raton se activaran los componentes de raton
	switcher.setMode(0);

	//mensajes
	keyboard->addObserver(render);//teclado a animaciones
	keyboard->addObserver(&switcher);//teclado a switcher para no pisarse con mouse
	keyboard->addObserver(app->getSoundManager());//teclado a soundmanager
	mouseMovement->addObserver(render);//mouse a animaciones
	mouseMovement->addObserver(&switcher);//mouse a switcher para no pisarse con teclado
	mouseMovement->addObserver(app->getSoundManager());//mouse a soundmanager
	this->addObserver(render);

	// posicion y dimensiones
	this->setWidth(j["mainPj"]["w"]);//ancho, alto, posicion y textura
	this->setHeight(j["mainPj"]["h"]);
	this->setPosition(Vector2D(j["mainPj"]["x"], j["mainPj"]["y"]));

	// posicion y dimensiones
	this->setWidth(j["mainPj"]["w"]);//ancho, alto, posicion y textura
	this->setHeight(j["mainPj"]["h"]);
	this->setPosition(Vector2D(j["mainPj"]["x"], j["mainPj"]["y"]));
	this->pass_ = j["mainPj"]["pass_"];

	// items de inventario
	for (int i = 0; i < (int)j["mainPj"]["itemList"].size(); i++) {
		n = j["mainPj"]["itemList"][i]["Texture"];

		
		GameObject* item = new ItemInventario(app, 0, 0, 0, 0,
			j["mainPj"]["itemList"][i]["descripcion"], j["mainPj"]["itemList"][i]["tag"], 
			app->getResources()->getImageTexture(Resources::ImageId(n)));

		addInventoryObject(item);
		delete item;
	}
	
	if(!j["mainPj"]["actualScene"].is_null())
		this->currentScene = j["mainPj"]["actualScene"];
}

MainCharacter::~MainCharacter()
{
	if (switcher.isKeyBoardComponent()) {
		delete mouseMovement;
		mouseMovement = nullptr;
	}
	else {
		delete movement;
		movement = nullptr;
		delete keyboard;
		keyboard = nullptr;
	}
	_texture = nullptr;
	shortCut = nullptr;
	list = nullptr;
	colisionables = nullptr;
}

void MainCharacter::addInventoryObject(GameObject* o) {
	list->addItem(o); //a�ade un item al inventario
	shortCut->ini(list->getLength()-1, shortCut->getCoef());
}

void MainCharacter::saveToJson(json& j) {
	json aux;
	Entity::saveToJson(aux);

	for (int i = 0; i < list->getLength(); i++) {
		list->getItem(i)->saveToJson(aux["itemList"]);
	}

	aux["actualScene"] = this->getCurrentScene();

	aux["pass_"] = this->getPass();

	j["mainPj"].update(aux);
}

void MainCharacter::setPosIni() { setPosition(mainState->getCurrentScene()->getPosIni()); }

void MainCharacter::setTam() {
	Vector2D tam = mainState->getCurrentScene()->getPlayerTam();
	setWidth(tam.getX()); setHeight(tam.getY());
}
void MainCharacter::cleanKeys() { keyboard->cleanStacks(); }//llamado al entrar en una escena, limpia las pilas de teclas para evitar errores

void MainCharacter::receive(Mensaje* msg) {
	switch (msg->id_)
	{
	case Stop: {
		this->setVelocity(Vector2D(0.0, 0.0));
		this->getMouseComponent()->send(&Mensaje(MouseStop));
		this->getMouseComponent()->send(&Mensaje(CambioEscena));
		this->cleanKeys();
		this->getMouseComponent()->stopSound();
		break;
	}
	default:
		break;
	}
}
