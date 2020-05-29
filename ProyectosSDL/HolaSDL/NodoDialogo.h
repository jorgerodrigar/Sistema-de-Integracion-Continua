#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Resources.h"


enum emociones{ normal, especial, sorpresa, enfado, triste, feliz };


using namespace std;

struct opciones{
	int nodoApuntado;
	string texto;
};

class NodoDialogo
{
public:
	


	NodoDialogo();
	virtual ~NodoDialogo();


	NodoDialogo(int numnodo, int nodosig, vector<string> text, int numopciones, vector<opciones> resp, Resources::ImageId Pj, emociones Emo);

	

	vector<string> getTexto();
	int getSiguiente(int opcion = -1);		//por defecto, no tiene opciones y apunta a nodoSig
	int getNumOpciones(){return numOpciones;}
	emociones getEmo(){return emo;}
	Resources::ImageId getPj(){return pj;}
	int getNumNodo(){ return numNodo; }
	vector<opciones> getOpciones(){ return respuestas; }

private:
	int numNodo;
	int nodoSig;
	vector<string> texto;
	int numOpciones;
	vector<opciones> respuestas;
	Resources::ImageId pj;
	emociones emo;
};

