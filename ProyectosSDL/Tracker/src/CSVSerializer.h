#pragma once
#include "ISerializer.h"
#include <fstream>
#include "json.hpp"
#include <string>


using namespace nlohmann;
using namespace std;

class CSVSerializer: public ISerializer
{
public:
	CSVSerializer();

	/// <summary>
	/// Returns the event serialized in csv format
	/// </summary>
	string Serialize(const TrackerEvent* event);

	/// <summary>
	/// Returns format name to be added to the file name 
	/// </summary>
	inline string Format() { return "csv"; };

	~CSVSerializer();
};

