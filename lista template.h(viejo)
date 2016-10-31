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
