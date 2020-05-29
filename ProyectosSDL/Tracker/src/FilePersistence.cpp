#include "FilePersistence.h"
#include "Tracker.h"
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <Windows.h>


FilePersistence::FilePersistence(const std::list<ISerializer*> serializers)
{
	//Gets files' path & creates directory if it doesn't exist
	_commonPath = _SOLUTIONDIR;
	_commonPath += "\logs\\";
	_mkdir(_commonPath.c_str());

	//Common path file name
	_commonPath.append("\\" + Tracker::GetInstance().GetSessionID() + ".");

	_serializeObjects = serializers;
	
}

FilePersistence::~FilePersistence()
{
}

void FilePersistence::Flush()
{
	mutex_.lock();

	if (threadFinished_) {
		std::cout << "flushingFile" << std::endl;
		threadFinished_ = false;
		mutex_.unlock();
		if (thread_.joinable())
			thread_.join();

		thread_ = std::thread(&FilePersistence::protectedFlush, this);
	}
	else {
		mutex_.unlock();
	}
}

/// Applies persistence to the stored events in the queue
void FilePersistence::protectedFlush()
{
	unsigned int i = 0;
	while(!_eventQueue.empty() && i < MAX_EVENTS)
	{
		const TrackerEvent* event = _eventQueue.pop();

		std::ofstream file; 
		//write pending events
		//serializes the event in all availlable formats
		for (std::list<ISerializer*>::iterator it = _serializeObjects.begin(); it != _serializeObjects.end(); ++it)
		{
			std::string path;
			path.append(_commonPath + (*it)->Format());
			file.open(path, std::ios::out | std::ios::app);

			std::string stringEvent = (*it)->Serialize(event);
			file << stringEvent << '\n'; //writes the event to the file

			file.close();
		}

		TrackerEvent::releasePointer(event);
		i++;
	}

	mutex_.lock();
	threadFinished_ = true;
	mutex_.unlock();
}

