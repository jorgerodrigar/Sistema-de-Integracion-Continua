#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include <string>
#include "json.hpp"
#include "Observable.h"


using namespace std;
using json = nlohmann::json;

class SDLApp;
class Texture;
class GameObject: public Observable, public Observer
{
public:
	enum Type { Collider, ItInventario, Doors, Default };
	GameObject();
	GameObject(SDLApp* game, int _id = -4) :app(game), _id(_id), active_(true), objectType(Default), soundEffect_(1) {}
	virtual ~GameObject();

	// abstract methods to be implemented in sub-classes
	virtual void handleInput(Uint32 time, const SDL_Event& event) = 0;
	virtual void update(Uint32 time) = 0;
	virtual void render(Uint32 time) = 0;
	virtual Texture* getTexture(Uint16 pos) const = 0;

	Vector2D getPosition() const{
		return position_;
	}

	Vector2D getVelocity() const{
		return velocity_;
	}

	Vector2D getDirection() const{
		return direction_;
	}

	int getCurrentAnim() const { return currentAnim; };

	double getWidth() const {
		return width_;
	}

	double getHeight() const{
		return height_;
	}

	double getAngle() const{
		return rotation_;
	}

	SDLApp* getGame() const {
		return app;
	}

	bool isActive() const {
		return active_;
	}

	Type getType() const {
		return objectType;
	}

	int getSoundEffect() const {
		return soundEffect_;
	}

	void setWidth(double w) {
		width_ = w;
	}

	void setHeight(double h) {
		height_ = h;
	}

	void setRotation(double angle) {
		rotation_ = angle;
	}

	void setPosition(Vector2D newPos) {
		position_ = newPos;
	}

	void setVelocity(Vector2D velocity) {
		velocity_ = velocity;
	}

	void setDirection(Vector2D velocity) {
		velocity_ = velocity;
	}

	void setActive(bool nActive) {
		active_ = nActive;
	}

	void setCurrentAnim(int nAnim) {
		currentAnim = nAnim;
	}

	void setType(Type newType) {
		objectType = newType;
	}

	void setSoundEffect(int s) {
		soundEffect_ = s;
	}

	virtual void saveToJson(json& j) = 0;

	virtual void receive(Mensaje* msg) {};

	int _id;

protected:
	SDLApp* app;   // pointer to the game

	bool active_;   // indicates if the object is active

	double width_;  // width
	double height_; // height
	double rotation_ = 0; // rotation respecto de {0,1} (eje vertical positivo)

	Vector2D position_; // position
	Vector2D direction_; // angle in degrees (0) is considered facing left
	Vector2D velocity_; // direction

	int currentAnim = 0;

	int soundEffect_;

private:
	Type objectType;
};
#endif /* GAMEOBJECT_H_ */

