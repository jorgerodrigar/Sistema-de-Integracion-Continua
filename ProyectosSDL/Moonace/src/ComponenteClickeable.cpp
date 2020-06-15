#include "ComponenteClickeable.h"
#include "Entity.h"
//using namespace std;

ComponenteClickeable::ComponenteClickeable()
{
}

ComponenteClickeable::~ComponenteClickeable()
{
}

bool ComponenteClickeable::handleInput(GameObject* o, const SDL_Event& e) {
	
	bool eventHandled = false;

	SDL_Rect rect;//Inizializacion del Rect
	rect.x = o->getPosition().getX();
	rect.y = o->getPosition().getY();
	rect.w = o->getWidth();
	rect.h = o->getHeight();

	SDL_Point mouse;
	mouse.x = e.button.x;
	mouse.y = e.button.y;

	//Vars control
	//cout << "X: " << rect.x << "  Y: " << rect.y << "  W: " << rect.w << "  H: " << rect.h << endl;
	//cout << "Mouse  " << "X: " << mouse.x << "" << "Y: " << mouse.y << endl;

	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && SDL_PointInRect(&mouse, &rect )){//Si se pulsa el boton izquierdo del raton y estamos en el rect deseado
		firstClickDown = true;
	}
	else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && firstClickDown && SDL_PointInRect(&mouse, &rect)) { //para que tenga que hacer el click completo
		eventHandled = true;
		firstClickDown = false;
	}

	return eventHandled;
}

bool ComponenteClickeable::handleInput(SDL_Rect* rect, const SDL_Event& e) {
	bool eventHandled = false;

	SDL_Point mouse;
	mouse.x = e.button.x;
	mouse.y = e.button.y;

	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && SDL_PointInRect(&mouse, rect)) {//Si se pulsa el boton izquierdo del raton y estamos en el rect deseado
		eventHandled = true;
		//cout << "TRUE" << endl;
	}
	return eventHandled;

}