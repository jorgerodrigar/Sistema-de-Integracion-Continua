#pragma once
#include "ColisionableObject.h"
#include "GOConversational.h"
class NPC :
	public GOConversational
{
private:
	ColisionableObject* obj;
	string convoName_;
public:
	NPC();
	NPC(SDLApp* game, int x, int y, int w, int h, Texture* texture, string convoName, bool repeat = true, bool done = false);
	virtual ~NPC();
	ColisionableObject* getColisionable() { return obj; };
	virtual void saveToJson(json& j) { json aux; Entity::saveToJson(aux); 
	aux["dialogo"] = convoName_;   aux["repeatDialog"] = repeat_; aux["done"] = done_; j["NPC"].push_back(aux); };
};

