#include "FeedbackCursorInputComponent.h"
#include "Entity.h"


FeedbackCursorInputComponent::FeedbackCursorInputComponent()
{
}


FeedbackCursorInputComponent::~FeedbackCursorInputComponent()
{
}

void FeedbackCursorInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_MOUSEMOTION) {
		SDL_Point p;
		p.x = event.button.x;
		p.y = event.button.y;

		SDL_Rect rect;
		rect.x = o->getPosition().getX();
		rect.y = o->getPosition().getY();
		rect.w = o->getWidth();
		rect.h = o->getHeight();

		if (SDL_PointInRect(&p, &rect)) {
			if (!isMe) {
				PlaySoundE msg = { soundId_, 0 };
				send(&msg);
				SoundEffectVolume vol = { soundId_, 10 };
				send(&vol);
			}
			cursor_->playAnim("Feedback");
			isMe = true;
		}
		else if (isMe) {
			cursor_->playAnim("Normal");
			isMe = false;
		}
	}
}
