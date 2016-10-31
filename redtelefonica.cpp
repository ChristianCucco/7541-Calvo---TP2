
#include "redTelefonica.h"


redTelefonica::redTelefonica(){
    this->celularesExistentes=new lista<celular>;
    this->antenasExistentes=new lista<antena>;
    this->mensajesEnCola=new lista<mensaje>;
    this->llamadasActivas=new lista<llamadas>;
    this->modoActual=aDefinir;
    this->celularActual=0;
}

void redTelefonica::seleccionarModo(modo modoAIniciar){
    this->modoActual=modoAIniciar;
}

void redTelefonica::agregarCelular(unsigned int numero,int ID, zonaCelu zonaActual){
    celular* celularNuevo;
    celularNuevo->asignarID(ID);
    celularNuevo->asignarNumero(numero);
    celularNuevo->cambiarDeZona(zonaActual);
    //TERMINARRR!!!!!
   }

void redTelefonica::agregarAntena(int ID,zonaCelu zonaACubrir,unsigned int capacidadMax){

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
   std::string mostrar = "";
   bool encontrado;
   while ((this->celularesExistentes->avanzarCursor())&&(!encontrado))
    {   celularActual=this->celularesExistentes->obtenerCursor();
        encontrado=celularActual->celularID()==idCelular;}
    if (encontrado)
        {
            //FALTA
        }
    else
{
        //FALTA
}
  }
