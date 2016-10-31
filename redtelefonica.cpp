/*
* redTelefonica.cpp
*/

#include "redTelefonica.h"
#include <iostream>


redTelefonica::redTelefonica(){
    this->celularesExistentes=new lista<celular*>;
    this->antenasExistentes=new lista<antena*>;
    this->mensajesEnCola=new lista<mensaje*>;
    this->llamadasActivas=new lista<llamadas*>;
    this->modoActual=aDefinir;
    this->celularActual=0;
}

void redTelefonica::seleccionarModo(modo modoAIniciar){
    this->modoActual=modoAIniciar;
}

void redTelefonica::agregarCelular(unsigned int numero,int ID, zona zonaActual){
    celular* celularNuevo;
    celularNuevo->asignarID(ID);
    celularNuevo->asignarNumero(numero);
    celularNuevo->cambiarDeZona(zonaActual);
    celularNuevo->cambiarEstado(LIBRE);
    this->celularesExistentes->agregarDato(celularNuevo,1);
   }

void redTelefonica::agregarAntena(int ID,zona zonaACubrir,unsigned int capacidadMax){

    antena* antenaNueva;
    antenaNueva->asignarID(ID);
    antenaNueva->asignarZona(zonaACubrir);
    antenaNueva->asignarCapacidadMax(capacidadMax);
    antenasExistentes->agregarDato(antenaNueva,1);
}


bool redTelefonica::realizarLlamada(){
    bool puedeLlamar=(this->celularActual->obtenerEstado()==LIBRE);
    if (puedeLlamar){
            this->celularActual->cambiarEstado(OCUPADO);
            }
    return puedeLlamar;
}


llamadas redTelefonica::cortarLlamada(unsigned int destino,unsigned int horaInicioEnSeg,unsigned int horaFinalEnSeg){
    llamadas l;
    if (this->celularActual->obtenerEstado()==OCUPADO){
        this->celularActual->cambiarEstado(LIBRE);
        l.horaInicio=horaInicioEnSeg;
        l.numeroEmisor=this->celularActual->numeroDeCelular();
        l.numeroRemitente=destino;
        unsigned int duracion;
        if(horaFinalEnSeg>horaInicioEnSeg){
            duracion=(horaFinalEnSeg-horaInicioEnSeg);
        }
        else {
            unsigned int segEnUnDia=86400;
            duracion=((segEnUnDia-horaInicioEnSeg)+horaFinalEnSeg);
              }
        l.duracionLlamada=duracion;

    }
    return l;

    }



void redTelefonica::cambiarDeCelular(unsigned int celular){
    this->celularActual->asignarNumero(celular);
}


mensaje redTelefonica::enviarMensaje(unsigned int destino,std::string texto, unsigned int hora)
{
    mensaje m;
    if (this->celularActual->obtenerEstado()==LIBRE){
        m.emisor=celularActual->numeroDeCelular();
        m.receptor=destino;
        m.hora=hora;
        m.texto=texto;
        }
    return m;
}

void redTelefonica::detalleCelulares(int idCelular){
   this->celularesExistentes->iniciarCursor();
   bool encontrado;
   while ((this->celularesExistentes->avanzarCursor())&&(!encontrado))
    {
        celularActual=celularesExistentes->obtenerCursor();
        encontrado=celularActual->celularID()==idCelular;}
    if (encontrado)
        {
            std::cout<<"ID: "<<celularActual->celularID()<<std::endl;
            std::cout<<"Numero: "<<celularActual->numeroDeCelular()<<std::endl;
            std::cout<<"Zona Actual: "<<celularActual->enDondeEsta()<<std::endl;
            std::cout<<"Estado Actual: "<<celularActual->obtenerEstado()<<std::endl;

        }
    else
{
        std::cout<<"No se encontro celular con ese ID"<<std::endl;
}
  }

  void redTelefonica::detalleAntena(int idAntena){
   this->antenasExistentes->iniciarCursor();
   bool encontrado;
   antena* antenaActual;
   while ((this->antenasExistentes->avanzarCursor())&&(!encontrado))
    {   antenaActual=antenasExistentes->obtenerCursor();
        encontrado=antenaActual->obtenerID()==idAntena;}
    if (encontrado)
        {
            std::cout<<"ID: "<<antenaActual->obtenerID()<<std::endl;
            std::cout<<"Zona Cubierta: "<<antenaActual->obtenerZonaCubierta()<<std::endl;
            std::cout<<"Capacidad Maxima: "<<antenaActual->obtenerCapacidadMaxima()<<std::endl;

        }
    else
{
        std::cout<<"No se encontro antena con ese ID"<<std::endl;
}
  }
