#pragma once
#include "checkML.h"
#include <SDL.h>
#include "CasillaInventario.h"
#include "Texture.h"
#include <list>
#include "ComponenteClickeable.h"
#include "ImageRenderer.h"

class ObjectList
{
private:
	list <CasillaInventario*> objetos; //lista de casillas (almacenan objetos)
	list <CasillaInventario*>::iterator it; //iterador de la lista
	SDLApp* app;
public:
	ObjectList();
	~ObjectList() { for (it = objetos.begin(); it != objetos.end();) { delete *it; it = objetos.erase(it); } }; //delete
	ObjectList(SDLApp* app) : app(app) {};
	void addItem(GameObject* o); //añadir un objeto
	void deleteItem(string tag);//elimina el objeto con el nombre 'tag'
	//void deleteItem(); podemos hacerlo por tags (?)
	CasillaInventario* getItem(int num);//coge el item de la lista en la casilla 'num'
	int getLength() { return (int)objetos.size(); }
	list<CasillaInventario*>::iterator getBegin() { return objetos.begin(); }
	list<CasillaInventario*>::iterator getEnd() { return objetos.end(); }
	void swap(CasillaInventario* uno, CasillaInventario* dos);
	void pushObjects(list <GameObject*>& stage) { for (it = objetos.begin(); it != objetos.end(); it++) { stage.push_back(*(it)); } } //recibe la lista de stages del inventario
	//y pushea esos objetos dentro para que realicen sus funciones básicas
};