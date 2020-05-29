#include "Conversacion.h"
#include "SDLApp.h"
#include "PlayState.h"

Conversacion::Conversacion(SDLApp* game) : Entity(game)
{
	grupoOps = 0;
	f = new Font("..//images/Dialogos/Moonace-Regular.ttf", tamanyoFuenteConv);
	this->setWidth(w);
	this->setHeight(h);

	this->setPosition(Vector2D(x, y));

	feed = FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar);
	addInputComponent(&feed);
}


Conversacion::~Conversacion()
{
	delete f;
	delInputComponent(&feed);
}

void Conversacion::escribir(){
		dialogo[nodoActual];
		if (nodoActual != -1) {
			vector<string> escribir = dialogo[nodoActual].getTexto(); //aqui salta excepcion de vez en cuando, jelp es que nodoActual = -1

			int numLineas = escribir.size();

			if (dialogo[nodoActual].getNumOpciones() > 3) {

				for (int i = grupoOps * 3; i < grupoOps * 3 + 3; i++) {
					if (i < dialogo[nodoActual].getNumOpciones()) {
						checkText(escribir[i], i%3);
					}
				}

				checkText("Mas opciones", 3);
			}

			else if (dialogo[nodoActual].getNumOpciones() > 0) {
				grupoOps = 0;
				for (int i = 0; i < numLineas; i++) {
					checkText(escribir[i], i % 3);
				}
			}
			else {
				grupoOps = 0;
				for (int i = 0; i < numLineas; i++) {
					Texture fuente(app->getRenderer(), escribir[i], *f, colorFuenteConv); //fuente dinámica
					fuente.render(app->getRenderer(), x, y + i * h / 4 + 2);
				}
			}
		}
	//MAGIA NEGRA PA QUE ESCRIBA
}

void Conversacion::handleInput(Uint32 time, const SDL_Event& event){

	texAux_ = "Default";
		if (event.type == SDL_MOUSEBUTTONDOWN) {

			SDL_Point p;
			p.x = event.button.x;
			p.y = event.button.y;

			SDL_Rect r;
			r.x = x;
			r.y = y;
			r.h = h;
			r.w = w;

			//Si el evento es click de raton creamos un punto en la posicion del click, un rectangulo con la forma y posicion del boton
			//y comprobamos si el punto donde se ha clickado está dentro del rectangulo
			if (SDL_PointInRect(&p, &r)) {

				if (nodoActual != -1) {
					if (dialogo[nodoActual].getNumOpciones() <= 0) {
						//if (nodoActual < dialogo.size() - 1) LINEA MUY MUY DUDOSA
						nodoActual = dialogo[nodoActual].getSiguiente();
					}
					else {

						vector<opciones> respuestas = dialogo[nodoActual].getOpciones();

						r.y = y;
						r.h = h / 4;
						if (SDL_PointInRect(&p, &r)) {
							nodoActual = respuestas[grupoOps * 3].nodoApuntado;
						}
						else if (grupoOps * 3 + 1 < dialogo[nodoActual].getNumOpciones()) {
							r.y = y + h / 4;
							if (SDL_PointInRect(&p, &r)) {
								nodoActual = respuestas[grupoOps * 3 + 1].nodoApuntado;
							}
							else if (grupoOps * 3 + 2 < dialogo[nodoActual].getNumOpciones()) {
								r.y = y + 2 * h / 4 + 2;
								if (SDL_PointInRect(&p, &r)) {
									nodoActual = respuestas[grupoOps * 3 + 2].nodoApuntado;
								}

								//ULTIMA OPCION: Más opciones
							}
						}
					}
				}

				if (nodoActual == -1) {
					sendMessage();
					app->getStateMachine()->currentState()->resetCursor();
					this->setActive(false);
					nodoActual = 0;
				}
				else if (dialogo[nodoActual].getNumOpciones() > 3){
						r.y = y + 3 * h / 4 + 2;
						if (SDL_PointInRect(&p, &r)){
							//Si la ultima opcion es Más opciones, pasa al siguiente grupo o vuelve al primero
							if (grupoOps < dialogo[nodoActual].getNumOpciones() / 3)
								grupoOps++;
							else
								grupoOps = 0;
						}
					}
			}
		}
		else resaltarOpcion(event);

		Entity::handleInput(time, event);
}
void Conversacion::update(Uint32 time){
	//ANIMACIONES GUAYS
}
void Conversacion::render(Uint32 time){

	if (nodoActual != -1) {
		app->getResources()->getImageTexture(Resources::GUIDialogosAlpha)->render(app->getRenderer(), { GUIx,GUIy,GUIw,GUIh });
		escribir();

		clip.x = 130 * (dialogo[nodoActual].getEmo() % 2);
		clip.y = 130 * (dialogo[nodoActual].getEmo() / 2);
		app->getResources()->getImageTexture(dialogo[nodoActual].getPj())->render(app->getRenderer(), { retratoX, retratoY, retratoW, retratoH }, &clip);
	}
}

void Conversacion::ConversacionDePrueba(){


	vector<string> text = { "Prueba de dialogo.", "Dialogo normal, se puede clickar", "en cualquiera de las frases para avanzar :)" };
	vector<opciones> ops;
	NodoDialogo nodo1 =  NodoDialogo(0, 1, text, -1, ops, Resources::JeffaExpresiones, feliz);
	text = { "Hola soy ander jejeje." };
	NodoDialogo nodo2 =  NodoDialogo(1, 2, text, -1, ops, Resources::AnderExpresiones, feliz);
	text = { "" };
	ops = { { 0, "Repite todo el dialogo desde el principio" }, { -1, "Acabar el dialogo." }, { 3, "Dialogo con 3 opciones" }, { 0, "Mas opciones para mostrar mas opciones" }, { 1, "Otra opcion random para probar" } };
	NodoDialogo nodo3 =  NodoDialogo(2, 3, text, 5, ops, Resources::AlenaExpresiones, sorpresa);
	ops = { { 0, "1" }, { -1, "2" }, { 1, "3" } };
	NodoDialogo nodo4 =  NodoDialogo(2, 3, text, 3, ops, Resources::AnderExpresiones, enfado);

	dialogo.push_back(nodo1);
	dialogo.push_back(nodo2);
	dialogo.push_back(nodo3);
	dialogo.push_back(nodo4);
	nodoActual = 0;
}

bool Conversacion::loadConversation(string fileName) {
	fileName = "..\\Conversations\\" + fileName + ".json";
	
	std::ifstream i(fileName);
	if (i.is_open()) { // Para que no intente abrir archivos que no existen

		json j;
		i >> j;
		int n;


		NodoDialogo nodo;
		vector<string> textos;
		vector<opciones> opciones;
		dialogo.resize(j["NumNodos"]);

		for (int i = 0; i < j["NumNodos"]; i++) {

			if (j["Nodo"][i]["numOpciones"].is_null() || j["Nodo"][i]["numOpciones"] == 0)
				opciones = {};
			else {
				int k = j["Nodo"][i]["numOpciones"];
				opciones.resize(j["Nodo"][i]["numOpciones"]);
				for (int k = 0; k < j["Nodo"][i]["numOpciones"]; k++) {
					opciones[k].nodoApuntado = j["Nodo"][i]["opciones"][k]["nodoApuntado"];
					string s = j["Nodo"][i]["opciones"][k]["textoOpcion"];
					opciones[k].texto = s;
				}
			}
			if (j["Nodo"][i]["numLineas"] == 0)
				textos = { "" };
			else {
				textos.resize(j["Nodo"][i]["numLineas"]);
				for (int k = 0; k < j["Nodo"][i]["numLineas"]; k++) {
					string s = j["Nodo"][i]["lineas"][k]["texto"];
					textos[k] = s;
				}
			}
			
			dialogo[i] = NodoDialogo(j["Nodo"][i]["numNodo"], j["Nodo"][i]["nodoSig"], textos,
				j["Nodo"][i]["numOpciones"], opciones, Resources::ImageId(j["Nodo"][i]["pj"]), 
				j["Nodo"][i]["emo"]);

			//dialogo[i] = &nodo;

		}

		if (!j["msg"].is_null()) {
			numMsg_ = j["msg"];
		}

		aux = j;

		i.close();
	}
	return 0;
}

void Conversacion::sendMessage()
{
	switch (numMsg_) { //pendiente de mas mensajes
	case 0: {
		MensajeCambioEscenaDialogos msg = MensajeCambioEscenaDialogos(CambioEscena, aux["numScene"]);
		send(&msg);
		break;
	}
	case 1: {
		MensajeAddItem msg = MensajeAddItem(AddItemDialog, aux["textureItem"], aux["tagItem"], aux["descripcionItem"], aux["permanenteItem"]);//añadir objeto al inventario de Alena
		send(&msg);
		break;
	}
	case 2: {
		PlayState* currState = static_cast<PlayState*>(app->getStateMachine()->currentState());
		if (currState->getMainPj()->getPass() == 1) {
			MensajeAddItem msg = MensajeAddItem(AddItemDialog, aux["textureItem"], aux["tagItem"], aux["descripcionItem"], aux["permanenteItem"]);//añadir objeto al inventario de Alena
			send(&msg);
		}
		else {
			Mensaje msg = Mensaje(DialogoAcabado);
			send(&msg);
		}
		currState->getMainPj()->activePass();
		break;
	}
	case 3: {
		MensajeCambioEscenaDialogos msg = MensajeCambioEscenaDialogos(CambioEscena, aux["numScene"]);
		send(&msg);
		MensajeAddItem msg2 = MensajeAddItem(AddItemDialog, aux["textureItem"], aux["tagItem"], aux["descripcionItem"], aux["permanenteItem"]);//añadir objeto al inventario de Alena
		send(&msg2);
		break;
	}
	case 4: {
		Mensaje msg = Mensaje(CHANGE_TO_CREDITS); //cambiar a créditos
		send(&msg);
		break;
	}
	default: {
		Mensaje msg = Mensaje(DialogoAcabado);
		send(&msg);
		break;
	}
	}
}

void Conversacion::resaltarOpcion(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION) {
		SDL_Point p;
		p.x = event.button.x;
		p.y = event.button.y;

		SDL_Rect r;
		r.x = x;
		r.y = y;
		r.h = h;
		r.w = w;

		vector<opciones> respuestas = dialogo[nodoActual].getOpciones();

		if (respuestas.size() > 0)
		{
			r.y = y;
			r.h = h / 4;
			if (SDL_PointInRect(&p, &r)) {
				texAux_ = respuestas[grupoOps * 3].texto;
			}
			else if (grupoOps * 3 + 1 < dialogo[nodoActual].getNumOpciones()) {
				r.y = y + h / 4;
				if (SDL_PointInRect(&p, &r)) {
					texAux_ = respuestas[grupoOps * 3 + 1].texto;
				}
				else if (grupoOps * 3 + 2 < dialogo[nodoActual].getNumOpciones()) {
					r.y = y + 2 * h / 4 + 2;
					if (SDL_PointInRect(&p, &r)) {
						texAux_ = respuestas[grupoOps * 3 + 2].texto;
					}

					//ULTIMA OPCION: Más opciones
				}
			}

			if (dialogo[nodoActual].getNumOpciones() > 3) {
				r.y = y + 3 * h / 4 + 2;
				if (SDL_PointInRect(&p, &r)) {
					//Si la ultima opcion es Más opciones, pasa al siguiente grupo o vuelve al primero
					if (grupoOps < dialogo[nodoActual].getNumOpciones() / 3)
						texAux_ = "Mas opciones";
				}
			}
		}
	}
}

void Conversacion::checkText(string text_, int i)
{
	if (texAux_ != "Default" && texAux_ == text_) {
		Texture fuente(app->getRenderer(), text_, *f, colorOpcionesDiag); //fuente dinámica
		fuente.render(app->getRenderer(), x, y + i * h / 4 + 2);
	}
	else {
		Texture fuente(app->getRenderer(), text_, *f, colorFuenteConv); //fuente dinámica
		fuente.render(app->getRenderer(), x, y + i * h / 4 + 2);
	}
}
