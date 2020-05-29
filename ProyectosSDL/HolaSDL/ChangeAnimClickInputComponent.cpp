#include "ChangeAnimClickInputComponent.h"
#include "Entity.h"

ChangeAnimClickInputComponent::ChangeAnimClickInputComponent()
{
}

ChangeAnimClickInputComponent::ChangeAnimClickInputComponent(SDL_EventType evento, string anim1, string anim2, int button):event_(evento), anim1_(anim1), anim2_(anim2), button_(button)
{
}


ChangeAnimClickInputComponent::~ChangeAnimClickInputComponent()
{
}

void ChangeAnimClickInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	Entity* aux = static_cast<Entity*>(o);
	if (aux->isAnimated()) {
		if (event.type == event_ && event.button.button == button_) {
			SDL_Point p;
			p.x = event.button.x;
			p.y = event.button.y;

			SDL_Rect rect;
			rect.x = aux->getPosition().getX();
			rect.y = aux->getPosition().getY();
			rect.w = aux->getWidth();
			rect.h = aux->getHeight();


			if (SDL_PointInRect(&p, &rect)) {
				swap(anim1_, anim2_);
				aux->playAnim(anim1_);
			}
		}
	}
}
