#pragma once
#include "ISerializer.h"
#include <fstream>
#include "json.hpp"
#include <string>


using namespace nlohmann;
using namespace std;

class JsonSerializer : public ISerializer 
{
public:
	JsonSerializer();
	
	/// <summary>
	/// Returns the event serialized in json format
	/// </summary>
	string Serialize(const TrackerEvent* event);

	/// <summary>
	/// Returns format name to be added to the file name 
	/// </summary>
	inline string Format() { return "json"; };

	~JsonSerializer();
};
