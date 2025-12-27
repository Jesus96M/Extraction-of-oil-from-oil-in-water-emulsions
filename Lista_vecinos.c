#include "parametros.h"
void anadirVecino(int nuevo){
	// Funcion que anade un elemento a la lista de indices
	vecinosArevisar[longitudVecinos]=nuevo;
	longitudVecinos++;
}

void quitarVecino(int eliminar){
	// Funcion que quita un elemento de la lista de indices
	int empieza;
	int ind;// indice local para evitar problemas cuando hay llamadas a muchas funciones
	empieza=N;// Si no hay ninguno no mueva nada.
	for(ind=0;ind<longitudVecinos;ind++){
		if(*(vecinosArevisar+ind)==eliminar){
			empieza=ind;
			longitudVecinos--;
			break;
		}
	}
	for(ind=empieza;ind<longitudVecinos;ind++){
		vecinosArevisar[ind]=*(vecinosArevisar+(ind+1));
	}
}

bool perteneceVecinoQ(int h){
	//Funcion que calcula si un indice esta en la lista de indices
	bool p;
	int ind;
	p=false;
	for(ind=0;ind<longitudVecinos;ind++){
		if(*(vecinosArevisar+ind)==h){
			p=true;
			return p;
		}
	}
	return p;
}
