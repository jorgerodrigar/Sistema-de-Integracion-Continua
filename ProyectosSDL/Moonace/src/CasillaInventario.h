#pragma once
#include "checkML.h"
#include "Entity.h"
#include "ComponenteClickeable.h"

class CasillaInventario :
	public Entity, ComponenteClickeable
{
private:
	string tag;
	string description;
	bool permanente_ = false;
public:
	CasillaInventario() {};
	virtual ~CasillaInventario() {}

	//Constructora que recibe el tag y su descripcion
	CasillaInventario(SDLApp* app, string tag, string description) : Entity(app), tag(tag), description(description) {};
	string getTag() { return this->tag; };
	string getDescription() { return this->description; };
	void setDescription(string newDescription) { this->description = newDescription; };
	void setTag(string newTag) { this->tag = newTag; };
	bool pulsacion(const SDL_Event& event, int espaciadoX, int espaciadoY);
	virtual void saveToJson(json& j) { json aux;  Entity::saveToJson(aux); aux["tag"] = tag; aux["descripcion"] = description; j.push_back(aux); };
	void setPermanente(bool p) { permanente_ = p; };
	bool const isPermanent() { return permanente_; };
};

