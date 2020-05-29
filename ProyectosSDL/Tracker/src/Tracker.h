#pragma once

#include <list>
#include "TrackerEvents.h"
#include <string>
#include <thread>

struct ITrackerAsset;
class IPersistence;

// clase que gestiona el sistema de telemetria
class Tracker
{
public:
	Tracker();
	~Tracker();

	// inicializacion del tracker, recibiendo los trackerAssets y persistencias deseadas
	void Init(const std::list<ITrackerAsset*>& trackerAssetList, const std::list<IPersistence*>& persistenceList);
	// libera los recursos del tracker. Se persisten todos los eventos que quedasen pendientes en la cola
	void End();

	/// <summary>
	/// Returns the singleton for the tracker
	/// </summary>
	static Tracker& GetInstance();

	/// <summary>
	/// Releases the instance created previously
	/// </summary>
	static void ShutDownInstance();

	// dado un trackerEvent, si alguno de sus trackerAssets lo acepta, se pasa un clon de ese evento a cada
	// objeto de persistencia. Por ultimo, se libera el evento recibido. Llamado desde instrumentalizacion
	void trackEvent(const TrackerEvent* trackerEvent);

	// metodos factoria que crean un evento del tipo correspondiente y lo devuelve (llamados desde instrumentalizacion)
	TestEvent* createTestEvent();
	SceneEvent* createSceneEvent();
	LightPuzzleEvent* createLightPuzzleEvent();
	Connect4Event* createConnect4Event();
	ClickSceneEvent* createClickSceneEvent();
	ClickPuzzleEvent* createClickPuzzleEvent();
	SessionStartEvent* createSessionStartEvent();
	SessionEndEvent* createSessionEndEvent();

	// devuelve el id de la sesion
	inline std::string GetSessionID() { return id_; };

private:
	unsigned int listSize_;

	// genera un id de sesion aplicando sha256 a una cadena inicial
	void generateSessionId();

	std::list<ITrackerAsset*> activeTrackers_;

	std::string id_;

	static Tracker* _instance;
	std::list<IPersistence*> _persistenceObjects; //active persistence types
};
