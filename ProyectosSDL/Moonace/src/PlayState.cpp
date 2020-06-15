#include "PlayState.h"
#include "GOstates.h"
#include <list>
#include "TransitionScreen.h"
#include "NPC.h"
#include "CreditosState.h"
#include <Tracker.h>

bool compareZ(GameObject* o1, GameObject* o2) { //pure luck require ahead
	int obj1_, obj2_;
	obj1_ = obj2_ = 10;
	if (o1->getPosition().getY() > o1->getGame()->getWindowHeight() / 2) {
		obj1_ = o1->getPosition().getY();
	}

	if (o2->getPosition().getY() > o2->getGame()->getWindowHeight() / 2) {
		obj2_ = o2->getPosition().getY();
	}

	if (o1->getWidth() > 1000) { //es feiiiiisimo pero es mas eficiente que las otras opciones
		obj1_ = 800;
	}

	if (o2->getWidth() > 1000) {
		obj2_ = 800;
	}

	return (obj1_ > obj2_);
}

void PlayState::SetZBuffer() //try tongue
{
	Zbuffer.clear();
	Zbuffer = stage;
	Zbuffer.pop_back(); //Quitamos el fondo
	Zbuffer.sort(compareZ);
}

PlayState::PlayState(SDLApp* app, bool load) : GameState(app) {
	Puzzle::numPuzzle = 0;

	// crea la lista vacia
	list = new ObjectList(app);
	string name;
	if (load) name = "..\\Scenes\\saves\\pj.json";
	else name = "..\\Scenes\\pj.json";
	// Inicializa el personaje con los datos de archivo de la primera escena
	std::ifstream i(name);

	if (!i.is_open() && load) { name = "..\\Scenes\\pj.json"; i = std::ifstream(name); } //controlar que le de a continuar sin haber guardado nada
	if (i.is_open()) {
		json j;
		i >> j;
		//SHORTCUT
		shortcut = new ShortCut(app, list, resources);
		stage.push_front(shortcut);

		alena = new MainCharacter(app, j, list, &collision, shortcut, 6.0, this);
		stage.push_front(alena);

		i.close();
	}

	name = "..\\Scenes\\numScenes.json"; //archivo que indica el numero de las escenas
	int numScenes = 0;
	std::ifstream k(name);
	if (k.is_open()) {
		json numSC;
		k >> numSC;
		numScenes = numSC["numScenes"];
		k.close();
	}
	else {
		cout << "Archivo no encontrado: " + name;
	}

	if (!load) {
		for (int cont = 0; cont < numScenes; cont++) {
			scenes.push_back(new Scene(cont, app, alena, this));
		}
	}
	else
	{
		for (int cont = 0; cont < numScenes; cont++) {
			scenes.push_back(new Scene(cont, app, alena, this, load));
		}
	}

	this->currentScene = alena->getCurrentScene();
	addObserver(alena);
}


PlayState::~PlayState() {

	//Se destruye la conversacion si la hay, para que no de problemas
	if (enConversacion) {
		setEnConversacion(false);
	}

	vector<Scene*>::iterator aux;
	scenes[currentScene]->exitScene();
	std::ofstream i("..\\Scenes\\saves\\pj.json"); //archivo donde se va a guardar
	json j;
	alena->saveToJson(j);
	i << std::setw(4) << j; //pretty identación para leer mejor el archivo
	i.close(); //cierra el flujo
	delete alena;
	delete shortcut;

	stage.clear();
	for (aux = scenes.begin(); aux != scenes.end(); aux++) {
		(*aux)->saveSceneToJson();
		delete (*aux);
	}
	delete list;
}


void PlayState::swapScene(int nextScene)
{
	if (nextScene < (int)scenes.size() && nextScene >= 0) { // basicamente se asegura de que la escena a la que quiere cambiar existe
		stopAllSoundEffect();
		scenes[currentScene]->exitScene();

		currentScene = nextScene;
		scenes[nextScene]->enterScene();
		alena->setCurrentScene(currentScene);
		app->getStateMachine()->pushState(new TransitionScreen(app, app->getStateMachine()->currentState(), 700)); //se puede quitar si eso
		this->changeList();
	}
	else cout << "Escena no encontrada, numero buscado: " << nextScene << " , escenas existentes hasta: " << scenes.size() - 1;

}

void PlayState::handleEvent(SDL_Event & e) {
	if (e.type == SDL_MOUSEBUTTONDOWN) { 
		// USABILIDAD
		ClickSceneEvent* sceneEvent = Tracker::GetInstance().createClickSceneEvent();
		sceneEvent->setParameters(currentScene, { e.button.x, e.button.y });
		Tracker::GetInstance().trackEvent(sceneEvent);
	}

	if (!enConversacion) {  //para que no de error con textos automaticos
		if (e.type == SDL_KEYDOWN) { //jaaaaaaaaaaaaaaaacksss
			if (e.key.keysym.sym == SDLK_F1) {
				swapScene(currentScene + 1);
			}
			else if (e.key.keysym.sym == SDLK_F2) {

				swapScene(currentScene - 1);
			}
		}
	}

	if (!enConversacion) {
		GameState::handleEvent(e);
	}
	else{
		stage.front()->handleInput(0, e);
		handleCursor(e);
	}

	if (timeToClose) finishGame(app); //deberia der un callback peeeero no me acuerdo de como hacerlos

}
void PlayState::setEnConversacion(bool conv) {

	enConversacion = conv;
	if (!conv) {
		stage.pop_front();
	}

}

void PlayState::render() {

	sortZbuffer();

	stage.back()->render(0);

	std::list<GameObject*>::const_reverse_iterator its;
	for (its = Zbuffer.rbegin(); its != Zbuffer.rend(); its++)
		(*its)->render(0);
	
	this->renderCursor();
}



void PlayState::sortZbuffer() { //no apto para sensibles
	int alenaZActual = alena->getPosition().getY();

	bool flag = true;
	if (listhasChanged) {
		SetZBuffer();
	}
	vector<std::list<GameObject*>::iterator*> overlap;
	overlap = getOverlapping();
	std::list<GameObject*>::iterator alenaIt;// = consAlenaIt;//No begin dynamic alena
	for (alenaIt = Zbuffer.begin(); (*alenaIt) != alena; alenaIt++); //Encontramos la pos de alena parece un for pero es un while disfrazado (eficiencia yeyy)
	alenaZ = alenaZActual;
	if(!enConversacion) Zbuffer.erase(alenaIt);
	//short
	if (!overlap.empty()) {
		SetZBuffer();
	}
	else if(!enConversacion){
		Zbuffer.push_front(alena);
	}
}

vector<std::list<GameObject*>::iterator*> PlayState::getOverlapping() //tears
{
	vector<std::list<GameObject*>::iterator*> overlap;
	SDL_Rect AlenaRect, itmRect, hanzpReckt;
	//Rect Alena
	AlenaRect.x = alena->getPosition().getX();
	AlenaRect.y = alena->getPosition().getY() + alena->getHeight() + 10;
	AlenaRect.w = alena->getWidth();
	AlenaRect.h = alena->getHeight() / 6; 
	
	for(it = Zbuffer.begin(); it != Zbuffer.end();it++){//Comprobamos con que rects hay colision
		itmRect.x = (*it)->getPosition().getX();
		itmRect.y = (*it)->getPosition().getY();
		itmRect.w = (*it)->getWidth();
		itmRect.h = (*it)->getHeight();
		if (SDL_IntersectRect(&AlenaRect, &itmRect, &hanzpReckt)) {
			overlap.push_back(&it); //Los añadimos al vector
		}
	}
	return overlap;
}

void PlayState::receive(Mensaje* msg) {
	switch (msg->id_) {
	case CambioEscena: 
	{
		int numScene = static_cast<MensajeCambioEscenaDialogos*>(msg)->numScene_; //los static de los mensajes no se pueden quitar T_T
		if(enConversacion) setEnConversacion(false);
		swapScene(numScene);
		break;
	}
	case AddItemDialog:
	{
		MensajeAddItem* msgDialog = static_cast<MensajeAddItem*>(msg);
		alena->addInventoryObject(&ItemInventario(app, 0, 0, 0, 0, msgDialog->desc_, msgDialog->tag_, app->getResources()->getImageTexture(Resources::ImageId(msgDialog->txt_)), msgDialog->perm_));
		if(enConversacion) setEnConversacion(false);
		break;
	}
	case CHANGE_TO_CREDITS: 
	{
		timeToClose = true;
		break;
	}
	case WinPuzzle:
	{
		SwapScenePuzzle* msgPuzzle = static_cast<SwapScenePuzzle*>(msg);
		if(msgPuzzle->swapScene) swapScene(currentScene + 1);
		break;
	}
	case DialogoAcabado:
		setEnConversacion(false);
		break;
	case SetZBufferPlayState:
		this->SetZBuffer();
		break;
	case Pausa:
		this->pauseMenu();
		break;
	case AbreInventario:
		this->creaInventario();
		break;
	case CambioEstado:
		send(&Mensaje(Stop));
		break;
	default:
		break;
	}
}

void PlayState::finishGame(SDLApp* app_)
{
	app_->getStateMachine()->currentState()->changeList();
	app_->getStateMachine()->popState();

	CreditosState* credits = new CreditosState(app_);

	app_->getStateMachine()->pushState(credits);

	app_->getStateMachine()->pushState(new TransitionScreen(app_, app_->getStateMachine()->currentState(), 1500));
}