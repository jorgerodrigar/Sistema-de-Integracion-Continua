#pragma once
#include "GOUnlockeable.h"
#include "Observer.h"
#include "ItemInventario.h"
#include "GOstates.h"
class GOcofres :
	public GOUnlockeable
{
private:
	int xItem, yItem;
public:
	GOcofres(SDLApp* game, int x, int y, int w, int h, Texture* texture, string tag, int wItm, int hItm, string _desc, string _tag, Texture* txtItm, int xItem, int yItem, bool permanente = false, char id = NULL, bool opened = false) :
		GOUnlockeable(game, x, y, w, h, texture, tag, id), itmW(wItm), itmH(hItm), itmDesc(_desc), itmTag(_tag), itmTexture(txtItm), xItem(xItem), yItem(yItem), imtPerm(permanente),guardado(false), puzzle(nullptr) { this->opened = opened; }

	GOcofres(SDLApp* game, int x, int y, int w, int h, Texture* texture, string _tag, char id = NULL, GOstates* puzzle = nullptr);

	virtual ~GOcofres();


	//Crear el GO states justo antes de crear este item y pasarselo??
	GOstates* puzzle;
	int itmW, itmH;
	string itmDesc, itmTag;
	Texture* itmTexture;
	bool imtPerm;
	bool guardado;

	void secondAct();

	virtual void saveToJson(json& j) {
		if (this->isActive()) {
			json aux; Entity::saveToJson(aux); aux["tag"] = key; aux["wItem"] = itmW; aux["hItem"] = itmH;
			aux["descripcionItem"] = itmDesc; aux["tagItem"] = itmTag; aux["numTextItem"] = app->getResources()->getPosTexture(itmTexture);
			aux["xItem"] = xItem; aux["yItem"] = yItem; aux["permanenteItem"] = imtPerm; aux["open"] = opened; aux["generaState"] = guardado; j["GOCofres"].push_back(aux);
		}
	};
};

