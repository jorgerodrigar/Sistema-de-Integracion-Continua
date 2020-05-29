#include "Interruptor.h"



Interruptor::Interruptor()
{
}


Interruptor::~Interruptor()
{
}

Interruptor::Interruptor(SDLApp* app, int x, int y, int w, int h, Texture* txt, string tag, int maxAlpha, int minAlpha, char id, bool on, bool canWork) : GOUnlockeable(app, x, y, w, h, txt, tag, id),
	maxAlpha_(maxAlpha), minAlpha_(minAlpha), off_(on), canWork_(canWork) {
	luz_ = new Entity(app);
	luz_->setWidth(app->getWindowWidth() + 100);
	luz_->setHeight(app->getWindowHeight() + 100);

	ausenciaDeLuz = new ImageRenderer(app->getResources()->getImageTexture(Resources::Luz));
	luz_->addRenderComponent(ausenciaDeLuz);

	changeLight();
}

void Interruptor::act()
{
	if (canWork_) {
		changeLight();
	}
}

void Interruptor::secondAct() {
	if (!canWork_) canWork_ = true;
}

void Interruptor::changeLight()
{
	if (off_) {
		luz_->getTexture()->changeAlpha(maxAlpha_);
		off_ = false;
	}
	else {
		luz_->getTexture()->changeAlpha(minAlpha_);
		off_ = true;
	}
}

void Interruptor::setLight()
{
	if (!off_) {
		if(luz_->getTexture() != nullptr)
			luz_->getTexture()->changeAlpha(maxAlpha_);
	}
	else {
		if (luz_->getTexture() != nullptr)
			luz_->getTexture()->changeAlpha(minAlpha_);
	}
}
