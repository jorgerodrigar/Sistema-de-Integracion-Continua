#include "GOUnlockeable.h"
#include "PlayState.h"

void GOUnlockeable::act() {
	if (!opened) {
		PlayState* aux = static_cast<PlayState*>(app->getStateMachine()->currentState());

		if (aux->getMainPj()->getCurrentTag() == key || key == "") {
			if (aux != nullptr) {
				MainCharacter* pj = aux->getMainPj();
				if (pj != nullptr) {
					aux->playSoundEffect(Resources::CorrectPuzle);
					pj->getList()->deleteItem(key);
					pj->setCurrenTag("");
					pj->marcaOut();
					if (pj->getList()->getLength() > 4) {
						pj->getList()->getItem(4)->setWidth(pj->getList()->getItem(4)->getWidth() / pj->getShortcut()->getCoef());
						pj->getList()->getItem(4)->setHeight(pj->getList()->getItem(4)->getHeight() / pj->getShortcut()->getCoef());
					}
					pj->getShortcut()->recorreEInicia();
				}
			}
			secondAct();
			opened = true;
		}
		else
		{
			aux->playSoundEffect(Resources::WrongPuzle);
		}
	}
	
}

