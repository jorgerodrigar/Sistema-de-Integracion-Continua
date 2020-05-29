#include "GameState.h"
#include "Cursor.h"

Cursor* GameState::cursor = nullptr;

GameState::GameState()
{
}

GameState::~GameState()
{
	for (GameObject* it : stage) { 
		delete it; //delete de los objetos
	}

	if (cursor->getDependencias() == 0) { //si no hay nadie más con él, significa que se cierra el juego (no puede haber una pila de estados vacia y todos los estados comparten el cursor)
		delete cursor; //se borra
	}
	else {
		cursor->decrementaDependencias(); //si hay más gente compartiendolo, significa que se ha cerrado un estado superior. Se decrementa una dependencia del cursor.
	}
}

GameState::GameState(SDLApp * app) : app(app)
{
	addObserver(app->getSoundManager());
	if (cursor == nullptr) {
		cursor = new Cursor(app, app->getResources()->getImageTexture(Resources::Cursor), 15, 21); //singleton (?)
	}
	else {
		cursor->incrementaDependencias(); // para saber por cuantos estados es compartido
	}

	this->resetCursor();
}

//manda a los objetos del estado update
void GameState::update() {
	startTime = SDL_GetTicks();

	for (GameObject* it : stage) { 
		it->update(startTime); }

	// Calcula el tiempo del update del playState
	frameTime = SDL_GetTicks() - startTime;

	// Si no ha pasado el tiempo definido en FRAME_RATE, hay delay de lo que falta
	if (frameTime<FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
}

void GameState::handleEvent(SDL_Event &e) { //manda a los objetos del juego que detecten 
	
	it = stage.begin();

	listhasChanged = false;

	while (!listhasChanged && it != stage.end() && *it != nullptr) {
		(*it)->handleInput(0, e);
		if (!listhasChanged) { //si borras un elemento, solo puede afectar aquí (se borra a traves de los componentes HandleInput)
			it++; //si no borras nada se incrementa
		}
	}

	this->handleCursor(e);
}

void GameState::handleCursor(SDL_Event &e)
{
	if (cursor != nullptr) { cursor->handleInput(0, e); } //aparte del stage por si acaso fallos je
}

void GameState::renderCursor()
{
	if (cursor != nullptr) { cursor->render(0); } //aparte del stage por si acaso fallos je (again)
}

void GameState::render() {
	list<GameObject*>::const_reverse_iterator aux;
	for(aux = stage.rbegin(); aux != stage.rend(); aux++)
		(*aux)->render(0);

	this->renderCursor();;
}

void GameState::deleteElement(GameObject* o) {
	it = stage.begin();
	bool encontrado = false;
	while (it != stage.end() && !encontrado) {
		if (*it == o) {
			encontrado = true;
			it = stage.erase(it);
			listhasChanged = true;
		}
		else {
			it++;
		}
	}
	delete o;
}

Entity * GameState::getCursor() const
{
	return cursor;
}

void GameState::resetCursor()
{
	cursor->playAnim("Normal");
}

void GameState::playMusicScene(Resources::MusicId music, int volume) {
	if (!app->getSoundManager()->isAlreadySounding(music)) {
		playMusic(music);
		if (volume != 0)setMusicVolume(music, volume);
	}
}