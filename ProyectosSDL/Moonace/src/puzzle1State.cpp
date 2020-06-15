#include "puzzle1State.h"
#include <fstream>
#include "json.hpp"
#include <Tracker.h>

Puzzle1State::Puzzle1State(SDLApp * game, GameState * previousState, Uint8 numberPuzzle, int numText, int id, bool swap) :Puzzle(game, id, swap), previousState(previousState), numText_(numText), _id(id)
{
	pb = MouseEventAnimComponent(SDL_MOUSEBUTTONDOWN, "Pressed", "Stop", SDL_BUTTON_LEFT);

	loadFromJson(numberPuzzle); //el 1 ese habr� que sacarlo de alg�n lado

	imagenCopia = new ImageRenderer(app->getResources()->getImageTexture(Resources::ImageId(numText)));
	copia->addRenderComponent(imagenCopia);
	copia->setWidth(imagenCopia->getTexture()->getHeight()*1.5*relacion.first);
	copia->setHeight(imagenCopia->getTexture()->getHeight()*1.7*relacion.second);
	copia->setPosition(Vector2D((103 * relacion.first) - copia->getWidth() / 2, (230 * relacion.second) - copia->getHeight() / 2));
	stage.push_back(copia);

	auxI = matriz[0][0]->getPosition().getX();
	auxD = auxI + relacion.first*espaciado;
	auxAB = matriz[numCas-1][numCas-1]->getPosition().getY();
	auxA = auxAB - relacion.second*espaciado;

	for (int i = 0; i < numCas*2; i++) {
		Boton* b;
		if (i < numCas) {
			b = new Boton(game, usar, this, "boton1", i, -1, Resources::BotonSonido);
			b->setWidth(50);
			b->setHeight(40);
			b->setPosition(Vector2D(b->getWidth() + 280, relacion.second*((espaciado-4)*i + 60)));
			b->setAnimated(true);
			b->addInputComponent(&pb);
		}
		else {
			b = new Boton(game, usar, this, "boton1", -1, i - numCas, Resources::BotonSonido);
			b->setWidth(50);
			b->setHeight(40);
			b->setPosition(Vector2D(relacion.first*(espaciado*(i-numCas) + 97) + espaciado*2, game->getWindowHeight()-b->getHeight() - b->getHeight()/2 + 10));
			b->setAnimated(true);
			b->addInputComponent(&pb);
		}
		b->addAnim("Stop", { 0 }, true);
		b->addAnim("Pressed", { 1 }, true, -1, 50);
		RenderComponent* bAnim = new AnimationRenderer(app->getResources()->getImageTexture(Resources::BotonPuzzle), b->getAnimations(), 1, 2, 49, 51);
		botonesAnim.push_back(bAnim);
		b->addRenderComponent(botonesAnim[i]);
		botones.push_back(b);
		stage.push_front(b);
	}

	//------------------------------------HUD-------------------------------------------------------------
	resetFunct_ = [this]() mutable { resetFunction(); };
	exitFunct_ = [this]() mutable { this->exit(); };

	resetButton = new Boton(app, "reset", resetFunct_, Resources::BotonSonido);
	resetButton->addAnim("Stop", { 0 }, true);
	resetButton->addAnim("Pressed", { 1 }, true, -1, 50);
	reiniciar = new AnimationRenderer(app->getResources()->getImageTexture(Resources::BotonReiniciar), resetButton->getAnimations(), 1, 2, 140, 140);
	resetButton->setAnimated(true);
	resetButton->addInputComponent(&pb);
	resetButton->setPosition(Vector2D(43.5*relacion.first, 378*relacion.second)); //numeros majos
	resetButton->setHeight(reiniciar->getTexture()->getHeight() * 2.1 / 3);
	resetButton->setWidth(reiniciar->getTexture()->getWidth() * 4 / 3);
	resetButton->addRenderComponent(reiniciar);
	stage.push_back(resetButton);

	exitButton = new Boton(app, "reset", exitFunct_, Resources::BotonSonido);
	exitButton->addAnim("Stop", { 0 }, true);
	exitButton->addAnim("Pressed", { 1 }, true, -1, 50);
	exitRenderer = new AnimationRenderer(app->getResources()->getImageTexture(Resources::BotonSalir), exitButton->getAnimations(), 1, 2, 49, 51);
	exitButton->setAnimated(true);
	exitButton->addInputComponent(&pb);
	exitButton->setHeight(exitRenderer->getTexture()->getHeight() * 2.1 / 3);
	exitButton->setWidth(exitRenderer->getTexture()->getWidth() * 4 / 3);
	exitButton->setPosition(Vector2D(exitButton->getWidth() / 2, exitButton->getHeight() / 2)); //numeros majos
	exitButton->addRenderComponent(exitRenderer);
	stage.push_back(exitButton);

	vector<int> j;
	j.resize(66);
	for (int i = 0; i < 66; i++)j[i] = i;
	puzzleHud->addAnim("Normal", j, true, -1, 50);
	puzzleHud->setHeight(app->getWindowHeight());
	puzzleHud->setWidth(app->getWindowWidth());
	puzzleHud->setPosition(Vector2D(Vector2D(app->getWindowWidth() / 2 - puzzleHud->getWidth() / 2,
		app->getWindowHeight() / 2 - puzzleHud->getHeight() / 2)));
	HUD = new AnimationRenderer(app->getResources()->getImageTexture(Resources::PuzzleHud), puzzleHud->getAnimations(), 8, 8, puzzleHud->getWidth()*0.75, puzzleHud->getHeight()*0.75);
	puzzleHud->addRenderComponent(HUD);
	HUD->playAnim(0);
	stage.push_back(puzzleHud);
	//---------------------------------------------------------------------------------------------------

	
}

//---------------------------------------------------------------------------------------------------
void Puzzle1State::update()
{
	if (!guarro) {
		guarro = true;
		// USABILIDAD
		Connect4Event* trackEvent = Tracker::GetInstance().createConnect4Event();
		trackEvent->setParameters(numPuzzle_, ENTER);
		Tracker::GetInstance().trackEvent(trackEvent);
	}

	GameState::update();
	if (mover) { mueveMatriz(); win(); }
}


void Puzzle1State::win() {

	if (numRestantes == 0) {
		Puzzle::win();
		// USABILIDAD
		Connect4Event* trackEvent1 = Tracker::GetInstance().createConnect4Event();
		trackEvent1->setParameters(numPuzzle_, COMPLETE);
		Tracker::GetInstance().trackEvent(trackEvent1);
	}
}

//---------------------------------------------------------------------------------------------------

void Puzzle1State::tresUnidos()
{
	vector<int> casSp;
	int cont = 0;
	Texture* aux = nullptr;
	if(currentFil >= 0){
		for (int i = 0; i < numCas; i++){
			//Si la casilla es especial
			if (matriz[currentFil][i]->active()) {
				casSp.push_back(i);//marcamos como especial para luego comprobar otra dir
				if (aux == nullptr) aux = matriz[currentFil][i]->getTexture(0);//Textura aux a comprobar
				if( matriz[currentFil][i]->getTexture(0) == aux) {//Si tiene la textura correcta
					cont++;//Aumentamos contador
				}
				else {
					aux = matriz[currentFil][i]->getTexture(0);//Le damos el valor de la nueva casilla activap
					if (cont >= 3) {//Vemos si habia mas de 3 acumuladas
						for (int j = cont; j > 0; j--) {
							destCasilla(matriz[currentFil][i - j]);
						}
					}
					cont = 1;//La que acabamos de recibir
				}
			}
			else {
				if (cont >= 3) {//Vemos si habia mas de 3 acumuladas
					for (int j = cont; j > 0; j--) {
						destCasilla(matriz[currentFil][i - j]);
					}
				}
				cont = 0; aux = nullptr;
			}//Reseteo vars
		}
		if (cont >= 3) {
			for (int j = cont; j > 0; j--) {
				destCasilla(matriz[currentFil][numCas - j]);
			}
			cont = 0;
			aux = nullptr;
		}
		else { cont = 0; aux = nullptr;}

		for (int i = 0; i < casSp.size(); i++)checkLine(casSp[i], false);
	}
	if(currentCol>-1){
		for (int i = 0; i < numCas; i++) {
			//Si la casilla es especial
			if (matriz[i][currentCol]->active()) {
				casSp.push_back(i);//marcamos como especial para luego comprobar otra dir
				if (aux == nullptr) aux = matriz[i][currentCol]->getTexture(0);//Textura aux a comprobar
				if (matriz[i][currentCol]->getTexture(0) == aux) {//Si tiene la textura correcta
					cont++;//Aumentamos contador
				}
				else {
					aux = matriz[i][currentCol]->getTexture(0);//Le damos el valor de la nueva casilla activap
					if (cont >= 3) {//Vemos si habia mas de 3 acumuladas
						for (int j = cont; j > 0; j--) {
							destCasilla(matriz[i - j][currentCol]);
						}
					}
					cont = 1;//La que acabamos de recibir
				}
			}
			else {
				if (cont >= 3) {//Vemos si habia mas de 3 acumuladas
					for (int j = cont; j > 0; j--) {
						destCasilla(matriz[i - j][currentCol]);
					}
				}
				cont = 0; aux = nullptr; 
			}//Reseteo vars
		}
		if (cont >= 3) {
			for (int j = cont; j > 0; j--) {
				destCasilla(matriz[numCas - j][currentCol]);
			}
			cont = 0;
			aux = nullptr;
		}
		else { cont = 0; aux = nullptr; }
		for (int i = 0; i < casSp.size(); i++)checkLine(casSp[i], true);
	}
}

//---------------------------------------------------------------------------------------------------

void Puzzle1State::mueveMatriz()
{
	if (currentFil >= 0) {
		if (auxD > auxI) {
			for (int i = 0; i < numCas; i++) {
				matriz[currentFil][i]->setVelocity(Vector2D(5, 0));
				matriz[currentFil][i]->setPosition(matriz[currentFil][i]->getPosition() + matriz[currentFil][i]->getVelocity());
				if (matriz[currentFil][i]->getPosition().getX() > topD) 
					matriz[currentFil][i]->setPosition(Vector2D(topI, matriz[currentFil][i]->getPosition().getY()));
			}
			auxI = matriz[currentFil][0]->getPosition().getX();
		}
		else {
			reestableFC(currentFil, -1);
			mover = false;
			auxI = matriz[0][0]->getPosition().getX();
			auxD = auxI + relacion.first*espaciado;
			tresUnidos();
		}
	}
	else {
		if (auxA < auxAB) {
			for (int i = 0; i < numCas; i++) {
				matriz[i][currentCol]->setVelocity(Vector2D(0, -5));
				matriz[i][currentCol]->setPosition(matriz[i][currentCol]->getPosition() + matriz[i][currentCol]->getVelocity());
				if (matriz[i][currentCol]->getPosition().getY() < topA) matriz[i][currentCol]->setPosition(Vector2D(matriz[i][currentCol]->getPosition().getX(), topAB));
			}
			auxAB = matriz[4][currentCol]->getPosition().getY();
		}
		else {
			reestableFC(-1, currentCol);
			mover = false;
			auxAB = matriz[numCas - 1][numCas - 1]->getPosition().getY();
			auxA = auxAB - relacion.second*espaciado;
			tresUnidos();
		}
	}
}

//---------------------------------------------------------------------------------------------------

void Puzzle1State::deleteMatrix() {
	vector<vector<CasillaPuzzle1*>>::iterator it;
	for (it = matriz.begin(); it != matriz.end();) {
		vector<CasillaPuzzle1*>::iterator anotherIt;
		for (anotherIt = (*it).begin(); anotherIt != (*it).end();) {
			this->deleteElement(*anotherIt);
			anotherIt = (*it).erase(anotherIt); //si no hacemos esto, la lista "stage" acaba con 10k objetos, todos nullptr
		}
		it = matriz.erase(it);
	}
}

//---------------------------------------------------------------------------------------------------

void Puzzle1State::destroy()
{
	for (int i = 0; i < botones.size(); i++) {
		if (botones[i] != nullptr) { botones[i]->delInputComponent(&pb); delete botones[i]; botones[i] = nullptr; }
		if (botonesAnim[i] != nullptr) { botonesAnim[i] = nullptr; }
	}

	deleteMatrix();

	resetButton->delInputComponent(&pb);
	exitButton->delInputComponent(&pb);

	if (resetButton != nullptr) { delete resetButton; resetButton = nullptr; }

	if (exitButton != nullptr) { delete exitButton; exitButton = nullptr; }

	if (puzzleHud != nullptr) { delete puzzleHud; puzzleHud = nullptr; }

	if (copia != nullptr) { delete copia; copia = nullptr; }
}

//---------------------------------------------------------------------------------------------------

void Puzzle1State::usar(GameState* state, int fil, int col)
{
	Puzzle1State* puzz = dynamic_cast<Puzzle1State*>(state);
	if (puzz != nullptr && !puzz->mover) { //comprobamos que sea el inventario por si acaso
		if (fil != -1) {
			puzz->currentFil = fil;
			puzz->currentCol = -1;
		}
		else if (col != -1) {
			puzz->currentCol = col;
			puzz->currentFil = -1;
		}
		puzz->mover = true;
	}
}

void Puzzle1State::resetFunction()
{
	if (!this->isMoving()) {
		this->restart();
		// USABILIDAD
		Connect4Event* trackEvent1 = Tracker::GetInstance().createConnect4Event();
		trackEvent1->setParameters(numPuzzle_, EXIT);
		Tracker::GetInstance().trackEvent(trackEvent1);
		Connect4Event* trackEvent2 = Tracker::GetInstance().createConnect4Event();
		trackEvent2->setParameters(numPuzzle_, ENTER);
		Tracker::GetInstance().trackEvent(trackEvent2);
	}
}

//---------------------------------------------------------------------------------------------------

void Puzzle1State::eligeTipoCasilla(int tipoCas, string name, CasillaPuzzle1*& cas) { //A partir del enum y el numero asociado a la casilla
	switch (tipoCas) {
		case CasillaVacia:
			cas = new CasillaPuzzle1(app, name, app->getResources()->getImageTexture(Resources::CasillaPuzzleV));
			break;
		case CasillaLlena:
			numRestantes++;
			cas = new CasillaPuzzle1(app, name, app->getResources()->getImageTexture(Resources::ImageId(numText_)), true);
			break;
		default:
			cas = new CasillaPuzzle1(app, name, app->getResources()->getImageTexture(Resources::CasillaPuzzleV)); //por defecto es vac�a
			break;
	}
}

//---------------------------------------------------------------------------------------------------

void Puzzle1State::loadFromJson(int numeroPuzzle){
	string name = "..\\Puzzles\\Puzzle" + to_string(numeroPuzzle);
	name += ".json";
	std::ifstream file(name);

	if (file.is_open()) { // Para que no pete si abre un archivo que no existe
		
		json json;
		file >> json;
		int index = 0;
		if (json["Casillas"].is_array()) {
			matriz.resize(numCas);  //numCas = j["numCas"]; es const asi que supondr� que siempre es el mismo tama�o de matriz
			matrizOriginal.resize(numCas);
			for (unsigned int i = 0; i < numCas; i++) {//inicializacion de la matriz de casillas
				matrizOriginal[i].resize(numCas);
				matriz[i].resize(numCas);
				for (unsigned int j = 0; j < numCas; j++) {
					matrizOriginal[i][j] = json["Casillas"][index]["Tipo"]; //se rellena la matriz original con su numero correspondiente
					eligeTipoCasilla(json["Casillas"][index]["Tipo"], std::to_string(i*numCas + j), matriz[i][j]);
					matriz[i][j]->setPosition(Vector2D(relacion.first*(espaciado*j + 240), relacion.second*((espaciado-5)*i + 53)));
					stage.push_back(matriz[i][j]);
					index++;
				}
			}
		}
		file.close();
	}
	else {
		cout << "No existe el archivo indicado" << name;
	}
}

//---------------------------------------------------------------------------------------------------

void Puzzle1State::checkLine(int line, bool Vert)
{
	int cont = 0;
	Texture* aux = nullptr;
	if (Vert) {//Vertical
		for (int i = 0; i < numCas; i++) {
			//Si la casilla es especial
			if (matriz[line][i]->active()) {
				if (aux == nullptr) aux = matriz[line][i]->getTexture(0);//Textura aux a comprobar
				if (matriz[line][i]->getTexture(0) == aux) {//Si tiene la textura correcta
					cont++;//Aumentamos contador
				}
				else {
					aux = matriz[line][i]->getTexture(0);//Le damos el valor de la nueva casilla activa
					if (cont >= 3) {//Vemos si habia mas de 3 acumuladas
						for (int j = cont; j > 0; j--) {
							destCasilla(matriz[line][i - j]);
						}
					}
					cont = 1;//La que acabamos de recibir
				}
			}
			else {
				if (cont >= 3) {//Vemos si habia mas de 3 acumuladas
					for (int j = cont; j > 0; j--) {
						destCasilla(matriz[line][i - j]);
					}
				}
				cont = 0; aux = nullptr;
			}//Reseteo vars
		}
		if (cont >= 3) {
			for (int j = cont; j > 0; j--) {
				destCasilla(matriz[line][numCas - j]);
			}
			cont = 0;
			aux = nullptr;
		}
		else { cont = 0; aux = nullptr; }
	}
	else {
		for (int i = 0; i < numCas; i++) {
			//Si la casilla es especial
			if (matriz[i][line]->active()) {
				if (aux == nullptr) aux = matriz[i][line]->getTexture(0);//Textura aux a comprobar
				if (matriz[i][line]->getTexture(0) == aux) {//Si tiene la textura correcta
					cont++;//Aumentamos contador
				}
				else {
					aux = matriz[i][line]->getTexture(0);//Le damos el valor de la nueva casilla activap
					if (cont >= 3) {//Vemos si habia mas de 3 acumuladas
						for (int j = cont; j > 0; j--) {
							destCasilla(matriz[line][i - j]);
						}
					}
					cont = 1;//La que acabamos de recibir
				}
			}
			else {
				if (cont >= 3) {//Vemos si habia mas de 3 acumuladas
					for (int j = cont; j > 0; j--) {
						destCasilla(matriz[i - j][line]);
					}
				}
				cont = 0; aux = nullptr;
			}//Reseteo vars
		}
		if (cont >= 3) {
			for (int j = cont; j > 0; j--) {
				destCasilla(matriz[numCas-j][line]);
			}
			cont = 0;
			aux = nullptr;
		}
		else { cont = 0; aux = nullptr; }
	}
}

void Puzzle1State::destCasilla(CasillaPuzzle1* auxi) {
	auxi->setActive(false); numRestantes--;
	auxi->addAnim("destroy", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, false, -1, 100);
	AnimationRenderer* aux = new AnimationRenderer(app->getResources()->getImageTexture(Resources::casillaPuzzleDest), auxi->getAnimations(), 3, 3, 64, 58);
	auxi->setRender(aux);
	aux->playAnim(0);
	aux = nullptr;
}

//---------------------------------------------------------------------------------------------------

void Puzzle1State::restart()
{
	this->deleteMatrix(); //primero borra todos los elementos de la matriz actual
	this->changeList(); //evita problemas de nullptr en el handle del state
	numRestantes = 0; //para que sea posible resolverlo. Si reinicia se setea a 0 y se suma en su lugar adecuado
	matriz.resize(numCas);
	for (unsigned int i = 0; i < matrizOriginal.size(); i++) {
		matriz[i].resize(numCas);
		for (unsigned int j = 0; j < matrizOriginal[i].size(); j++) {
			eligeTipoCasilla(matrizOriginal[i][j], std::to_string(i*numCas + j), matriz[i][j]); //depende del tipo anteriormente guardado, se crea una casilla u otra
			matriz[i][j]->setPosition(Vector2D(relacion.first*(espaciado*j + 240), relacion.second*((espaciado - 5)*i + 53))); //la coloca
			stage.push_front(matriz[i][j]); //la pushea
		}
	}
}

//---------------------------------------------------------------------------------------------------
