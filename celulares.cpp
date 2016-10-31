
/*
 * celular.cpp
 */

#include "celulares.h"

celular::celular(unsigned int numero,int ID,zona zona){
	this-> zonaActual = zona;
	this-> numero = numero;
	this-> estadoActual = LIBRE;
	this->ID = ID;

}

void celular::asignarNumero(unsigned int numeroNuevo){
    this->numero=numeroNuevo;
}

void celular::asignarID(int IDNuevo){
    this->ID=IDNuevo;

}

unsigned int celular::numeroDeCelular()
    {return this-> numero;}

int celular::celularID()
    {return this-> ID;}


zona celular::enDondeEsta()
    {return this-> zonaActual;}

void celular::cambiarDeZona(zona nuevaZona){
	this->zonaActual = nuevaZona;
}

void celular::cambiarEstado(estado estadoNuevo){
	this->estadoActual = estadoNuevo;
}

estado celular::obtenerEstado()
    {return this-> estadoActual;}



//FALTAN POR HACER
void celular::verHistorialMensajesRecibidos(){

}
void celular::verHistorialMensajesEnviados(){

}
