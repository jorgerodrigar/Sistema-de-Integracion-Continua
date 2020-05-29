#pragma once
#include "IPersistence.h"
#include <queue>

class ServerPersistence : public IPersistence
{
public:
	ServerPersistence(const std::list<ISerializer*> serializers);

	virtual void Flush();
	virtual ~ServerPersistence();

protected:
	/// <summary>
	/// Applies persistence to the stored events in the queue sending them to a server
	/// </summary>
	virtual void protectedFlush();
};

