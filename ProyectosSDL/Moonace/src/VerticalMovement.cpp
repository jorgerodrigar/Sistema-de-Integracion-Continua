#include "VerticalMovement.h"



VerticalMovement::VerticalMovement(Vector2D vel): vel_(vel)
{
}


VerticalMovement::~VerticalMovement()
{
}

void VerticalMovement::update(GameObject * o, Uint32 time)
{
	Vector2D position = o->getPosition();
	Vector2D velocity = vel_;

	position = position + velocity;//actualizamos posicion en funcion de la velocidad

	o->setPosition(position);
}
