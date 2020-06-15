#include "GOTimer.h"



GOTimer::GOTimer()
{
}


GOTimer::~GOTimer()
{
	this->delPhysicsComponent(&timerino);
}
