#include "ClickeableGO.h"
#include "PlayState.h"
//Clase de Testeo


ClickeableGO::ClickeableGO(SDLApp* game, int x, int y, int w, int h, Texture* texture, bool rangeCheck_): Entity(game), rangeCheck(rangeCheck_)
{
	render = new ImageRenderer(texture);
	this->addRenderComponent(render); //componente de pintado para que aparezca en pantalla
	position_ = Vector2D(x, y);
	height_ = h;
	width_ = w;
	addObserver(app->getSoundManager());
}

ClickeableGO::~ClickeableGO()
{
	this->delRenderComponent(render);
	delete render;
}

void ClickeableGO::handleInput(Uint32 time, const SDL_Event& event) {
	if (ComponenteClickeable::handleInput(this, event) && this->isActive()) {
		if (rangeCheck)
			if(inRange((int)static_cast<PlayState*>(this->getGame()->getStateMachine()->currentState())->getMainPj()->getPosition().getX())) { //este static, a no ser que se le pase un puntero de tipo "PlayState" no se me ocurre manera de quitarlo (o subiendo el metodo al padre, no tiene sentido eso)
				act();//Redefinico en cada clase
				//cout << "Pulsado" << endl;
			}
			else {
				PlaySoundE msg = { Resources::WrongPuzle, 0 };
				send(&msg);
				SoundEffectVolume vol = { Resources::WrongPuzle, 50 };
				send(&vol);
				//cout << "not in range" << endl;
			}
		else
			act();
	}

	Entity::handleInput(time, event);
}
