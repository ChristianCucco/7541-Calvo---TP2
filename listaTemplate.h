/*
 * listaTemplate.h
 *
 *  Created on: 08/10/2016
 *      Author: Matias
 */

#ifndef LISTATEMPLATE_H_
#define LISTATEMPLATE_H_
#include "nodoTemplate.h"
typedef unsigned int uint;

template <class T>
class lista{
private:
	uint tamanio;
	nodo<T>* primero;
	nodo<T>* obtenerNodo(uint pos);
	nodo<T>* cursor;
public:
	//POS crea una lista vacia
	lista();
	//POS destroyer class warship, annihilates your data
	~lista();
	//PRE
	//POS agrega dato a la lista en la posicion pos
void agregarDato(T dato,uint pos);
	//
	//POS borra el dato en la posicion pos
void borrar(uint pos);
	//POS devuelve el tamaño de la lista
uint obtenerTam();
	//POS devuelve el dato guardado en pos
T obtenerElemento(uint pos);
	//POS inicia el cursor al comienzo de la lista
void iniciarCursor();
	//POS devuelve verdadero si pudo avanzar el cursor
bool avanzarCursor();
	//POS devuelve el dato guardado en la direccion donde apunta el cursor
T obtenerCursor();
};
template <class T>
lista<T>::lista(){
	this->tamanio=0;
	this->primero=0;
}
template <class T>
void lista<T>::iniciarCursor(){
	this->cursor = this->primero;
}

template <class T>
bool lista<T>::avanzarCursor(){
	if (this->cursor == 0){
		this->cursor = this->primero;
	}
	this->cursor = this->cursor->obtenerSiguiente();
	return (this->cursor != 0);
}
template <class T>
T lista<T>::obtenerCursor(){
	return (this->cursor->obtenerDato());
}

template <class T>
void lista<T>::agregarDato(T dato,uint pos){
	nodo<T>* nuevo = new nodo<T>(dato, 0);
	this->tamanio++;
	if (pos == 1){
		nuevo->cambiarSiguiente(this->primero);
		this->primero = nuevo;
	}
	else{
		nodo<T>* anterior= obtenerNodo(pos-1);
		nuevo->cambiarSiguiente(anterior->obtenerSiguiente());
		anterior->cambiarSiguiente(nuevo);
	}
}
template <class T>
T lista<T>::obtenerElemento(uint pos){
	nodo<T>* elemento = obtenerNodo(pos);
	return (elemento->obtenerDato());
}
template <class T>
lista<T>::~lista(){
	while (this-> tamanio>0){
		this->borrar(1);
	}
}
template <class T>
void lista<T>::borrar(uint pos){
	nodo<T>* aBorrar = this->primero;
	if (pos == 1){
		 primero =aBorrar->obtenerSiguiente();
	}
	else{
		nodo<T>* anterior = obtenerNodo(pos-1);
		aBorrar=anterior->obtenerSiguiente;
		anterior->cambiarSiguiente(aBorrar->obtenerSiguiente());
	}
	 tamanio--;
	delete aBorrar;
}
template <class T>
nodo<T>* lista<T>::obtenerNodo(uint pos){
	nodo<T>* cursor = primero;
	for (int i= 1; i<pos;i++){
		cursor= cursor->obtenerSiguiente();
	}
	return cursor;
}
template <class T>
uint lista<T>::obtenerTam(){
	return this-> tamanio;
}
