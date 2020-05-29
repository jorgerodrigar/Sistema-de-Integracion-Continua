#pragma once
#include "checkML.h"
#include "GODoors.h"
#include "json.hpp"
#include "ItemInventario.h"
#include "GOTransiciones.h"
#include "ColisionableObject.h"
#include <fstream>
#include "Puzzle.h"
#include "Interruptor.h"
#include <queue>

using json = nlohmann::json;

class MainCharacter;
class Scene: public Observable
{
public:
	Scene();
	Scene(int numEscena, SDLApp* app, MainCharacter* pj, Observer* playState, bool load = false);
	~Scene();
	void enterScene();
	void exitScene();
	int getSceneNumber() const { return SceneNum; };
	void saveSceneToJson();
	Vector2D getPosIni() { return posIni; }
	Vector2D getPlayerTam() { return playerTam; }
	void setPosIni(Vector2D newPos) { posIni = newPos; }
private:
	SDLApp* app;
	int SceneNum;
	list<GameObject*> SceneItems;
	list<GameState*> SceneStates;
	Resources::MusicId SceneMusic;
	bool music = false;
	bool stopMusic = false;
	queue<Resources::SoundEffectId> SceneSoundEffects;
	vector <int> volumenes;
	vector <int> numReps_;
	bool alenaActiva = true;
	enum PuzzleTypes {Match3, Lights, Password}; //para la lectura del json
	list<GameObject*>::iterator it;
	GameState* CurrentState;
	MainCharacter* pj;
	Interruptor* intAux_ = nullptr;
	double width = 0, height = 0, x = 0, y = 0;
	Vector2D posIni, playerTam;
	GameState* PuzzleCreator(PuzzleTypes type, json& j); //dependiendo del tag, elige un puzzle u otro (podemos tener mas de dos)
	bool addAnimsFromJSON(Entity* obj, json& j, const int numText);
	void readSoundEffect(Entity* obj, json& j);
	bool cambioActo = false;
	string headerActo;
	int actNumber_ = -1;
	int musicVolume = 0;
};

