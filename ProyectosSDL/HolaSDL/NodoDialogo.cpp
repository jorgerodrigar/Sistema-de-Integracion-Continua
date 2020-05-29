#include "NodoDialogo.h"


NodoDialogo::NodoDialogo()
{
	texto = { "" };
}


NodoDialogo::~NodoDialogo()
{
}

int NodoDialogo::getSiguiente(int opcion){

	if (opcion = -1)
		return nodoSig;
	else
		return respuestas[opcion].nodoApuntado;
}


// Si no hay opciones devuelve un string con el texto a mostrar
// Las opciones se devuelven cada una en un string
vector<string> NodoDialogo::getTexto(){
	
	if (numOpciones <= 0)
		return texto;
	else{
		vector<string> salida;
		salida.resize(numOpciones);
		int n = 0;
		for each (opciones op in respuestas)
		{
			salida[n] = op.texto;
			n++;
		}
		return salida;
	}
}

NodoDialogo::NodoDialogo(int numnodo, int nodosig, vector<string> text, 
	int numopciones, vector<opciones> resp, Resources::ImageId Pj, emociones Emo):numNodo(numnodo),nodoSig(nodosig),texto(text),
	numOpciones(numopciones), respuestas(resp), pj(Pj), emo(Emo) {
	;
}