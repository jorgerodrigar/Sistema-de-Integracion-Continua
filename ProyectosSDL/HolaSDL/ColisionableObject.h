#pragma once
#include "checkML.h"
#include "Entity.h"
#include "ImageRenderer.h"

class ColisionableObject :
	public Entity
{
public:
	ColisionableObject() { this->setType(Collider); }
	ColisionableObject(SDLApp* game, int x, int y, int w, int h, Texture* texture);
	virtual ~ColisionableObject() {
		this->delRenderComponent(&render);
	}
	virtual void saveToJson(json& j) { json aux; Entity::saveToJson(aux); j["CollisionableObject"].push_back(aux); };
private:
	ImageRenderer render;
};

