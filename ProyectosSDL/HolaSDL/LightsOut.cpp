#include "LightsOut.h"
#include <Tracker.h>


LightsOut::LightsOut(SDLApp* app, int numCas, int dificultad, int id, bool swap) : Puzzle(app, id, swap), puzzleHasStarted(false), numCas(numCas)
{
	press = MouseEventAnimComponent(SDL_MOUSEBUTTONDOWN, "Pressed", "Stop", SDL_BUTTON_LEFT);
	this->creaDecoracion(); //crea los objetos del HUD

	lights.resize(numCas);
	aux.resize(numCas);

	for (int i = 0; i < numCas; i++) { //inicializacion de la lights de casillas
		lights[i].resize(numCas);
		aux[i].resize(numCas);
		for (int j = 0; j < numCas; j++) {
			lights[i][j] = new CasillaLight(app, i, j, tamCas/numCas, tamCas/numCas, app->getResources()->getImageTexture(Resources::LuzApagada), this);
			lights[i][j]->setPosition(Vector2D(relacion.first*(espaciado*j + posX), relacion.second*(espaciado*i + 182)));
			stage.push_front(lights[i][j]);
		}
	}

	this->apagaLuces(dificultad);

	//--------Botones-----
	resetFunc_ = [this]() mutable { resetPuzzle(); };
	exitFun_ = [this]() mutable { this->exit(); };
	botonReset = new Boton(app, "reset", resetFunc_, Resources::BotonSonido);
	botonReset->setWidth(80);
	botonReset->setHeight(60);
	botonReset->setPosition(Vector2D(app->getWindowWidth() / 1.35, app->getWindowHeight()/2 + botonReset->getHeight()*1.8));
	botonReset->addAnim("Stop", { 0 }, true, -1, 100);
	botonReset->addAnim("Pressed", { 1 }, true, -1, 100);
	botonReset->addRenderComponent(new AnimationRenderer(app->getResources()->getImageTexture(Resources::ReturnLuces), botonReset->getAnimations(), 1, 2, 56, 53));
	botonReset->setAnimated(true);
	botonReset->addInputComponent(&press);
	stage.push_front(botonReset);

	botonExit = new Boton(app, "exit", exitFun_, Resources::BotonSonido);
	botonExit->setWidth(80);
	botonExit->setHeight(60);
	botonExit->setPosition(Vector2D(app->getWindowWidth() / 1.35, app->getWindowHeight() / 2 + botonReset->getHeight()*3));
	botonExit->addAnim("Stop", { 0 }, true, -1, 100);
	botonExit->addAnim("Pressed", { 1 }, true, -1, 100);
	botonExit->addInputComponent(&press);
	botonExit->addRenderComponent(new AnimationRenderer(app->getResources()->getImageTexture(Resources::BotonSalirLuces), botonExit->getAnimations(), 1, 2, 56, 53));
	botonExit->setAnimated(true);
	stage.push_front(botonExit);
}


LightsOut::~LightsOut() //destructora
{
	hudAux->delRenderComponent(&hudRend);

	for (unsigned int i = 0; i < numCas; i++) {
		for (unsigned int j = 0; j < numCas; j++) {
			delete lights[i][j]; lights[i][j] = nullptr;
		}
	}

	botonReset->delInputComponent(&press);
	botonExit->delInputComponent(&press);
	delete botonReset;
	delete botonExit;
	stage.clear();
}

void LightsOut::win(){ //comprueba que todas las luces esten encendidas

	bool _win = true;
	unsigned int i = 0;
	while (i < lights.size() && _win) {
		unsigned int j = 0;
		while (j < lights[i].size() && _win) {
			if (!lights[i][j]->isOn()) { _win = false;}
			j++;
		}
		i++;
	}
	
	if (_win && puzzleHasStarted) { //si gana y el puzzle ha empezado
		Puzzle::win();
		// USABILIDAD
		LightPuzzleEvent* trackEvent = Tracker::GetInstance().createLightPuzzleEvent();
		trackEvent->setParameters(numPuzzle_, COMPLETE);
		Tracker::GetInstance().trackEvent(trackEvent);
	}
}

void LightsOut::receive(Mensaje* msg){
	if(msg->id_ == LuzInvertida) {
		pair<int, int> aux;
		aux = static_cast<MensajePosicionMatriz*>(msg)->pos_; //devuelve i, j de la matriz

		//invierte las adyacentes
		if (aux.first + 1 < lights.size()) { 
			lights[aux.first + 1][aux.second]->invertir(); 
		}
		if (aux.first - 1 >= 0) { 
			lights[aux.first - 1][aux.second]->invertir();
		}
		if (aux.second + 1 < lights[aux.first].size()) {
			lights[aux.first][aux.second + 1]->invertir();
		}
		if (aux.second - 1 >= 0) {
			lights[aux.first][aux.second - 1]->invertir();
		}

		win(); //comprueba si ha ganado o no
	}
}

void LightsOut::render(){
	if (!guarro) {
		guarro = true;
		// USABILIDAD
		LightPuzzleEvent* trackEvent = Tracker::GetInstance().createLightPuzzleEvent();
		trackEvent->setParameters(numPuzzle_, ENTER);
		Tracker::GetInstance().trackEvent(trackEvent);
	}

	fadeOut();
	GameState::render();
}

void LightsOut::handleEvent(SDL_Event & e){
	Puzzle::handleEvent(e);
	if (faded && !hasWon) GameState::handleEvent(e); //podria hacerlo activando los gameObjects, pero como el active no lo usamos para nada, no quiero tocar la estructura por un efecto "fancy"
}

void LightsOut::apagaLuces(const unsigned int n){
	unsigned int i = 0;
	pair<pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int>> parAux; //par donde se guardan las dos ultimas posiciones invertidas
	parAux.first.first = parAux.first.second = parAux.second.first = parAux.second.second = numCas + 1; //no sé iniciar un par de pares snif

	while (i < n) {
		unsigned int x = rand() % numCas; //random entre 0 y numCas - 1
		unsigned int y = rand() % numCas;

		while(x == parAux.first.first || x == parAux.second.first) { x = rand() % numCas; } //mientras x sea igual al primer elemento de las dos posiciones, se hace random
		while (y == parAux.first.second || y == parAux.second.second) { y = rand() % numCas; } //igual en la y
		parAux.first.first = x;
		parAux.first.second = y;
		swap(parAux.first, parAux.second); //swap : (parActual, parViejo)--->(parViejo, parActual)

		lights[x][y]->act();
		i++;
	}
	updateAux();
	puzzleHasStarted = true; //puede ser que mientras hace el random de invertir, genere un puzzle resuelto. Si hace la comprobacion de win siempre, se saldra del estado y no queremos eso. Bool 
	//auxiliar para que solo compruebe cuando el random haya acabado y ya el usuario haga click en las casillas
}

void LightsOut::updateAux(){
	for (unsigned int i = 0; i < aux.size(); i++) {
		for (unsigned int j = 0; j < aux[i].size(); j++) {
			aux[i][j] = lights[i][j]->isOn();
		}
	}
}

void LightsOut::restartMatrix(){
	for (unsigned int i = 0; i < lights.size(); i++) {
		for (unsigned int j = 0; j < lights[i].size(); j++) {
			lights[i][j]->setOn(aux[i][j]); //cambia el bool y la textura a la inicial
		}
	}
}

void LightsOut::resetPuzzle(){
	this->restartMatrix();
	// USABILIDAD
	LightPuzzleEvent* trackEvent1 = Tracker::GetInstance().createLightPuzzleEvent();
	trackEvent1->setParameters(numPuzzle_, EXIT);
	Tracker::GetInstance().trackEvent(trackEvent1);
	LightPuzzleEvent* trackEvent2 = Tracker::GetInstance().createLightPuzzleEvent();
	trackEvent2->setParameters(numPuzzle_, ENTER);
	Tracker::GetInstance().trackEvent(trackEvent2);
}

void LightsOut::creaDecoracion(){ //como ensuciar el código 2.0
	decorado.resize(6);

	hudRend = (app->getResources()->getImageTexture(Resources::HudLuces)); //hud del inventario

	decorado[0] = Entity(app); //barras y su animacion
	decorado[0].addAnim("IdleRight", {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,6,7}, true, -1, 100); //...
	decorado[0].setHeight(150); decorado[0].setWidth(200); decorado[0].setPosition(Vector2D(0 + decorado[0].getWidth() / 2 + 10, decorado[0].getHeight()/0.55)); //numeros majos
	anim.push_back(new AnimationRenderer(app->getResources()->getImageTexture(Resources::Barras), decorado[0].getAnimations(), 2, 4, 226, 164));
	decorado[0].addRenderComponent(anim[0]);
	stage.push_back(&decorado[0]);

	decorado[1] = Entity(app); //barra de carga y su animacion
	decorado[1].addAnim("IdleRight", {0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,25,26,26,25,25,25,26,26,25,25,26,26,25,25}, true, -1, 75); //...
	decorado[1].setHeight(480); decorado[1].setWidth(480); decorado[1].setPosition(Vector2D(app->getWindowWidth()/1.5 - decorado[1].getWidth()/60, decorado[1].getHeight()/3.6));
	anim.push_back(new AnimationRenderer(app->getResources()->getImageTexture(Resources::Carga), decorado[1].getAnimations(), 5, 6, 480, 480));
	decorado[1].addRenderComponent(anim[1]);
	stage.push_back(&decorado[1]);

	decorado[2] = Entity(app); //ondas y su animacion
	decorado[2].addAnim("IdleRight", { 0, 1, 2, 3, 4, 5, 6, 7 , 8, 9, 10, 11, 12, 13, 14, 15, 16 }, true, -1, 75);
	decorado[2].setHeight(300); decorado[2].setWidth(280); decorado[2].setPosition(Vector2D(decorado[2].getWidth()/4, app->getWindowHeight()/1.8));
	anim.push_back(new AnimationRenderer(app->getResources()->getImageTexture(Resources::Onda), decorado[2].getAnimations(), 4, 5, 272, 272));
	decorado[2].addRenderComponent(anim[2]);
	stage.push_back(&decorado[2]);

	decorado[3] = Entity(app); //texto y su animacion
	decorado[3].addAnim("IdleRight", { 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1}, true, -1, 175); //...
	decorado[3].setHeight(300); decorado[3].setWidth(280); decorado[3].setPosition(Vector2D(decorado[3].getWidth() / 4, 0));
	anim.push_back(new AnimationRenderer(app->getResources()->getImageTexture(Resources::TextoPixel), decorado[3].getAnimations(), 1, 2, 240, 240));
	decorado[3].addRenderComponent(anim[3]);
	stage.push_back(&decorado[3]);

	decorado[4] = Entity(app); //botella y su animacion
	decorado[4].addAnim("IdleRight", {0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,9,9,9,9,9,9,9,9,9,9,9,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29}, true, -1, 150); //...
	decorado[4].setHeight(200); decorado[4].setWidth(200); decorado[4].setPosition(Vector2D(app->getWindowWidth() - decorado[4].getWidth()*1.54,decorado[4].getHeight()/2.5));
	anim.push_back(new AnimationRenderer(app->getResources()->getImageTexture(Resources::BotellaAnimada), decorado[4].getAnimations(), 5, 6, 200, 200));
	decorado[4].addRenderComponent(anim[4]);
	stage.push_back(&decorado[4]);

	decorado[5] = Entity(app); //hud
	decorado[5].setWidth(app->getWindowWidth()); decorado[5].setHeight(app->getWindowHeight()); decorado[5].setPosition(Vector2D(0, 0));
	decorado[5].addRenderComponent(&hudRend);
	hudAux = &decorado[5];
	stage.push_back(&decorado[5]);
}

void LightsOut::fadeOut(){ 
	if (alpha > alphaMin) {
		alpha -= 2;
		for (int i = 0; i < decorado.size(); i++) {
			decorado[i].getTexture()->changeAlpha(alpha);
		}
		if (alpha <= alphaMin) faded = true;
	}
}
