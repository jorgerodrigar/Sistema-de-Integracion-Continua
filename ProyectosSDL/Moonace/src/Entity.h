	#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "checkML.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include <vector>
#include "Texture.h"
#include "AnimationData.h"


using namespace std;

class Entity : public GameObject {
public:
	Entity() {};
	Entity(SDLApp* game);
	virtual ~Entity();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual void addInputComponent(InputComponent* ic);
	virtual void addPhysicsComponent(PhysicsComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delPhysicsComponent(PhysicsComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);
	Texture* getTexture(Uint16 pos = 0) const;
	void setTexture(Uint16 pos, Texture* newText);
	void playAnim(string label);
	virtual void saveToJson(json& j);
	virtual void delEveryRenderComponent();
	void setAnimated(bool an) { animated = an; };
	bool isAnimated () const { return animated; };
	void saveAnims(json& j);

	virtual void addAnim(string label, vector<int> framesAnim, bool loop = true, int onEnded = -1, double rate = 100)
	{
		animData* newAnim = new animData(label, framesAnim, loop, onEnded, rate); animations.push_back(newAnim);
	}
	virtual vector<animData*> getAnimations() { return animations; }
	

private:
	vector<InputComponent*> inputComp_;
	vector<PhysicsComponent*> physicsComp_;
	vector<RenderComponent*> renderComp_;
	bool animated = false;


protected:
	vector<animData*> animations;
};

#endif /* GAMECOMPONENT_H_ */