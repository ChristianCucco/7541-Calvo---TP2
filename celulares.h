
/*
 * celular.h
 *
 */

#ifndef CELULAR_H_
#define CELULAR_H_

enum estado{
	LIBRE,//no esta haciendo ninguna accion
	OCUPADO,//se encuentra dentro de una llamada
};

enum zonaCelu{
    zona1,
    zona2,
    zona3,
    zona4,
};

class celular{
private:
	unsigned int numero;
	zonaCelu zonaActual;// el celular se conecta a la antena de la zona en la que se encuentra
	estado estadoActual;
	celular* enLlamadaCon;//nose si va a ser necesario
	int ID;

public:
    void asignarNumero(unsigned int numeroNuevo);

	void asignarID(int IDNuevo);

	//PRE ID debe ser unico al igual que numero
	//POS: crea un celular con identificacion ID y numero de telefono numero
	celular(unsigned int numero,int ID, zonaCelu zona);
	//POS devuelve el numero telefonico del celular
	unsigned int numeroDeCelular();
	//POS Devuelve el numero de ID del celular
	int celularID();

	//PRE minuto debe estar entre 0 y 1439 siendo 0 las 12:00 AM y 1439 las 11:59PM
	//POS: Muestra los mensajes recibidos a partir de minuto
	void verMensajesNuevos(unsigned int minuto);

	//PRE
	//POS: Muestra todos los mensajes enviados
	void verHistorialMensajesEnviados();

	//PRE
	//POS:Muestra todos los mensajes recibidos
	void verHistorialMensajesRecibidos();

	//POS devuelve la zona
	zonaCelu enDondeEsta();

	//PRE zona debe ser valida
	//POS cambia la zona actual del celular
	void cambiarDeZona(zonaCelu nuevaZona);
	//PRE
	//POS:cambia el estado del celular
	void cambiarEstado(estado estadoNuevo);
	//POS devuelve el estado actual
	std::string obtenerEstado();
	//PRE:exista id correspondiente
	//POS:devuelve en este mismo orden "id: (id) numero:(numero) estado (estado) Antena de ultima conexion (antena) " en un string
	std::string mostrarDetalleCelular();


};
#endif /* CELULAR_H_ */
