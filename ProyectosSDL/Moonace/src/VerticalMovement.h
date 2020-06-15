#pragma once
#include "PhysicsComponent.h"
class VerticalMovement :
	public PhysicsComponent
{
private:
	Vector2D vel_;
public:
	VerticalMovement(Vector2D vel = {0, -1});
	virtual ~VerticalMovement();
	virtual void update(GameObject* o, Uint32 time);
};

