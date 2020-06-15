#include "SDLApp.h"
#include "PlayState.h"
#include "Inventory.h"
#include "LightsOut.h"
#include "MainMenuState.h"
#include "PasswordState.h"
#include "TransitionScreen.h"
#include "IntroState.h"
#include "CreditosState.h"
#include <Tracker.h>


SDLApp::SDLApp(int w, int h): winWidth(w), winHeight(h)
{
	SessionStartEvent* startEvent = Tracker::GetInstance().createSessionStartEvent();
	Tracker::GetInstance().trackEvent(startEvent);

	srand(time(NULL)); //inicia la seed del random para que genere distintos numeros siempre que compilemos
	window = nullptr;
	renderer = nullptr;
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	//Inicialización del sistema y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Moonace", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	// SDL Mixer (Music, Sound, etc)
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	loadCarga();
	initResources();
	SDL_ShowCursor(0);
	soundManager = SoundManager(this);
	maquinaEstados = new GameStateMachine();

	maquinaEstados->pushState(new MainMenuState(this));

	introState_ = new IntroState(this);
	maquinaEstados->pushState(introState_);
}

void SDLApp::handleEvent() {
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT && introDone_)
			exit = true;

		maquinaEstados->currentState()->handleEvent(event); //invoca el handleEvent del currentState
	}
}

void SDLApp::update() {
	maquinaEstados->currentState()->update();
	soundManager.update();//actualizamos soundManager para que actualice la cola de soundEffects
}

void SDLApp::render() {
	SDL_RenderClear(renderer); 
	maquinaEstados->currentState()->render(); 
	SDL_RenderPresent(renderer);
}

void SDLApp::closeSDL() {
	delete maquinaEstados; maquinaEstados = nullptr;
	delete resources; resources = nullptr;
	delete carga; carga = nullptr;
	delete tx; tx = nullptr;
	if (introState_ != nullptr) { delete introState_; introState_ = nullptr; }
	SDL_DestroyRenderer(renderer); 
	renderer = nullptr; 
	SDL_DestroyWindow(window); 
	window = nullptr; SDL_Quit();

	SessionEndEvent* endEvent = Tracker::GetInstance().createSessionEndEvent();
	Tracker::GetInstance().trackEvent(endEvent);
}
//---------------------------Gets-------------------------
SDL_Window* SDLApp::getWindow() const {
	return window;
}

SDL_Renderer* SDLApp::getRenderer() const {
	return renderer;
}

int SDLApp::getWindowWidth() const {
	return winWidth;
}

int SDLApp::getWindowHeight() const {
	return winHeight;
}

GameStateMachine* SDLApp::getStateMachine() {
	return this->maquinaEstados;
}

void SDLApp::updatePantallaCarga()
{
	SDL_RenderClear(getRenderer());
    carga->render(SDL_GetTicks());
	SDL_RenderPresent(getRenderer());
}

void SDLApp::loadCarga()
{
	carga = new Entity(this);
	tx = new Texture(this->getRenderer(), "..//images/SpriteSheets_Personajes/vecinaNinya.png");
	carga->addAnim("carga", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,13,12,11,10,9,8,7,6,0,1,0,1,0,0,1 }, true, -1, 200);
	carga->playAnim("carga");
	carga->setHeight(81);
	carga->setWidth(50);
	carga->setPosition(Vector2D(1280-carga->getWidth()*3/2, 720-carga->getHeight()*3/2));
	carga->addRenderComponent(new AnimationRenderer(tx, carga->getAnimations(), 4, 5, 39, 81));
}