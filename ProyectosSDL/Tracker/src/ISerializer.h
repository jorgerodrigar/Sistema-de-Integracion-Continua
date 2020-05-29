#pragma once
#include <cstdio>
#include <string>
#include "TrackerEvents.h"
using namespace std;

//Serializer Interface 

class ISerializer 
{
public:
	/// <summary>
	/// Returns the event serialized in an especific format
	/// </summary>
	virtual string Serialize(const TrackerEvent* event) = 0;

	/// <summary>
	/// Returns format name to be added to the file name
	/// </summary>
	virtual string Format() = 0;
};
