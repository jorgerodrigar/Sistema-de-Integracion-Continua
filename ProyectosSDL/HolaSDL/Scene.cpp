#include "Scene.h"
#include <fstream>
#include "MainCharacter.h"
#include "GOstates.h"
#include "LightsOut.h"
#include "GOConversational.h"
#include "PasswordState.h"
#include "PasswordState.h"
#include "AutoConversational.h"
#include "Decorado.h"
#include "NPC.h"
#include "FeedbackCursorInputComponent.h"
#include "ActEndingScreen.h"
#include "GOcofres.h"
#include <Tracker.h>

Scene::Scene()
{
	//Leer num scene
	//Idealmente lee de un archivo
}

Scene::Scene(int numEscena, SDLApp* app, MainCharacter* pj, Observer* playState, bool load):app(app), SceneNum(numEscena), pj(pj) {

	addObserver(playState);

	string name;
	if (load)name = "..\\Scenes\\saves\\Scene";
	else name = "..\\Scenes\\Scene";
	name = name + to_string(numEscena) +".json";

	std::ifstream i(name);
	
	if (!i.is_open() && load) { name = "..\\Scenes\\Scene"; name = name + to_string(numEscena) + ".json"; i = std::ifstream(name); }
	if (i.is_open()) { // Para que no intente abrir archivos que no existen

		json j;
		i >> j;
		int n;

		if (!j["CambioActo"].is_null()) {
			cambioActo = j["CambioActo"];
			if (!j["HeaderActo"].is_null()) {
				string h = j["HeaderActo"];
				headerActo = h;
			}

			if (!j["actNumber"].is_null()) {
				actNumber_ = j["actNumber"];
			}
		}


		GOstates* puzzleAux = nullptr; //para el objeto que requiere un puzzle en su constructora

		// Cargado de items de inventario
		string obj = "ItemInventario"; // nombre del array del objeto en el json
		for (int i = 0; i < j[obj].size(); i++) {

			n = j[obj][i]["Texture"];

			bool permanente = false;
			if (!j[obj][i]["permanente"].is_null()) { permanente = j[obj][i]["permanente"]; }

			ItemInventario* item = new ItemInventario(app, j[obj][i]["x"], j[obj][i]["y"], j[obj][i]["w"], j[obj][i]["h"],
				j[obj][i]["descripcion"], j[obj][i]["tag"],
				app->getResources()->getImageTexture(Resources::ImageId(n)), permanente);

			item->addInputComponent(new FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar));
			item->addInputComponent(new MouseEventAnimComponent(SDL_MOUSEMOTION, "Anim1", "Anim0"));
			SceneItems.push_front(item);

			addAnimsFromJSON(item, j[obj][i], n);

			readSoundEffect(item, j[obj][i]);

			if (!j[obj][i]["rotation"].is_null()) {
				SceneItems.front()->setRotation(j[obj][i]["rotation"]);
			}
		}

		obj = "GOState";
		//Cargado de Puzles
		for (int i = 0; i < j[obj].size(); i++) {

			n = j[obj][i]["Texture"];


			SceneStates.push_back(PuzzleCreator(j[obj][i]["type"], j[obj][i]));

			GOstates* goSt = new GOstates(app, j[obj][i]["x"], j[obj][i]["y"],
				j[obj][i]["w"], j[obj][i]["h"],
				app->getResources()->getImageTexture(Resources::ImageId(n)), SceneStates.back(), j[obj][i], playState);

			puzzleAux = goSt;

			goSt->addInputComponent(new FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar));

			SceneItems.push_back(goSt);

			addAnimsFromJSON(goSt, j[obj][i], n);

			readSoundEffect(goSt, j[obj][i]);

			if (!j[obj][i]["rotation"].is_null()) {
				SceneItems.back()->setRotation(j[obj][i]["rotation"]);
			}
		}

		obj = "Music"; 
		if (!j[obj].is_null()) {
			SceneMusic = j[obj][0];
			music = true;
		}
		else music = false;

		obj = "MusicVolume";
		if (!j[obj].is_null()) {
			musicVolume = j[obj][0];
		}
		
		obj = "StopActualMusic";
		if (!j[obj].is_null()) {
			stopMusic = j[obj][0];
		}

		obj = "SoundEffect";
		//Cargado de soundEffects
		for (int i = 0; i < j[obj].size(); i++) {
			if (!j[obj][i].is_null()) { //si el sonido no es null, se añade a la lista de soundEffects
				SceneSoundEffects.push(j[obj][i]);
			}
		}

		obj = "volumenes";
		//Cargado de volumenes
		for (int i = 0; i < j[obj].size(); i++) {
			if (!j[obj][i].is_null()) { //si el sonido no es null, se añade a la lista de soundEffects
				volumenes.push_back(j[obj][i]);
			}
		}

		obj = "numRepeticionesSonidos";

		if (j[obj].empty()) {
			for (int i = 0; i < SceneSoundEffects.size(); i++)
				numReps_.push_back(-1);
		}

		//Cargado de repeticiones
		for (int i = 0; i < j[obj].size(); i++) {
			if (!j[obj][i].is_null()) {
				numReps_.push_back(j[obj][i]);
			}
		}

		//Cargado objetos conversaciones
		for (int i = 0; i < j["GOConversational"].size(); i++) {

			n = j["GOConversational"][i]["Texture"];

			bool repeat = true;
			if (!j["GOConversational"][i]["repeat"].is_null()) {
				repeat = j["GOConversational"][i]["repeat"];
			}

			bool done = false;
			if (!j["GOConversational"][i]["done"].is_null()) {
				done = j["GOConversational"][i]["done"];
			}

			GOConversational* conver = new GOConversational(app, j["GOConversational"][i]["x"], j["GOConversational"][i]["y"], j["GOConversational"][i]["w"], j["GOConversational"][i]["h"],
				app->getResources()->getImageTexture(Resources::ImageId(n)), j["GOConversational"][i]["convoName"], repeat, done);

			conver->addInputComponent(new FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar));
			conver->addInputComponent(new MouseEventAnimComponent(SDL_MOUSEMOTION, "Anim1", "Anim0"));

			SceneItems.push_front(conver);

			addAnimsFromJSON(conver, j["GOConversational"][i], n);

			readSoundEffect(conver, j["GOConversational"][i]);

		}

		//Cargado objetos autoconversaciones
		for (int i = 0; i < j["AutoGOConversational"].size(); i++) {

			n = j["AutoGOConversational"][i]["Texture"];

			bool repeat = true;
			if (!j["AutoGOConversational"][i]["repeat"].is_null()) {
				repeat = j["AutoGOConversational"][i]["repeat"];
			}

			SceneItems.push_front(new AutoConversational(app, j["AutoGOConversational"][i]["x"], j["AutoGOConversational"][i]["y"], j["AutoGOConversational"][i]["w"], j["AutoGOConversational"][i]["h"],
				app->getResources()->getImageTexture(Resources::ImageId(n)), j["AutoGOConversational"][i]["convoName"], repeat));
		}

		// Cargado de decoracion
		obj = "Decorado";
		for (int i = 0; i < j[obj].size(); i++) {

			n = j[obj][i]["Texture"];
			Decorado* aux = new Decorado(app);
			aux->setPosition(Vector2D(j[obj][i]["x"], j[obj][i]["y"]));
			aux->setHeight(j[obj][i]["h"]);
			aux->setWidth(j[obj][i]["w"]);			

			if (!addAnimsFromJSON(aux, j[obj][i], n)) {
				ImageRenderer* im = new ImageRenderer(app->getResources()->getImageTexture(Resources::ImageId(n)));
				aux->addRenderComponent(im); //si no tiene animaciones, añade un render normal
			}

			readSoundEffect(aux, j[obj][i]);

			if (!j[obj][i]["rotation"].is_null()) {
				int n = j[obj][i]["rotation"];
				aux->setRotation(n);
			}
			SceneItems.push_back(aux);
		}


		//Cargado de NPCs
		obj = "NPC";
		for (int i = 0; i < j[obj].size(); i++) {

			n = j[obj][i]["Texture"];

			bool repeat_ = true;
			if (!j[obj][i]["repeatDialog"].is_null()) {
				repeat_ = j[obj][i]["repeatDialog"];
			}

			bool done = false;
			if (!j["NPC"][i]["done"].is_null()) {
				done = j["NPC"][i]["done"];
			}

			NPC* npc = new NPC(app, j[obj][i]["x"], j[obj][i]["y"], j[obj][i]["w"], j[obj][i]["h"], 
				app->getResources()->getImageTexture(Resources::ImageId(n)), j[obj][i]["dialogo"], repeat_, done);

			npc->addInputComponent(new FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar));

			SceneItems.push_back(npc);
			SceneItems.push_back(npc->getColisionable()); //pusheamos el colisionable asociado

			addAnimsFromJSON(npc, j[obj][i], n);

			readSoundEffect(npc, j[obj][i]);

			if (!j[obj][i]["rotation"].is_null()) {
				SceneItems.back()->setRotation(j[obj][i]["rotation"]);
			}
		}

		// Cargado de GOTransiciones
		obj = "GOTransiciones";
		for (int i = 0; i < j[obj].size(); i++) {

			n = j[obj][i]["Texture"];
			int soundId = 8;
			if (!j[obj][i]["soundEffect"].is_null())
				soundId = j[obj][i]["soundEffect"];
			GOTransiciones* goTrans = new GOTransiciones(app, j[obj][i]["x"], j[obj][i]["y"],
				j[obj][i]["w"], j[obj][i]["h"],
				app->getResources()->getImageTexture(Resources::ImageId(n)), j[obj][i]["scneNum"], soundId);

			goTrans->addInputComponent(new FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar));

			SceneItems.push_back(goTrans);

			addAnimsFromJSON(goTrans, j[obj][i], n);

			readSoundEffect(goTrans, j[obj][i]);

			if (!j[obj][i]["rotation"].is_null()) {
				SceneItems.back()->setRotation(j[obj][i]["rotation"]);
			}
		}

		// Cargado de GOCofres (valido para taquillas, cofres, cajas...)
		obj = "GOCofres";
		for (int i = 0; i < j[obj].size(); i++) {

			n = j[obj][i]["Texture"];
			double rotGOTrans = 0;
			if (!j[obj][i]["rotGOTr"].is_null())
				rotGOTrans = j[obj][i]["rotGOTr"];

			int id = -4;
			if (!j[obj][i]["UnlockId"].is_null())
				if (j[obj][i]["UnlockId"].is_number_integer()) {
					id = j[obj][i]["UnlockId"];
				}

			bool itPerm = false;
			if (!j[obj][i]["permanenteItem"].is_null()) {
				itPerm = j[obj][i]["permanenteItem"];
			}

			bool open = false;
			if (!j[obj][i]["open"].is_null()) {
				open = j[obj][i]["open"];
			}

			bool devuelveEstado = false;

			if (!j[obj][i]["generaState"].is_null()) {
				devuelveEstado = j[obj][i]["generaState"];
			}
			GOcofres* cofre = nullptr;
			if (devuelveEstado) {
				cofre = new GOcofres(app, j[obj][i]["x"], j[obj][i]["y"], j[obj][i]["w"], j[obj][i]["h"],
					app->getResources()->getImageTexture(Resources::ImageId(n)), j[obj][i]["tag"], id, puzzleAux);
			}
			else {
				cofre = new GOcofres(app, j[obj][i]["x"], j[obj][i]["y"], j[obj][i]["w"], j[obj][i]["h"],
					app->getResources()->getImageTexture(Resources::ImageId(n)), j[obj][i]["tag"], j[obj][i]["wItem"], j[obj][i]["hItem"], j[obj][i]["descripcionItem"], j[obj][i]["tagItem"],
					app->getResources()->getImageTexture(Resources::ImageId(j[obj][i]["numTextItem"])), j[obj][i]["xItem"], j[obj][i]["yItem"], itPerm, id, open);
			}

			cofre->addInputComponent(new FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar));

			SceneItems.push_back(cofre);
			addAnimsFromJSON(cofre, j[obj][i], n);

			readSoundEffect(cofre, j[obj][i]);

			if (!j[obj][i]["open"].is_null()) {
				if (j[obj][i]["open"]) {
					cofre->playAnim("Anim1");
				}
			}
			if (!j[obj][i]["rotation"].is_null()) {
				SceneItems.back()->setRotation(j[obj][i]["rotation"]);
			}
		}

		// Cargado de Colisiones
		obj = "CollisionableObject";
		for (int i = 0; i < j[obj].size(); i++) {

			n = j[obj][i]["Texture"];

			ColisionableObject* newCol = new ColisionableObject(app, j[obj][i]["x"], j[obj][i]["y"],
				j[obj][i]["w"], j[obj][i]["h"],
				app->getResources()->getImageTexture(Resources::ImageId(n)));

			SceneItems.push_back(newCol);

			addAnimsFromJSON(newCol, j[obj][i], n);

			readSoundEffect(newCol, j[obj][i]);

			if (!j[obj][i]["rotation"].is_null()) {
				SceneItems.back()->setRotation(j[obj][i]["rotation"]);
			}
		}

		// Cargado de GODoors
		obj = "Interruptores";
		for (int i = 0; i < j[obj].size(); i++) {

			n = j[obj][i]["Texture"];

			int id = -4;
			if (!j[obj][i]["UnlockId"].is_null())
				if (j[obj][i]["UnlockId"].is_number_integer()) {
					id = j[obj][i]["UnlockId"];
				}

			bool off = true;
			if (!j[obj][i]["off"].is_null()) {
				off = j[obj][i]["off"];
			}

			bool canWork = true;
			if (!j[obj][i]["canWork"].is_null()) {
				canWork = j[obj][i]["canWork"];
			}


			Interruptor* interr = new Interruptor(app, j[obj][i]["x"], j[obj][i]["y"], j[obj][i]["w"], j[obj][i]["h"],
				app->getResources()->getImageTexture(Resources::ImageId(n)), j[obj][i]["tag"], j[obj][i]["maxAlpha"], j[obj][i]["minAlpha"], id, off, canWork);

			interr->addInputComponent(new FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar));

			intAux_ = interr;

			SceneItems.push_back(interr);
			SceneItems.push_back(interr->getLuz());

			addAnimsFromJSON(interr, j[obj][i], n);

			readSoundEffect(interr, j[obj][i]);

			if (!j[obj][i]["rotation"].is_null()) {
				SceneItems.back()->setRotation(j[obj][i]["rotation"]);
			}
		}

		// Cargado de GODoors
		obj = "GODoors";
		for (int i = 0; i < j[obj].size(); i++) {

			n = j[obj][i]["Texture"];
			double rotGOTrans = 0;
			if(!j[obj][i]["rotGOTr"].is_null())
				rotGOTrans = j[obj][i]["rotGOTr"];
			int soundId = 8;
			if (!j[obj][i]["soundEffect"].is_null())
				soundId = j[obj][i]["soundEffect"];
			int id = -4;
			if (!j[obj][i]["UnlockId"].is_null())
				if (j[obj][i]["UnlockId"].is_number_integer()) {
					id = j[obj][i]["UnlockId"];
				}

			GODoors* door = new GODoors(app, j[obj][i]["x"], j[obj][i]["y"], j[obj][i]["w"], j[obj][i]["h"],
				app->getResources()->getImageTexture(Resources::ImageId(n)), j[obj][i]["tag"], j[obj][i]["scneNum"], soundId, rotGOTrans, id);

			door->addInputComponent(new FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar));

			SceneItems.push_back(door);
			addAnimsFromJSON(door, j[obj][i], n);

			readSoundEffect(door, j[obj][i]);
			
			if (!j[obj][i]["rotation"].is_null()) {
				SceneItems.back()->setRotation(j[obj][i]["rotation"]);
			}
		}


		//ESCENARIO

		if(!j["Texture"].is_null()) n = j["Texture"];
		else n = 0;

		Entity* escenario = new Entity(app);

		if (j["w"].is_null())
			escenario->setWidth(app->getWindowWidth());
		else escenario->setWidth(j["w"]);

		if (j["h"].is_null())
			escenario->setHeight(app->getWindowHeight());
		else escenario->setHeight(j["h"]);

		width = escenario->getWidth();
		height = escenario->getHeight();

		Vector2D pos;
		if (j["x"].is_null())
			pos.setX(0);
		else
			pos.setX(j["x"]);
		
		if (j["y"].is_null())
			pos.setY(0);
		else
			pos.setY(j["y"]);

		escenario->setPosition(pos);
		x = escenario->getPosition().getX();
		y = escenario->getPosition().getY();

		if (j["PlayerPos"].is_object()) {
			posIni.setX(j["PlayerPos"]["x"]);
			posIni.setY(j["PlayerPos"]["y"]);
		}

		if (!j["AlenaActiva"].is_null()) { alenaActiva = j["AlenaActiva"]; }

		//guardamos su tamaño dependiendo de lo que ponga en el json
		if (j["PlayerTam"].is_object()) {
			playerTam.setX(j["PlayerTam"]["w"]);
			playerTam.setY(j["PlayerTam"]["h"]);
		}//si en el json no se especificaba nada, se queda con un tamaño por defecto
		else playerTam.set({ pj->defaultW, pj->defaultH });

		RenderComponent* renderEscenario = new ImageRenderer(app->getResources()->getImageTexture(Resources::ImageId(n)));
		escenario->addRenderComponent(renderEscenario);
		if (addAnimsFromJSON(escenario, j, n)) {
			delete renderEscenario;
		}
		SceneItems.push_back(escenario);
		i.close();
	}
	else {
		cout << "No existe el archivo " << name;
	}
}

Scene::~Scene()
{
	list<GameObject*>::iterator aux;
	for (aux = SceneItems.begin(); aux != SceneItems.end();) {
		delete *aux;
		aux = SceneItems.erase(aux); //aux = aux++
	}

	list<GameState*>::iterator stateIt;
	for (stateIt = SceneStates.begin(); stateIt != SceneStates.end();) {
		if(!app->getStateMachine()->checkElement(*stateIt)) delete *stateIt; //si no está dentro de la pila en el momento de borrar todo, se borra. Si está, no se borra ya que ya ha sido borrado
		stateIt = SceneStates.erase(stateIt); //aux = aux++
	}
}

void Scene::enterScene() {
	SceneEvent* trackEvent = Tracker::GetInstance().createSceneEvent();
	trackEvent->setParameters(SceneNum, ENTER);
	Tracker::GetInstance().trackEvent(trackEvent);

	CurrentState = app->getStateMachine()->currentState();
	//Iniciamos ite, saltamos primer ite(jugador) borrarmos el resto de items copiamos nuestra lista
	it = CurrentState->getStage()->begin();
	it++; it++;
	app->getStateMachine()->currentState()->changeList();

	while (it != CurrentState->getStage()->end()) {//Mientras no se acaben los items
		
		it = CurrentState->getStage()->erase(it);//borramos el item
	}
	CurrentState->getStage()->insert(CurrentState->getStage()->end(), SceneItems.begin(), SceneItems.end());

	send(&Mensaje(SetZBufferPlayState)); //mensaje para recolocar el zBuffer

	for (GameObject* it : SceneItems) {
		if(it->getType() == GameObject::Collider) //casteo personalizado
			pj->setNewCollision(it);
	}

	if(music) CurrentState->playMusicScene(SceneMusic, musicVolume);
	if (stopMusic)CurrentState->stopActualMusic();
	CurrentState->playSoundEffects(SceneSoundEffects, numReps_, volumenes);

	//establecemos el tamaño de la nueva escena en el jugador (para las colisiones y el mouse)
	pj->setSceneTam(width, height, x, y);

	//limpiamos las pilas de teclas para evitar errores entre cambios de escena
	pj->cleanKeys();

	//establecemos su posicion inicial
	pj->setPosIni();

	//establecemos su tamaño
	pj->setTam();

	if (!alenaActiva) {
		pj->setActive(false);
	}
	else {
		pj->setActive(true);
	}

	//genera la matriz para el mouse
	pj->collisionListWasModified();

	app->getStateMachine()->currentState()->resetCursor();

	if (intAux_ != nullptr) {
		intAux_->setLight();
	}

	if (cambioActo) { cambioActo = false; app->getStateMachine()->pushState(new ActEndingScreen(app, actNumber_, headerActo)); } //CAMBIO ACTO
}

void Scene::exitScene() { //al salir de la escena, todos los objetos de stage se vuelcan en la lista de la escena para que se queden guardados (menos el jugador)
	SceneEvent* trackEvent = Tracker::GetInstance().createSceneEvent();
	trackEvent->setParameters(SceneNum, EXIT);
	Tracker::GetInstance().trackEvent(trackEvent);

	app->getStateMachine()->currentState()->changeList();
	SceneItems.clear();
	SceneItems = *(app->getStateMachine()->currentState()->getStage()); //la lista stage es igual a todos los objetos de la escena
	pj->clearCollisions(); //fuera colisiones
	SceneItems.pop_front(); //quitamos al jugador de la escena (es global). Se puede hacer as� o con un for que se salte el primero y copie los dem�s
	SceneItems.pop_front(); //quitamos al shortcut
	pj->setVelocity(Vector2D(0.0, 0.0));
	pj->getMouseComponent()->send(&Mensaje(MouseStop));
	pj->getMouseComponent()->send(&Mensaje(CambioEscena));
	this->setPosIni(pj->getPosition()); //funciona *_*
}


void Scene::saveSceneToJson() {
	string name = "..\\Scenes\\saves\\Scene" + to_string(SceneNum);
	name += ".json";

	std::ofstream i(name); //archivo donde se va a guardar
	json j;
	for (GameObject* it : SceneItems) {
		it->saveToJson(j);	//manda a todos los objetos guardarse en dichos archivos
	}

	j["PlayerPos"]["x"] = posIni.getX();
	j["PlayerPos"]["y"] = posIni.getY();

	j["PlayerTam"]["w"] = playerTam.getX();
	j["PlayerTam"]["h"] = playerTam.getY();

	j["AlenaActiva"] = alenaActiva;

	j["CambioActo"] = cambioActo;

	j["HeaderActo"] = headerActo;

	j["actNumber"] = actNumber_;

	while (!SceneSoundEffects.empty()) {
		j["SoundEffect"].push_back(SceneSoundEffects.front());
		SceneSoundEffects.pop();
	}

	if (music)j["Music"][0] = SceneMusic;
	j["StopActualMusic"][0] = stopMusic;
	j["MusicVolume"][0] = musicVolume;

	for (int vol : volumenes) {
		j["volumenes"].push_back(vol);
	}

	for (int n : numReps_) {
		j["numRepeticionesSonidos"].push_back(n);
	}

	i << std::setw(3) << j; //pretty identación para leer mejor el archivo
	i.close(); //cierra el flujo
}

GameState * Scene::PuzzleCreator(PuzzleTypes type, json& j){
	GameState* nPuzzle = nullptr;

	bool swapScene = false;
	if (!j["swapScene"].is_null())
		swapScene = j["swapScene"];

	switch (type)
	{
	case (Match3):
	{
		int aux = -4;
		if(!j["UnlockId"].is_null())
			aux = j["UnlockId"];

		nPuzzle = new Puzzle1State(app, app->getStateMachine()->currentState(), j["numberPuzzle"], j["numText"], aux, swapScene);
		break;
	}
	case (Lights):
	{
		int aux = -4;
		if (!j["UnlockId"].is_null())
			aux = j["UnlockId"];
		
		nPuzzle = new LightsOut(app, j["numCas"], j["dificultad"], aux, swapScene);
		break;
	}

	case (Password): 
	{
		int aux = -4;
		if (!j["UnlockId"].is_null())
			aux = j["UnlockId"];

		int fondo = -1;
		if (!j["TexturaFondo"].is_null())
			fondo = j["TexturaFondo"];

		nPuzzle = new PasswordState(app, j["posFontX"], j["posFontY"],j["password"], aux, fondo, swapScene);
		break;
	}
	default:
		break;
	}
	return nPuzzle;
}

bool Scene::addAnimsFromJSON(Entity* obj, json& j, const int numText){

	if (!j["animation"].is_null()) {
		if (j["animation"]) {
			Entity* col = obj;
			col->setAnimated(true);
			col->delEveryRenderComponent();
			for (unsigned int k = 0; k < j["Anims"].size(); k++) {
				col->addAnim("Anim" + to_string(k), j["Anims"][k], j["loop"], -1, j["vel"]);
			}

			col->addRenderComponent(new AnimationRenderer(
				app->getResources()->getImageTexture(Resources::ImageId(numText)), col->getAnimations(),
				 j["numColsFrame"], j["numFilsFrame"], j["widthFrame"], j["heightFrame"]));
			return true;
		}
	}
	return false;
}

void Scene::readSoundEffect(Entity * obj, json & j)
{
	if (!j["soundEffect"].is_null()) { //si el sonido no es null, se establece su valor
		obj->setSoundEffect(j["soundEffect"]);
	}
}
