/*
 * antena.h
 *
 *  Created on: 08/10/2016
 *      Author: Matias
 */

#ifndef ANTENA_H_
#define ANTENA_H_
#include <string>
#include "listaTemplate.h"
#include "nodoTemplate.h"

enum zonaAntena{

};

struct estadisticas{
    unsigned int llamadasRealizadas;
	unsigned int llamadasRecibidas;
	unsigned int tiempoHablado;
	unsigned int vecesOcupado;
	unsigned int numero;
	int ID;
};


class antena{
private:
	int ID; //Identificacion de la antena
	zonaAntena zonaCubierta;
	unsigned int celularesMaxConectados;//al mismo tiempo
	unsigned int llamadasAnuladas;
	unsigned int capacidadMax;
	unsigned int conectadosActual;
	lista<estadisticas>* registrosEstadisticas;//cada vez q alguien se conecta, se crean o se actualizan los datos

public:
	//PRE zonaACubrir debe existir en zona, capacidad positva
	//POS crea una antena en la zonaACubrir
	antena(int ID,zonaAntena zonaACubrir,unsigned int capacidadMax);
	//POS bye bye antena
	~antena();

	//POS devuelve si hay espacio restante para realizar acciones
	bool quedaCapacidad();

	//POS procesa una las estadisticas llamada terminada
	void procesarLlamado(unsigned int celular,unsigned int horaComienzo,unsigned int horaFin);

	//POS procesa un mensaje (por ahi deberia estar en redCentral)
	bool procesarMensaje(unsigned int emisor,unsigned int remitente,std::string mensaje);
	//PRE necesario para comunicarse entre celulares
	//POS conecta un celular a la Antena, true si se pudo conectar
	bool conectarCelular();

	//POS desconecta un celular
	void desconectarCelular();

	//POS devuelve la capacidad restante
	unsigned int obtenerCapacidadRestante();

	//POS devuelve la cantidad de llamadas anuladas
	unsigned int obtenerLlamadasAnuladas();

	//POS devuelve la cantidad de conexiones maximas
	unsigned int obtenerMaxConexiones();

	//POS devuelve las estadisticas
	lista<estadisticas>* obtenerEstadisticas();

	//POS devuelve la zona
	zonaAntena obtenerZonaCubierta();
};

#endif /* ANTENA_H_ */
