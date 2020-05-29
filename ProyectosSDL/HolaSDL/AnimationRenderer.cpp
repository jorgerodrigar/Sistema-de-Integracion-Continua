#include "AnimationRenderer.h"


AnimationRenderer::AnimationRenderer(Texture* texture, vector<animData*> animations, int numColsFrames, int numFilsFrames,
	int frWidth, int frHeigth, Observer* obs) :
	texture_(texture), numFrCols_(numFilsFrames), numFrFils_(numColsFrames), frWidth_(frWidth), frHeigth_(frHeigth)
{
	currentAnim_ = 0;
	currentFrame_ = 0;

	numFrames = numFilsFrames * numColsFrames;
	timeNext = SDL_GetTicks();
	timeLastFrame = timeNext;
	nextAnim_ = currentAnim_;
	animations_ = animations;

	// si no hay animaciones, crea una con todos los frames de la textura
	if (animations_.size() == 0) {
		animData* aux = new animData();
		for (int i = 0; i < numFrames; i++) {
			aux->framesAnim_.push_back(i);
		}
		animations_.push_back(aux);
		aux = nullptr;
		delete aux;
	}

	playAnim(0);

	if (obs != nullptr) {
		this->addObserver(obs);
	}
}

AnimationRenderer::~AnimationRenderer()
{
	for (int i = 0; i < animations_.size(); i++)
		delete animations_[i];
	texture_ = nullptr;
}

void AnimationRenderer::render(GameObject* o, Uint32 time)
{
	timeNext = SDL_GetTicks();
	changeAnim();

	if (timeNext - timeLastFrame >= animations_[currentAnim_]->rate_) {

		calculateNextSourceRect();

		if (currentFrame_ == animations_[currentAnim_]->framesAnim_.size() - 1 && !observers_.empty()) {
			send(&Mensaje(ANIM_DONE));
		}

		if (animations_[currentAnim_]->framesAnim_.size() > 0)
			currentFrame_ = nextFrame();

		timeLastFrame = SDL_GetTicks();
	}

	SDL_Rect rect{ o->getPosition().getX(), o->getPosition().getY(),
		o->getWidth(), o->getHeight() };

	texture_->render(o->getGame()->getRenderer(), rect, o->getAngle(), &sourceRect);
	changeAnim();

}
void AnimationRenderer::playAnim(string label)
{
	int i = 0;
	while (i < animations_.size() && animations_[i]->label_ != label) i++;

	if (i < animations_.size()) { 
		nextAnim_ = i; 

		if (!animations_[nextAnim_]->loop_)
			changeAnim();
	}
}

void AnimationRenderer::changeAnim()
{
	// si la animacion siguiente no es la que ya esta puesta
	if (nextAnim_ != currentAnim_) {
		// si la actual es en loop
		if (animations_[currentAnim_]->loop_) {
			currentAnim_ = nextAnim_;
			currentFrame_ = 0;
		}
		else if(currentFrame_ >= animations_[currentAnim_]->framesAnim_.size()-1){
			currentAnim_ = nextAnim_;
			currentFrame_ = 0;
		}
	}
}

int AnimationRenderer::nextFrame()
{

	int aux = currentFrame_ + 1;

	// prueba si hay frame siguiente
	if (aux >= animations_[currentAnim_]->framesAnim_.size()) // si no hay
		if (animations_[currentAnim_]->loop_)  // si es loopeada, vuelve al principio
			aux = 0;
		else if (animations_[currentAnim_]->onEnded_ >= 0 && animations_[currentAnim_]->onEnded_ < animations_.size()) { // si no, y tiene animacion siguiente
			currentAnim_ = animations_[currentAnim_]->onEnded_; // la pone
			nextAnim_ = currentAnim_;
		}
		else
			aux = currentFrame_;
	return aux;
}

void AnimationRenderer::receive(Mensaje* msg)
{
	switch (msg->id_) {
	case Ch_Left:
		playAnim("Left");
		break;
	case Ch_Right:
		playAnim("Right");
		break;
	case StopRight:
		playAnim("IdleRight");
		break;
	case StopLeft:
		playAnim("IdleLeft");
		break;
	case Ch_TakeObj:
		playAnim("TakeObj");
		break;
	default:
		playAnim("Idle");
		break;
	}
}

void AnimationRenderer::calculateNextSourceRect()
{
	if (currentFrame_ < animations_[currentAnim_]->framesAnim_.size()) {
		int y = (animations_[currentAnim_]->framesAnim_[currentFrame_]) / numFrFils_;
		int x = (animations_[currentAnim_]->framesAnim_[currentFrame_]) % numFrFils_;

		y *= frHeigth_;
		x *= frWidth_;

		sourceRect = { x, y, frWidth_, frHeigth_ };
	}
}