#ifndef COMPONENTSWITCHER_H_
#define COMPONENTSWITCHER_H_
#include "checkML.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include <vector>

#include "Entity.h"

/*
 *
 */
class ComponentSwitcher: public GameObject, public Observer {
public:

	struct ModeInfo {
		InputComponent* ic;
		PhysicsComponent* pc;
		RenderComponent* rc;
	};
	ComponentSwitcher() {}
	ComponentSwitcher(SDLApp* game, Entity* o);
	virtual ~ComponentSwitcher();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time) {};
	virtual void render(Uint32 time) {};

	void addMode(ModeInfo mode);
	void switchToNextMode();
	void setMode(int i);

	virtual void receive(Mensaje* msg);
	bool isKeyBoardComponent() { return keyComp; }

private:
	bool cambioEscena;
	Entity* o_;
	std::vector<ModeInfo> modes_;
	int currMode_;
	virtual Texture* getTexture(Uint16 pos) const { return nullptr; }
	virtual void saveToJson(json& j) {}
	bool keyBoard = false;//flags para saber si se pueden switchear los componentes
	bool mouse = false;
	bool keyComp = true;//indica si el componente keyboard esta activo
};

#endif /* COMPONENTSWITCHER_H_ */
