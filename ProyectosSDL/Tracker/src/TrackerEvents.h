#pragma once
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

// TIPOS DE LOS EVENTOS
enum EventType	{ 
	TEST_EVENT,
	SESSION_START_EVENT,
	SESSION_END_EVENT,
	SCENE_EVENT,
	LIGHTPUZZLE_EVENT,
	CONNECT4_EVENT,
	CLICK_EVENT_SCENE,
	CLICK_EVENT_PUZZLE
};

// NOMBRE DE LOS TIPOS DE LOS EVENTOS (nombre que se escribe al serializarse)
const std::string eventTypes[] = {
	"TEST_EVENT",
	"SESSION_START_EVENT",
	"SESSION_END_EVENT",
	"SCENE_EVENT",
	"LIGHTPUZZLE_EVENT",
	"CONNECT4_EVENT",
	"CLICK_EVENT_SCENE",
	"CLICK_EVENT_PUZZLE"
};

// ACCIONES DE LOS EVENTOS
enum EventAction {
	NONE_ACTION,
	ENTER,
	EXIT,
	COMPLETE
};

// NOMBRE DE LAS ACCIONES DE LOS EVENTOS (nombre que se escribe al serializarse)
const std::string eventActions[] = {
	"NONE_ACTION",
	"ENTER",
	"EXIT",
	"COMPLETE"
};

// EVENTOS
// padre de todos los eventos. Tiene los campos comunes de todos los eventos: timeStamp, id de la sesion y tipo del evento
// Tiene metodos para serializar el evento, clonarse, etc.
struct TrackerEvent
{
protected:
	double timeStamp_;
	string id_;
	EventType type_;

public:
	TrackerEvent(double timeStamp, string id, EventType type) : timeStamp_(timeStamp), id_(id), type_(type) {}

	// serializacion a formato json
	virtual const string toJson() const;
	// serializacion a formato csv
	virtual const string toCSV() const;     

	// devuelve el tipo del evento
	inline const EventType getType() const { return type_; } 

	// clona y devuelve la copia del evento. Esto pide memoria dinamica, que tendra que liberarse mas tarde 
	virtual TrackerEvent* clone() const = 0;                 

	// libera la memoria del evento recibido
	static inline void releasePointer(const TrackerEvent* event) { delete event;  };
};

// EVENTO PARA TESTING
struct TestEvent : public TrackerEvent {
public:
	TestEvent(double timeStamp, string id) : TrackerEvent(timeStamp, id, TEST_EVENT) {}

	virtual const string toJson() const;
	virtual const string toCSV() const;

	virtual TrackerEvent* clone() const;
};

//EVENTOS DE INICIO Y FIN DE SESION
struct SessionStartEvent : public TrackerEvent {
public:
	SessionStartEvent(double timeStamp, string id) : TrackerEvent(timeStamp, id, SESSION_START_EVENT) { std::cout << "SESSION START " << std::endl; }
	virtual TrackerEvent* clone() const;
};

struct SessionEndEvent : public TrackerEvent {
public:
	SessionEndEvent(double timeStamp, string id) : TrackerEvent(timeStamp, id, SESSION_END_EVENT) { std::cout << "SESSION END " << std::endl; }
	virtual TrackerEvent* clone() const;
};

// EVENTO DE ESCENA
struct SceneEvent : public TrackerEvent {
private:
	int numScene_;
	EventAction action_;

public:
	SceneEvent(double timeStamp, string id) : TrackerEvent(timeStamp, id, SCENE_EVENT), numScene_(0), action_(NONE_ACTION) {}

	inline void setParameters(int numScene, EventAction action) { numScene_ = numScene; action_ = action; std::cout << "SCENE " << numScene_ << " " << eventActions[action] << std::endl; }
	virtual const string toJson() const;
	virtual const string toCSV() const;

	virtual TrackerEvent* clone() const;
};

// EVENTOS DE PUZLE
// padre de LightPuzzle y Connect4
struct PuzzleEvent : public TrackerEvent {
protected: // de esta forma no se pueden hacer instancias de PuzzleEvent
	int numPuzzle_;
	EventAction action_;
	PuzzleEvent(double timeStamp, string id, EventType eventType) : TrackerEvent(timeStamp, id, eventType), numPuzzle_(0), action_(NONE_ACTION) {}

public:
	inline void setParameters(int numPuzzle, EventAction action) { numPuzzle_ = numPuzzle; action_ = action; std::cout << "PUZZLE " << numPuzzle_ << " " << eventActions[action] << std::endl; }
	virtual const string toJson() const;
	virtual const string toCSV() const;
};

struct Connect4Event : public PuzzleEvent {
public:
	Connect4Event(double timeStamp, string id) : PuzzleEvent(timeStamp, id, CONNECT4_EVENT) {}
	virtual TrackerEvent* clone() const;
};

struct LightPuzzleEvent : public PuzzleEvent {
public:
	LightPuzzleEvent(double timeStamp, string id) : PuzzleEvent(timeStamp, id, LIGHTPUZZLE_EVENT) {}
	virtual TrackerEvent* clone() const;
};

// EVENTO DE CLICK DEL JUGADOR
// padre de ClickSceneEvent y ClickPuzzleEvent
struct ClickEvent : public TrackerEvent {
protected:
	std::pair<int, int> pos_;
	ClickEvent(double timeStamp, string id, EventType type) : TrackerEvent(timeStamp, id, type), pos_({ 0, 0 }) {}

public:
	inline void setParameters(std::pair<int, int> pos) { pos_ = pos; }

	virtual const string toJson() const;
	virtual const string toCSV() const;
};

struct ClickSceneEvent : public ClickEvent {
private:
	int numScene_;

public:
	ClickSceneEvent(double timeStamp, string id) : ClickEvent(timeStamp, id, CLICK_EVENT_SCENE), numScene_(0) {}
	inline void setParameters(int numScene, std::pair<int, int> pos) {
		ClickEvent::setParameters(pos),	numScene_ = numScene; std::cout << "CLICK SCENE " << numScene_ << " " << pos_.first << " " << pos_.second << std::endl;
	}
	virtual const string toJson() const;
	virtual const string toCSV() const;

	virtual TrackerEvent* clone() const;
};


struct ClickPuzzleEvent : public ClickEvent {
private:
	int numPuzzle_;

public:
	ClickPuzzleEvent(double timeStamp, string id) : ClickEvent(timeStamp, id, CLICK_EVENT_PUZZLE), numPuzzle_(0) {}
	inline void setParameters(int numPuzzle, std::pair<int, int> pos) {
		ClickEvent::setParameters(pos), numPuzzle_ = numPuzzle; std::cout << "CLICK PUZZLE " << numPuzzle_ << " " << pos_.first << " " << pos_.second << std::endl;
	}
	virtual const string toJson() const;
	virtual const string toCSV() const;

	virtual TrackerEvent* clone() const;
};




