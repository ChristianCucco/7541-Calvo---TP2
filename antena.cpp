/*
 * antena.cpp
 */

#include "antena.h"
antena::antena(int ID, zona zonaACubrir,unsigned int capacidadMax){
	this-> ID = ID;
	this-> zonaCubierta = zonaACubrir;
	this-> capacidadMax = capacidadMax;
	this->llamadasAnuladas = 0;
	this->celularesMaxConectados = 0;
	this-> registrosEstadisticas = new lista<estadisticas>;
	this-> conectadosActual = 0;
}
bool antena::quedaCapacidad(){
	return (this->capacidadMax>conectadosActual);
}
bool antena::conectarCelular(){
	if (this->quedaCapacidad()){
		this->conectadosActual++;
	}
}

void antena::desconectarCelular()
    {this->conectadosActual--; }

unsigned int antena::obtenerCapacidadRestante()
    {return (this->capacidadMax-this->conectadosActual);}


unsigned int antena::obtenerMaxConexiones()
    {return this->capacidadMax;}


unsigned int antena::obtenerLlamadasAnuladas()
    {return this->llamadasAnuladas;}


lista<estadisticas>* antena::obtenerEstadisticas()
    {return this->registrosEstadisticas;}

zona antena::obtenerZonaCubierta()
    {return this-> zonaCubierta;}

void antena::asignarID(int ID){
this->ID=ID;
}

void antena::asignarZona(zona zona){
this->zonaCubierta=zona;
}


void antena::asignarCapacidadMax(unsigned int maximo){
this->capacidadMax=maximo;

}

int antena::obtenerID(){
	    return this->ID;
	}

zona antena::obtenerAntena(){
	return this->zonaCubierta;
	}

unsigned int antena::obtenerCapacidadMaxima(){
	return this->capacidadMax;
	}




//FALTAN POR HACER
bool antena::procesarMensaje(unsigned int emisor,unsigned int remitente,std::string mensaje){


}

void antena::procesarLlamado(unsigned int celular,unsigned int horaComienzo,unsigned int horaFin){


}

