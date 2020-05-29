#include "Entity.h"
#include "SDLApp.h"
#include "AnimationRenderer.h"

Entity::Entity(SDLApp* game) :
		GameObject(game), inputComp_(), physicsComp_(), renderComp_() {
}

Entity::~Entity() {
	for (InputComponent* ic : inputComp_) { //problemas al hacer todo esto, hay destructoras perdidas que deben estar mal (o no están..)
		if (ic != nullptr && dynamic_cast<PhysicsComponent*>(ic) == nullptr) { delete ic; ic = nullptr; delInputComponent(ic); }
	}
	for (PhysicsComponent* pc : physicsComp_) {
		if (pc != nullptr) { delete pc; pc = nullptr; delPhysicsComponent(pc); }
	}
	for (RenderComponent* rc : renderComp_) {
		if (rc != nullptr) { delete rc; rc = nullptr; delRenderComponent(rc); }
	}
}

void Entity::handleInput(Uint32 time, const SDL_Event& event) {
	if (this->active_) {
		for (InputComponent* ic : inputComp_) {
			ic->handleInput(this, time, event);
		}
	}
}

void Entity::update(Uint32 time) {
	if (this->active_) {
		for (PhysicsComponent* pc : physicsComp_) {
			pc->update(this, time);
		}
	}
}

void Entity::render(Uint32 time) {
	if (this->active_) {
		for (RenderComponent* rc : renderComp_) {
			rc->render(this, time);
		}
	}
}

void Entity::addInputComponent(InputComponent* ic) {
	inputComp_.push_back(ic);
}

void Entity::addPhysicsComponent(PhysicsComponent* pc) {
	physicsComp_.push_back(pc);
}

void Entity::addRenderComponent(RenderComponent* rc) {
	renderComp_.push_back(rc);
}

void Entity::delInputComponent(InputComponent* ic) {
	std::vector<InputComponent*>::iterator position = std::find(
			inputComp_.begin(), inputComp_.end(), ic);
	if (position != inputComp_.end())
		inputComp_.erase(position);
}

void Entity::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(
			physicsComp_.begin(), physicsComp_.end(), pc);
	if (position != physicsComp_.end()) {
		physicsComp_.erase(position);
	}
}

void Entity::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
			renderComp_.begin(), renderComp_.end(), rc);
	if (position != renderComp_.end())
		renderComp_.erase(position);
}

Texture* Entity::getTexture(Uint16 pos) const {
	if (pos < renderComp_.size()) {
		return renderComp_[pos]->getTexture();
	}
}

void Entity::setTexture(Uint16 pos, Texture* newText) {
	if (pos < renderComp_.size()) {
		renderComp_[pos]->setTexture(newText);
	}
}

void Entity::saveToJson(json& j) {
	Vector2D pos = this->getPosition(); j["x"] = pos.getX(); j["y"] = pos.getY();  j["w"] = this->getWidth();
	j["h"] = this->getHeight(); j["Texture"] = app->getResources()->getPosTexture(this->getTexture(0)); j["rotation"] = this->getAngle();
	j["soundEffect"] = this->getSoundEffect();

	if (_id != -4) {
		j["UnlockId"] = _id;
	}
	saveAnims(j);
}

void Entity::delEveryRenderComponent() { //deletea y borra de la lista
	std::vector<RenderComponent*>::iterator it;
	for (it = renderComp_.begin(); it != renderComp_.end();) {
		it = renderComp_.erase(it);
	}
}

void Entity::saveAnims(json & j){
	if (this->isAnimated()) { //si esta animado, guarda las animaciones
		j["animation"] = true;
		AnimationRenderer* aux = static_cast<AnimationRenderer*>(renderComp_.front()); //ambos los veo necesarios peero
		j["numColsFrame"] = aux->getnumFrFils();
		j["numFilsFrame"] = aux->getNumFrCols();
		j["widthFrame"] = aux->getfrWidth();
		j["heightFrame"] = aux->getfrHeight();
		j["loop"] = this->getAnimations()[0]->loop_;
		j["vel"] = this->getAnimations()[0]->rate_;
		for (unsigned int i = 0; i < this->getAnimations().size(); i++) {
			j["Anims"][i] = this->getAnimations()[i]->framesAnim_;
		}
	}
}

void Entity::playAnim(string label)
{
	if (this->isAnimated()) {
		static_cast<AnimationRenderer*>(renderComp_[0])->playAnim(label);
	}
}

