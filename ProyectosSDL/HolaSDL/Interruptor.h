#pragma once

#include "GOUnlockeable.h"
class Interruptor :
	public GOUnlockeable
{
private:
	Entity* luz_;
	int maxAlpha_;
	int minAlpha_;
	ImageRenderer* ausenciaDeLuz;
	bool off_ = true;
	bool canWork_ = false;
	virtual void saveToJson(json& j) { if (this->isActive()) { json aux; Entity::saveToJson(aux); aux["tag"] = key; aux["maxAlpha"] = maxAlpha_; aux["minAlpha"] = minAlpha_; aux["off"] = !off_;
		aux["canWork"] = canWork_; j["Interruptores"].push_back(aux); } };
public:
	Interruptor();
	~Interruptor();
	Interruptor(SDLApp* app, int x, int y, int w, int h, Texture* txt, string tag, int maxAlpha, int minAlpha, char id = NULL, bool on = true, bool canWork = true);
	virtual void act();
	virtual void secondAct();
	void changeLight();
	void setLight();
	Entity* getLuz() const { return luz_; };
};

