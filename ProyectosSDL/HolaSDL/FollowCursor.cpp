#include "FollowCursor.h"



FollowCursor::FollowCursor()
{
}


FollowCursor::~FollowCursor()
{
}

void FollowCursor::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_MOUSEMOTION) {

		o->setPosition(Vector2D(event.button.x, event.button.y));

	}
}
