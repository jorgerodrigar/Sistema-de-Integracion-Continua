#include "Cursor.h"


int Cursor::dependencias = 0;

Cursor::Cursor()
{
}


Cursor::~Cursor()
{
	this->delInputComponent(&fc);
	this->delRenderComponent(ren);
	delete ren;
}

Cursor::Cursor(SDLApp * app, Texture* txt, unsigned int w, unsigned int h): Entity(app)
{
	this->setWidth(w);
	this->setHeight(h); //set de anchura y altura

	fc = FollowCursor();
	this->addInputComponent(&fc); //add del componente que hace que siga al cursor

	this->addAnim("Normal", { 0 }, true, -1, 200);
	this->addAnim("Feedback", { 1 }, true, -1, 200);

	ren = new AnimationRenderer(txt, this->getAnimations(), 2, 1, 138,200);
	this->addRenderComponent(ren); //add del render

	this->setAnimated(true);
}
