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
	virtual void secondAct() {};
	virtual void act(MainCharacter* player = nullptr);
	inline void setKey(std::string value) { key = value; };
	inline const bool isOpened() const { return opened; }
	inline const void setOpened(const bool value) { opened = value; }

protected:
	bool opened = false;
	string key;
	virtual void saveToJson(json& j) {};
};

