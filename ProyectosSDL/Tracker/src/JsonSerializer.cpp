#include "JsonSerializer.h"

JsonSerializer::JsonSerializer() {

}

/// Returns the event serialized in json format
string JsonSerializer::Serialize(const TrackerEvent* event) {
	return event->toJson();
}

JsonSerializer::~JsonSerializer()
{
}