#include "TrackerEvents.h"
#include "json.hpp"
using namespace nlohmann;

const string TrackerEvent::toJson() const
{
	json j;
	//Elementos comunes del evento
	j["userID"] = id_;
	j["time"] = timeStamp_;
	j["type"] = eventTypes[type_]; // escribe el tipo de forma legible
	string result = j.dump();

	return result;
}

const string TrackerEvent::toCSV() const
{
	string timeStamp = to_string(timeStamp_);
	string type = eventTypes[type_]; // escribe el tipo de forma legible
	string result = "user id: " + id_ + ",time: " + timeStamp + ",type: " + type;
	//También se puede usar append y sstream, pero de momento lo dejo así que es lo mismo
	return result;
}

const string TestEvent::toJson() const
{
	//Aquí se meterían los atributos especificos del evento en el json
	string head = TrackerEvent::toJson();
	json j;
	//Elementos comunes del evento
	j["userID"] = id_;
	j["time"] = timeStamp_;
	string info = j.dump();
	string result = head + info;
	return result;
}

const string TestEvent::toCSV() const
{
	//Aquí irían los atributos específicos del evento en csv
	string head = TrackerEvent::toCSV();
	string timeStamp = to_string(timeStamp_);
	string result = head + ",user id: " + id_ + ",time: " + timeStamp;
	return result;
}

TrackerEvent* TestEvent::clone() const
{
	return new TestEvent(timeStamp_, id_);
}

const string SceneEvent::toJson() const
{
	//Habría que mirar la legibilidad 
	string head = TrackerEvent::toJson();
	json j;
	j["Number scene"] = numScene_;
	j["Action"] = eventActions[action_];
	string info = j.dump();
	string result = head + info;
	return result;
}

const string SceneEvent::toCSV() const
{
	//Revisar
	string head = TrackerEvent::toCSV();
	string result = head + ",Number scene: " + to_string(numScene_) + ",Action: " + eventActions[action_];
	return result;
}

TrackerEvent* SceneEvent::clone() const
{
	SceneEvent* aux = new SceneEvent(timeStamp_, id_);
	aux->setParameters(numScene_, action_);

	return aux;
}

const string PuzzleEvent::toJson() const
{
	string head = TrackerEvent::toJson();
	json j;
	j["Number puzzle"] = numPuzzle_;
	j["Action"] = eventActions[action_];
	string info = j.dump();
	string result = head + info;
	return result;
}

const string PuzzleEvent::toCSV() const
{
	string head = TrackerEvent::toCSV();
	string result = head + ",Number puzzle: " + to_string(numPuzzle_) + ",Action: " + eventActions[action_];
	return result;
}

const string ClickEvent::toJson() const
{
	string head = TrackerEvent::toJson();
	json j;
	j["Position_X"] = pos_.first;
	j["Position_Y"] = pos_.second;
	string info = j.dump();
	string result = head + info;
	return result;
}

const string ClickEvent::toCSV() const
{
	string head = TrackerEvent::toCSV();
	string result = head + ",Position_X: " + to_string(pos_.first) +
		",Position_Y: " + to_string(pos_.second);
	return result;
}

const string ClickSceneEvent::toJson() const
{
	string head = ClickEvent::toJson();
	json j;
	j["Number scene"] = numScene_;
	string info = j.dump();
	string result = head + info;
	
	return result;
}

const string ClickSceneEvent::toCSV() const
{
	string head = ClickEvent::toCSV();
	string result = head + ",Number scene: " + to_string(numScene_);
	return result;
}

TrackerEvent* ClickSceneEvent::clone() const
{
	ClickSceneEvent* aux = new ClickSceneEvent(timeStamp_, id_);
	aux->setParameters(numScene_, pos_);

	return aux;
}

const string ClickPuzzleEvent::toJson() const
{
	string head = ClickEvent::toJson();
	json j;
	j["Number puzzle"] = numPuzzle_;
	string info = j.dump();
	string result = head + info;

	return result;
}

const string ClickPuzzleEvent::toCSV() const
{
	string head = ClickEvent::toCSV();
	string result = head + ",Number puzzle: " + to_string(numPuzzle_);
	return result;
}

TrackerEvent* ClickPuzzleEvent::clone() const
{
	ClickPuzzleEvent* aux = new ClickPuzzleEvent(timeStamp_, id_);
	aux->setParameters(numPuzzle_, pos_);

	return aux;
}

TrackerEvent* SessionStartEvent::clone() const
{
	return new SessionStartEvent(timeStamp_, id_);
}

TrackerEvent* SessionEndEvent::clone() const
{
	return new SessionEndEvent(timeStamp_, id_);
}

TrackerEvent* Connect4Event::clone() const
{
	Connect4Event* aux = new Connect4Event(timeStamp_, id_);
	aux->setParameters(numPuzzle_, action_);

	return aux;
}

TrackerEvent* LightPuzzleEvent::clone() const
{
	LightPuzzleEvent* aux = new LightPuzzleEvent(timeStamp_, id_);
	aux->setParameters(numPuzzle_, action_);

	return aux;
}
