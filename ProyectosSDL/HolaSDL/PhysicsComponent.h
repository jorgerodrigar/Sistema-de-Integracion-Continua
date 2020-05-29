#ifndef PHYSICSCOMPONENT_H_
#define PHYSICSCOMPONENT_H_
#include "checkML.h"
#include "GameObject.h"
#include "Collisions.h"

/*
 *
 */
class PhysicsComponent {
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void update(GameObject* o, Uint32 time) = 0;
};

#endif /* PHYSICSCOMPONENT_H_ */
