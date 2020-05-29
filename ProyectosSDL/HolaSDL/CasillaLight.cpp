#include "CasillaLight.h"
#include "FeedbackCursorInputComponent.h"


CasillaLight::CasillaLight()
{
}

CasillaLight::CasillaLight(SDLApp * game, int x, int y, int w, int h, Texture * texture, Observer* obs) : Entity(game), pos_(x, y), render(texture), encendido(false) {
	this->setWidth(w);
	this->setHeight(h);
	this->addRenderComponent(&render);
	this->addObserver(obs); //observer es el estado del puzzle
	this->addInputComponent(new FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar));
	invertir();
}

CasillaLight::~CasillaLight()
{
	this->delRenderComponent(&render); //no es puntero, asi que lo deleteamos para evitar fallos
}

void CasillaLight::handleInput(Uint32 time, const SDL_Event & event)
{
	if (ComponenteClickeable::handleInput(this, event)) { //si es clickada...
		act();
	}

	Entity::handleInput(time, event);
}

void CasillaLight::act()
{
	invertir(); //se invierte 
	send(&MensajePosicionMatriz(LuzInvertida, pos_));//manda un mensaje al estado de que ha sido clickada
}

void CasillaLight::invertir()
{
	encendido = !encendido; //cambio de bool
	updateText();
}

void CasillaLight::updateText(){
	if (encendido) {
		this->setTexture(0, app->getResources()->getImageTexture(Resources::LuzEncendida)); //cambio de textura 
	}
	else {
		this->setTexture(0, app->getResources()->getImageTexture(Resources::LuzApagada));
	}
}

