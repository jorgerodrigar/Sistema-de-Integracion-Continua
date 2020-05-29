#pragma once
#include "PhysicsComponent.h"
#include <functional>

class Timer :
	public PhysicsComponent
{
private:
	int temporizador_;
	int actualTime_ = 0;
	function<void()> fun_;
	bool on = false;
	
public:
	Timer();
	virtual ~Timer();
	Timer(int temporizador, function<void()> fun = nullptr) : temporizador_(temporizador), fun_(fun) {};
	virtual void update(GameObject* o, Uint32 time);
	void start();
};

