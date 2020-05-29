#include "Boton.h"
#include "AnimationRenderer.h"

Boton::~Boton()
{
	delInputComponent(&feed);
	actualState = nullptr;
}

Boton::Boton(SDLApp * app, CallBackOnClickStateFC * stateFC, GameState * actualState, string nombre, int fil, int col, Resources::SoundEffectId id_, int repeticiones, int volumen) :
	Entity(app), stateFC(stateFC), actualState(actualState), nombre(nombre), f(fil), c(col), fun(nullptr), idSonido(id_), repeticiones_(repeticiones), volumen_(volumen)
{
	addObserver(app->getSoundManager());
	feed = FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar); addInputComponent(&feed);
}

Boton::Boton(SDLApp * app, string nombre, function<void()> f, Resources::SoundEffectId id_, int repeticiones, int volumen) : 
	Entity(app), nombre(nombre), fun(f), stateFC(nullptr), idSonido(id_), repeticiones_(repeticiones), volumen_(volumen)
{
	addObserver(app->getSoundManager());
	feed = FeedbackCursorInputComponent(app->getStateMachine()->currentState()->getCursor(), Resources::BotonSinClickar); addInputComponent(&feed);
}

void Boton::handleInput(Uint32 time, const SDL_Event& event) {
	Entity::handleInput(time, event); //se llama al handleInput --> componentes adicionales que puedan tener

	if (ComponenteClickeable::handleInput(this, event)) { //si es pulsado
		playSoundEffect(idSonido, repeticiones_, volumen_);//reproduce el sonido correspondiente
		if (stateFC != nullptr) { //si state != nullptr se ejecuta (valido para las matrices del puzzle match3 solo...)
			stateFC(actualState, f, c);
		}
		else fun(); //para todo lo demás, fun();
	}
}
