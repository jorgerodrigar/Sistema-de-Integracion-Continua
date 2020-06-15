#include "MouseEventAnimComponent.h"
#include "Entity.h"

MouseEventAnimComponent::~MouseEventAnimComponent()
{
}


void MouseEventAnimComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	Entity* aux = static_cast<Entity*>(o);
	if (aux->isAnimated()) {
		if (event.type == event_ && (button_ == -1 || event.button.button == button_ )) {
			SDL_Point p;
			p.x = event.button.x;
			p.y = event.button.y;

			SDL_Rect rect;
			rect.x = aux->getPosition().getX();
			rect.y = aux->getPosition().getY();
			rect.w = aux->getWidth();
			rect.h = aux->getHeight();

			if (SDL_PointInRect(&p, &rect)) {
				aux->playAnim(anim_);
			}
			else {
				aux->playAnim(defaultAnim_);
			}
		}
		else if(button_ != -1){
			aux->playAnim(defaultAnim_); //si hubiera manera de ver si esta haciendo play de una anim totalmente diferente (se puede hacer supongo), entonces se podria meter un boton con overlap y con click
		}
	}
}

