#pragma once
#include "InputComponent.h"
#include "Entity.h"
#include "SDLApp.h"

class FeedbackCursorInputComponent :
	public InputComponent
{
private:
	Entity* cursor_;
	bool isMe = false;
	Resources::SoundEffectId soundId_;
public:
	FeedbackCursorInputComponent();
	FeedbackCursorInputComponent(Entity* cursor, Resources::SoundEffectId soundId) : cursor_(cursor), soundId_(soundId) { addObserver(cursor_->getGame()->getSoundManager()); }
	virtual ~FeedbackCursorInputComponent();
	virtual void FeedbackCursorInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event);
};

