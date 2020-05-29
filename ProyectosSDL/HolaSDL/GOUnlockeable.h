#pragma once
#include "checkML.h"
#include "ClickeableGO.h"
class GOUnlockeable :
	public ClickeableGO
{
public:
	GOUnlockeable() {};
	GOUnlockeable(SDLApp* game, int x, int y, int w, int h, Texture* texture, string tag, char id = NULL) : ClickeableGO(game, x, y, w, h, texture), key(tag) { this->_id = id; };
	~GOUnlockeable() {};
	virtual void secondAct() = 0;
protected:
	bool opened = false;
	string key;
	virtual void act();
	virtual void saveToJson(json& j) = 0;
};

