#include "Timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::update(GameObject * o, Uint32 time)
{
	if (on && time > (actualTime_ + temporizador_)) {

		if(fun_ != nullptr) fun_();
		else { cout << "no se que hacer pero ha pasado el tiempo"; }
		on = false;

	}
}

void Timer::start()
{
	actualTime_ = SDL_GetTicks(); //ticks de sdl
	on = true;
}
