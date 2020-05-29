#pragma once
#include "checkML.h"
#include "RenderComponent.h"
#include "Observer.h"
#include "SDLApp.h"
#include "AnimationData.h"

class AnimationRenderer :
	public RenderComponent, public Observer, public Observable
{
public:
	AnimationRenderer() {};
	AnimationRenderer(Texture* texture, vector<animData*> animations, int numColsFrames, int numFilsFrames, int frWidth, int frHeigth, Observer* obs = nullptr);

	virtual ~AnimationRenderer();
	virtual void render(GameObject* o, Uint32 time);
	virtual Texture* getTexture() const { return texture_; };
	virtual void setTexture(Texture* newText) { this->texture_ = newText; };

	// añade una animacion al vector
	virtual void addAnim(string label, vector<int> framesAnim, bool loop = true, double rate = ANIM_RATE) 
	{
		animData* newAnim = new animData(label, framesAnim, loop, rate); animations_.push_back(newAnim);
	}

	// inicia la animacion de entrada o pone la 0 en caso de no encontrarla
	virtual void playAnim(string label);
	virtual void playAnim(int anim) {(anim < animations_.size() && anim >= 0) ? (nextAnim_ = anim) : (nextAnim_ = currentAnim_); // operador ternario (if)?(true):(false);
	if (nextAnim_ != anim && !animations_[nextAnim_]->loop_)
		changeAnim();
	}
	
	virtual void receive(Mensaje* msg);

	int getfrWidth() const { return frWidth_; };
	int getfrHeight() const { return frHeigth_; };
	int getnumFrFils() const { return numFrFils_; };
	int getNumFrCols() const { return numFrCols_; };

protected:

	uint32_t timeNext; // Control del tiempo de repeticion del bucle
	uint32_t timeLastFrame = 0;

	Texture * texture_;// textura
	SDL_Rect sourceRect;

	int frWidth_, frHeigth_, numFrFils_, numFrCols_; // datos frames
	
	vector <animData*> animations_; // animaciones existentes
	int currentAnim_, currentFrame_, nextAnim_; // posicion en el vector de la animacion activa
	int numFrames;

	virtual void calculateNextSourceRect();
	virtual void changeAnim();
	virtual int nextFrame();
};

