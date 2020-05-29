#include "ItemInventario.h"
#include "MainCharacter.h"
#include "PlayState.h" //esto está mal, deberiamos subirlo al padre
#include "Messages.h"



ItemInventario::ItemInventario(SDLApp* game, int x, int y, int w, int h, string _desc, string _tag, Texture* texture, bool permanente) : 
	ClickeableGO(game,x, y,w,h, texture), desc(_desc), tag(_tag), permanente_(permanente)
{
}


ItemInventario::~ItemInventario()
{
}

void ItemInventario::act() {
	cout << "Hanzo main" << endl;

	PlayState* aux = static_cast<PlayState*>(app->getStateMachine()->currentState()); //casteo del playState

	if (aux != nullptr) {
		app->getStateMachine()->currentState()->resetCursor();
		MainCharacter* personaje = aux->getMainPj(); //casteo del main
		if (personaje != nullptr) {
			personaje->addInventoryObject(this); //añadimos objeto
			personaje->send(&Mensaje(Ch_TakeObj));
			this->setActive(false);
			aux->playSoundEffect(Resources::SoundEffectId(getSoundEffect()));
		}
	}
}

