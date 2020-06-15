#pragma once

#include "sdl_includes.h"
#include <string>

class Music {
public:
	Music();
	Music(std::string fileName);
	virtual ~Music();

	bool load(std::string fileName);
	void play(int repetitions = -1);
	void stop();
	void pause();
	void resume();
	void close();
	void setVolume(int volume);
private:
	Mix_Music* music_;
};

