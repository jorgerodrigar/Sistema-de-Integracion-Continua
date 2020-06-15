#pragma once
#include "ClickeableGO.h"
class CasillaLight :
	public ComponenteClickeable, public Entity
{
private:
	bool encendido;
	pair<const int, const int> pos_;
	ImageRenderer render;
	void updateText();
public:
	CasillaLight();
	virtual ~CasillaLight();
	CasillaLight(SDLApp* game, int x, int y, int w, int h, Texture* texture, Observer* obs);
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void act();
	void invertir();
	virtual void saveToJson(json& j) {};
	bool isOn() const { return encendido; };
	void setOn(bool on) { this->encendido = on; this->updateText(); };
};

