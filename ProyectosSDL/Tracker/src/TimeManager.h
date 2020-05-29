#pragma once
#include <list>
#include <time.h>

class TimeManager
{
private:
	static TimeManager* instance;
	time_t start_;

	TimeManager();
	~TimeManager();

public:
	static TimeManager* GetSingleton();
	static void ShutDownSingleton();

	/// returns time since glfwInit()
	double getTimeSinceBeginning();
};

