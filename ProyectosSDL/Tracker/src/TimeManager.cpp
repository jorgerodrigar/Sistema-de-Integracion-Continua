#include "TimeManager.h"

TimeManager* TimeManager::instance = nullptr;

TimeManager* TimeManager::GetSingleton()
{
	if (instance == nullptr) instance = new TimeManager();
	return instance;
}

void TimeManager::ShutDownSingleton()
{
	if (instance != nullptr) {
		delete instance; instance = nullptr;
	}
}

TimeManager::TimeManager()
{
	start_ = time(0);
}

TimeManager::~TimeManager()
{
}

double TimeManager::getTimeSinceBeginning()
{
	return difftime(time(0), start_);
}
