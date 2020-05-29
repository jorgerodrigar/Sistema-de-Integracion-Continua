#include "CasillaPuzzle1.h"

CasillaPuzzle1::CasillaPuzzle1(SDLApp* app, string tag, Texture* textura,bool _special) : Entity(app), tag(tag), special(_special)
{
	if (textura != nullptr) {
		imagen = new ImageRenderer(textura);
		addRenderComponent(imagen);
		setWidth(60);
		setHeight(60);
	}
}
