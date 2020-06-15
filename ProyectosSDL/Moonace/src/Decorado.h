#pragma once
#include "Entity.h"
class Decorado :
	public Entity
{
public:
	Decorado();
	virtual ~Decorado();
	Decorado(SDLApp* game) : Entity(game) {};
	virtual void saveToJson(json& j) { json aux; Entity::saveToJson(aux); j["Decorado"].push_back(aux); };
};

