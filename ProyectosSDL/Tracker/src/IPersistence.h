#pragma once
#include "TrackerEvents.h"
#include "ISerializer.h"
#include <string>
#include <list>
#include "ConcurrentQueue.h"
#include <thread>

// interfaz de persistencia, con metodos para recibir eventos y persistirlos
// utiliza una hebra para persistir los eventos concurrentemente
class IPersistence
{
public:
	IPersistence() {};
	virtual ~IPersistence() {};

	// se recibe un evento, se añade a la cola, y si esta supera el tamaño maximo se persisten todos los eventos
	inline void Send(const TrackerEvent* trackerEvent) 
	{
		const TrackerEvent* clone = trackerEvent->clone(); //pushes the pointer's clone
		_eventQueue.push(clone);

		if (_eventQueue.size() >= MAX_EVENTS)
		{
			Flush();
		}
		//std::cout << "PUSH" << std::endl;
		//std::cout << "event sent" << std::endl;
	};

	// si la hebra de persistencia ha acabado de hacer flush, se hace otro flush
	// si no, no hace nada
	virtual void Flush() = 0;

	inline void release() 
	{
		if (thread_.joinable()) {
			thread_.join();
		}
	};

	// flush final de los eventos -> persiste todos los eventos que queden en la cola
	inline virtual void finalFlush() {
		while (!_eventQueue.empty()) {			
			Flush();
		}
	};

protected:
	// thread
	std::thread thread_;

	std::list<ISerializer*> _serializeObjects; //list of active formats
	
	ConcurrentQueue<const TrackerEvent*> _eventQueue; //stored events pending flush operation
	
	const int MAX_EVENTS = 20; //max queue storage

	// recorrera la lista de serializadores para persistir cada evento en cada uno de los formatos
	virtual void protectedFlush() = 0;

	bool threadFinished_ = true;
	std::mutex mutex_;
};

