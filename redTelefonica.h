/*
 * redTelefonica.h
 *
 *  Created on: 08/10/2016
 *      Author: Matias
 */

#ifndef REDTELEFONICA_H_
#define REDTELEFONICA_H_
#include "antena.h"
#include "celulares.h"
#include "listaTemplate.h"


enum modo{
    aDefinir,
	Celular,
	RedCentral,
};

struct mensaje {
	int emisor,receptor,hora;
	std::string texto;

};
struct llamadas{// registro que guarda las llamadas activas
	unsigned int horaInicio;
	unsigned int duracionLlamada;
	unsigned int numeroEmisor;
	antena* emisor;
	unsigned int numeroRemitente;
	antena* remitente;
};

class redTelefonica{
	private:
	modo modoActual;
	lista<celular>* celularesExistentes;
	lista<antena>* antenasExistentes;
	celular* celularActual;//unicamente en modo celular
	lista<mensaje>* mensajesEnCola;//guarda los mensajes a procesar
	lista<llamadas>* llamadasActivas;

	public:
	redTelefonica();

	void seleccionarModo(modo modoAIniciar);

	void agregarCelular(unsigned int numero,int ID, zonaCelu zonaActual);

	void agregarAntena(int ID,zonaCelu zonaACubrir,unsigned int capacidadMax);

	//MODO CELULAR------------------------------------------------------
	//PRE destino debe ser valido y >0
	//POS: envia texto a destino, devuelve los datos del mensaje guardados
	mensaje enviarMensaje(unsigned int destino,std::string texto, unsigned int hora);

	//PRE destino debe ser valido y >0
	//POS: hace una llamada a destino, devuelve true si la operacion se pudo realizar con exito
	//si fue exitoso pone al celular en estado OCUPADO
	bool realizarLlamada();

	//PRE: estado == OCUPADO
	//POS: corta la llamada y devuelve los datos de la llamada guardados
	llamadas cortarLlamada(unsigned int destino,unsigned int horaInicioEnSeg,unsigned int horaFinalEnSeg);

	//PRE celular debe ser valido y >0
	//POS: el programa cambia el celular que se esta usando
	void cambiarDeCelular(unsigned int celular);

	//MODO RedCentral-------------------------------------------------------
	//PRE celular1,2 deben ser numeros de celulares esxistentes
	//POS muestra los registros de llamadas entre los celulares
	std::string mostrarDetalleLlamadasEntre(unsigned int celular1, unsigned int celular2);
	//PRE celular1,2 deben ser numeros de celulares esxistentes
	//POS muestra los registros de mensajes entre los celulares1,2
	std::string mostratDetalleMensajesEntre(unsigned int celular1, unsigned int celular2);

	unsigned int celularMasHablo();//Por antena y en total

	unsigned int celularMasLlamo();//=

	unsigned int celularMasOcupado();//=

	unsigned int celularMasLlamaron();

	std::string detalleLlamadasPor(unsigned int celular);

	std::string detalleLlamadasPara(unsigned int celular);

	//PRE idAntena tiene que ser el id de la antena
	//POS muestra los maximos conectados simultaneos en la antena correspondiente
	int conectadosMax(int idAntena);

	//PRE idAntena tiene que ser el id de la antena
	//POS muestra las llamadas anuladas por la antena correspondiente
	int llamadasAnuladas(int idAntena);

	//PRE idAntena tiene que ser el id de la antena
	//POS muestra los detalles de la antena correspondiente
	std::string detalleAntena(int idAntena);

	//PRE idCelular tiene que ser el id o celular del telefono
	//POS muestra los detalles del celular correspondiente
	void detalleCelulares(int idCelular);

	void procesarArchivoMaestro();

	//POS envia los mensajes en cola
	void procesarMensajes();
	//----------------------------------------
	//PRE
	//POS: Sale del programa
	void salir();
	~redTelefonica();
};


#endif /* REDTELEFONICA_H_ */
