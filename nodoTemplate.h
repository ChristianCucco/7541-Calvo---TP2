/*
 * nodoTemplate.h
 *
 *  Created on: 08/10/2016
 *      Author: Matias
 */

#ifndef NODOTEMPLATE_H_
#define NODOTEMPLATE_H_
template <class T>
class nodo{
private:
	T dato;
	nodo<T>* siguiente;
public:
	//POS crea un nodo con el dato dato y con el siguiente nodo
	nodo<T>(T dato,nodo<T>* nodo);
	//POS devuelve el dato del nodo
	T obtenerDato();
	//POS devuelve el siguiente
	nodo<T>* obtenerSiguiente();
	//POS cambia el siguiente
	void cambiarSiguiente(nodo<T>* sig);
};

template <class T>
 nodo<T>::nodo(T dato,nodo<T>* nodo){
	this-> dato = dato;
	this-> siguiente= nodo;
}

template <class T>
T nodo<T>::obtenerDato(){
	return this-> dato;
}

template <class T>
nodo<T>* nodo<T>::obtenerSiguiente(){
	return this-> siguiente;
}

template <class T>
void nodo<T>::cambiarSiguiente(nodo<T>* sig){
	this-> siguiente = sig;
}
#endif /* NODOTEMPLATE_H_ */
