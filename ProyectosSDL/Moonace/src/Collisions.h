#ifndef SRC_SIMPLEENGINE_BASE_COLLISIONS_H_
#define SRC_SIMPLEENGINE_BASE_COLLISIONS_H_

#include "checkML.h"
#include "Vector2D.h"
#include "GameObject.h"

/*
 *
 */
class Collisions {
public:
	Collisions();
	virtual ~Collisions();

	static bool collides(GameObject* o1, GameObject* o2);

};

#endif /* SRC_SIMPLEENGINE_BASE_COLLISIONS_H_ */
