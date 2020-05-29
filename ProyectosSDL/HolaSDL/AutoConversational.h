#pragma once
#include "GOConversational.h"
class AutoConversational :
	public GOConversational
{
public:
	AutoConversational(SDLApp* game, int x, int y, int w, int h, Texture* texture, string convoName, bool repeat = true) : GOConversational(game, x, y, w, h, texture, convoName, repeat) {};
	AutoConversational();
	~AutoConversational();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void saveToJson(json& j) {
		json aux; Entity::saveToJson(aux);
		aux["convoName"] = convoName_;  aux["repeat"] = repeat_; j["AutoGOConversational"].push_back(aux);
	};
};

