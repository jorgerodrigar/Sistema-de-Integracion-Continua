#include "GOcofres.h"
#include "AnimationRenderer.h"
#include "MouseEventAnimComponent.h"

GOcofres::GOcofres(SDLApp * game, int x, int y, int w, int h, Texture * texture, string _tag, char id, GOstates * puzzle):GOUnlockeable(game, x, y, w, h, texture, _tag, id), puzzle(puzzle)
{
	if (puzzle != nullptr)
		puzzle->setActive(false);//Lo desactivamos
	guardado = true;
}

GOcofres::~GOcofres()
{
}

void GOcofres::secondAct()
{
	if (puzzle !=nullptr) {
		puzzle->setActive(true);//Activamos el item
	}
	else {
		this->playAnim("Anim1");

		list<GameObject*>::iterator it = app->getStateMachine()->currentState()->getStage()->begin();
		it++; it++;
		/*int x, y;
		x = this->getPosition().getX() + (this->getWidth() / 2) - 10;
		y = this->getPosition().getY() + (this->getHeight() / 2);*/
		ItemInventario* newItem_ = new ItemInventario(app, xItem, yItem, itmW, itmH, itmDesc, itmTag, itmTexture, imtPerm);
		newItem_->addAnim("Anim0", { 0 }, true, -1, 100);
		newItem_->addAnim("Anim1", { 1 }, true, -1, 100);
		newItem_->delEveryRenderComponent();
		newItem_->addRenderComponent(new AnimationRenderer(itmTexture, newItem_->getAnimations(), 1, 2, itmTexture->getWidth(), itmTexture->getHeight() / 2));
		newItem_->addInputComponent(new MouseEventAnimComponent(SDL_MOUSEMOTION, "Anim1", "Anim0"));
		newItem_->setAnimated(true);
		app->getStateMachine()->currentState()->getStage()->insert(it, newItem_);

		app->getStateMachine()->currentState()->changeList();

		opened = true;
	}
}


