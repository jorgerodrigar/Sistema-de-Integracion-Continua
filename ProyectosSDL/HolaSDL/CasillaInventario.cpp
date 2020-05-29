#include "CasillaInventario.h"

bool CasillaInventario::pulsacion(const SDL_Event& event, int espaciadoX, int espaciadoY){
	//Cambio    vvvvvvvvvvvvvvv Antes: This->handleEvent
	SDL_Rect rect;
	rect.x = this->getPosition().getX()+this->getWidth()/2-espaciadoX/2;
	rect.y = this->getPosition().getY()+this->getHeight()/2-espaciadoY/2;
	rect.w = espaciadoX;
	rect.h = espaciadoY;

	bool flag = ComponenteClickeable::handleInput(&rect, event); //handle del raton
	return flag;
}
