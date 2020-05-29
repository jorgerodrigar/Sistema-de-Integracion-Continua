#include "CSVSerializer.h"



CSVSerializer::CSVSerializer()
{
}

/// Returns the event serialized in csv format
string CSVSerializer::Serialize(const TrackerEvent* event) 
{
	return event->toCSV();
}

CSVSerializer::~CSVSerializer()
{
}
