#include "GODoors.h"
#include "GOTransiciones.h"



GODoors::~GODoors()
{
}

void GODoors::secondAct() {
	list<GameObject*>::iterator it = app->getStateMachine()->currentState()->getStage()->begin();
	it++; it++;
	int x, y;
	x = this->getPosition().getX()+(this->getWidth()/2)-30;
	y = this->getPosition().getY() + (this->getHeight() / 2)+10;
	app->getStateMachine()->currentState()->getStage()->insert
	(it, new GOTransiciones(app, x, y, 60, 60,
		app->getResources()->getImageTexture(Resources::FlechaTransicionSpriteSheet), scneNum, soundId_));
	it--; // hay que restarle 1 porque señala al siguiente al que se ha metido nuevo 
	(*it)->setRotation(rotationGOTrans);
	app->getStateMachine()->currentState()->changeList();
}
