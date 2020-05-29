#pragma once
#include "Entity.h"
#include "Timer.h"

class GOTimer :
	public Entity
{
private:
	Timer timerino;
public:
	GOTimer();
	virtual ~GOTimer();
	GOTimer(int tiempo, function<void()> fun_) { timerino = Timer(tiempo, fun_); this->addPhysicsComponent(&timerino); };
	void startTimer() { timerino.start(); };
};

