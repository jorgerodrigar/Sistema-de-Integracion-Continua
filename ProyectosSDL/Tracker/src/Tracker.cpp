#include "Tracker.h"
#include "ITrackerAsset.h"
#include "TimeManager.h"
#include "IPersistence.h"
#include "FilePersistence.h"
#include "ServerPersistence.h"
#include "sha256.h"
#include <ctime>
#include <iostream>

// Static variable for the singleton
Tracker * Tracker::_instance = nullptr;

Tracker::Tracker()
{
	generateSessionId();
}

Tracker::~Tracker()
{
}

void Tracker::Init(const std::list<ITrackerAsset*>& trackerAssetList, const std::list<IPersistence*>& persistenceList)
{
	activeTrackers_ = trackerAssetList;
	_persistenceObjects = persistenceList;
}

void Tracker::End()
{
	for (std::list<IPersistence*>::iterator ite = _persistenceObjects.begin(); ite != _persistenceObjects.end(); ++ite)
		(*ite)->finalFlush(); 

	activeTrackers_.clear();
	_persistenceObjects.clear();

	TimeManager::ShutDownSingleton();
	ShutDownInstance();
}

Tracker & Tracker::GetInstance()
{
	// If there wasn't an instance created, create a new one
	if (Tracker::_instance == nullptr)
		Tracker::_instance = new Tracker();

	return *Tracker::_instance;
}

void Tracker::ShutDownInstance()
{
	if (_instance != nullptr) {
		delete Tracker::_instance;
		Tracker::_instance = nullptr;
	}
}

void Tracker::trackEvent(const TrackerEvent* trackerEvent)
{
	list<ITrackerAsset*>::iterator it = activeTrackers_.begin();
	while (it != activeTrackers_.end() && !(*it)->accept(trackerEvent)) { it++;	}
	if(it != activeTrackers_.end())
	{
		for (std::list<IPersistence*>::iterator ite = _persistenceObjects.begin(); ite != _persistenceObjects.end(); ++ite) {
			(*ite)->Send(trackerEvent);
		}
	}

	TrackerEvent::releasePointer(trackerEvent); // delete the event. Its already cloned in persistence
}

SessionStartEvent* Tracker::createSessionStartEvent()
{
	SessionStartEvent* event = new SessionStartEvent(TimeManager::GetSingleton()->getTimeSinceBeginning(), id_);
	return event;
}

SessionEndEvent* Tracker::createSessionEndEvent()
{
	SessionEndEvent* event = new SessionEndEvent(TimeManager::GetSingleton()->getTimeSinceBeginning(), id_);
	return event; 
}

TestEvent* Tracker::createTestEvent()
{
	TestEvent* event = new TestEvent(TimeManager::GetSingleton()->getTimeSinceBeginning(), id_);
	return event;
}

SceneEvent* Tracker::createSceneEvent()
{
	SceneEvent* event = new SceneEvent(TimeManager::GetSingleton()->getTimeSinceBeginning(), id_);
	return event;
}

LightPuzzleEvent* Tracker::createLightPuzzleEvent()
{
	LightPuzzleEvent* event = new LightPuzzleEvent(TimeManager::GetSingleton()->getTimeSinceBeginning(), id_);
	return event;
}

Connect4Event* Tracker::createConnect4Event()
{
	Connect4Event* event = new Connect4Event(TimeManager::GetSingleton()->getTimeSinceBeginning(), id_);
	return event;
}

ClickSceneEvent* Tracker::createClickSceneEvent()
{
	ClickSceneEvent* event = new ClickSceneEvent(TimeManager::GetSingleton()->getTimeSinceBeginning(), id_);
	return event;
}

ClickPuzzleEvent* Tracker::createClickPuzzleEvent()
{
	ClickPuzzleEvent* event = new ClickPuzzleEvent(TimeManager::GetSingleton()->getTimeSinceBeginning(), id_);
	return event;
}

void Tracker::generateSessionId()
{
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);

	id_ = sha256(dt);

	std::cout << id_ << " " << dt << std::endl;
}
