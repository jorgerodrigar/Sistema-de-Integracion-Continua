#pragma once
#include "InputComponent.h"
class FollowCursor :
	public InputComponent
{
public:
	FollowCursor();
	virtual ~FollowCursor();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};

