#include "ControlesState.h"
#include <fstream>
#include "ImageRenderer.h"
#include "MouseEventAnimComponent.h"

vector<Entity*> ControlesState::entities; 

ControlesState::ControlesState()
{
}


ControlesState::~ControlesState()
{
	stage.clear();
}

void ControlesState::readFromJson()
{
	if (entities.empty()) { //si la variable static está vacia...

		botonSalir = new Boton(app, "exitButton", exitFun_, Resources::BotonSonido);
		botonSalir->setWidth(65); botonSalir->setHeight(65); botonSalir->setPosition(Vector2D(40, 40));
		botonSalir->addAnim("Stop", { 0,0,1,1,2,2,3,3,4,4,5,5,6,6 }, true, -1, 100);
		botonSalir->addAnim("Feedback", { 7 }, true, -1, 100);
		botonSalir->addAnim("Pressed", { 8 }, true, -1, 100);
		botonSalir->addRenderComponent(new AnimationRenderer(app->getResources()->getImageTexture(Resources::SalirControles), botonSalir->getAnimations(), 3, 3, 65, 65));
		botonSalir->addInputComponent(new MouseEventAnimComponent(SDL_MOUSEBUTTONDOWN, "Pressed", "Stop", SDL_BUTTON_LEFT));
		botonSalir->addInputComponent(new MouseEventAnimComponent(SDL_MOUSEMOTION, "Feedback", "Stop"));
		botonSalir->setAnimated(true);

		stage.push_back(botonSalir);
		entities.push_back(botonSalir);

		string name;
		name = "..\\Controles\\controles.json";

		std::ifstream i(name);

		if (i.is_open()) { // Para que no intente abrir archivos que no existen

			json j;
			i >> j;

			for (unsigned int i = 0; i < j["imagenes"].size(); i++) {
				entities.push_back(new Entity(app));

				Entity* aux = entities.back();

				if (!j["imagenes"][i]["w"].is_null())
					aux->setWidth(j["imagenes"][i]["w"]);
				else
					aux->setWidth(app->getWindowWidth());

				if (!j["imagenes"][i]["h"].is_null())
					aux->setHeight(j["imagenes"][i]["h"]);
				else
					aux->setHeight(app->getWindowHeight());

				if (!j["imagenes"][i]["y"].is_null() && !j["imagenes"][i]["x"].is_null())
					aux->setPosition(Vector2D(j["imagenes"][i]["x"], j["imagenes"][i]["y"]));

				bool animated = false;

				if (!j["imagenes"][i]["animated"].is_null()) {
					if (j["imagenes"][i]["animated"]) {
						animated = true;
						if (!j["imagenes"][i]["frames"].is_null() && !j["imagenes"][i]["loop"].is_null() && !j["imagenes"][i]["vel"].is_null())
							aux->addAnim("Loop", j["imagenes"][i]["frames"], j["imagenes"][i]["loop"], -1, j["imagenes"][i]["vel"]);
					}
				}

				if (animated) {
					if (!j["imagenes"][i]["numText"].is_null() && !j["imagenes"][i]["cols"].is_null() && !j["imagenes"][i]["fils"].is_null() && !j["imagenes"][i]["frameWidth"].is_null() && !j["imagenes"][i]["frameHeight"].is_null())
						aux->addRenderComponent(new AnimationRenderer(app->getResources()->getImageTexture(Resources::ImageId(j["imagenes"][i]["numText"])), aux->getAnimations(), j["imagenes"][i]["cols"], j["imagenes"][i]["fils"], j["imagenes"][i]["frameWidth"], j["imagenes"][i]["frameHeight"]));
				}
				else {
					if (!j["imagenes"][i]["numText"].is_null())
						aux->addRenderComponent(new ImageRenderer(app->getResources()->getImageTexture(Resources::ImageId(j["imagenes"][i]["numText"]))));
				}

				if (!j["imagenes"][i]["alpha"].is_null()) {
					aux->getTexture()->changeAlpha(j["imagenes"][i]["alpha"]);
				}

				stage.push_back(aux);
			}
		}
	}
	else { //si no, simplemente pusheamos
		for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++) {
			stage.push_back(*it);
		}
	}
}
