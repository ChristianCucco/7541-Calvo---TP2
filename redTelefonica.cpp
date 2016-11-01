/*
* redTelefonica.cpp
*/

#include "redTelefonica.h"
#include <iostream>

#include <sstream>

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

redTelefonica::redTelefonica(){
    this->celularesExistentes=new lista<celular*>;
    this->antenasExistentes=new lista<antena*>;
    this->mensajesEnCola=new lista<mensaje*>;
    this->mensajesHistorico=new lista<mensaje*>;
    this->llamadasActivas=new lista<llamada*>;
    this->modoActual=aDefinir;
    this->celularActual=0;
}

bool redTelefonica::seleccionarModo(modo modoAIniciar,unsigned int celularNum){
    bool encontrado = true;
    if (celularNum){
    celular* actualCelular;
    this->celularesExistentes->iniciarCursor();
    while( this->celularesExistentes->avanzarCursor()&&!encontrado){
    	actualCelular = this->celularesExistentes->obtenerCursor();
    	encontrado = (celularNum == actualCelular->numeroDeCelular());

    }
    if (encontrado){
    	this->modoActual=modoAIniciar;
    }
    }
    return encontrado;
}

void redTelefonica::agregarCelular(unsigned int numero,int ID, zona zonaActual){
    celular* celularNuevo= new celular(numero,ID,zonaActual);
    celularNuevo->cambiarEstado(LIBRE);
    this->celularesExistentes->agregarDato(celularNuevo,1);
   }

void redTelefonica::agregarAntena(int ID,zona zonaACubrir,unsigned int capacidadMax){

    antena* antenaNueva = new antena(ID,zonaACubrir,capacidadMax);
    antenasExistentes->agregarDato(antenaNueva,1);
}


bool redTelefonica::realizarLlamada(uint destino,uint horaLlamada){
    bool puedeLlamar=(this->celularActual->obtenerEstado()==LIBRE);
    this-> celularesExistentes ->iniciarCursor();
    bool encontrado = false;
    celular* actual;
    while (celularesExistentes->avanzarCursor()&&(!encontrado)){
    	actual = celularesExistentes->obtenerCursor();
    	if ((actual->numeroDeCelular()==destino)&&(actual->obtenerEstado()==LIBRE)){
    		encontrado = true;
    	}
    }
    if (puedeLlamar && encontrado){
            this->celularActual->cambiarEstado(OCUPADO);
            actual->cambiarEstado(OCUPADO);
            llamada* nuevaLlamada = new llamada;
            nuevaLlamada->duracionLlamada = horaLlamada;
            nuevaLlamada->numeroEmisor = this->celularActual;
            nuevaLlamada->numeroReceptor = actual;
            nuevaLlamada->activa = true;
            llamadasActivas->agregarDato(nuevaLlamada,0);
            }
    return puedeLlamar;
}


void redTelefonica::cortarLlamada(unsigned int horaFinal){
    if (this->celularActual->obtenerEstado()==OCUPADO){
        this->celularActual->cambiarEstado(LIBRE);
        this-> llamadasActivas ->iniciarCursor();
            bool encontrado = false;
            llamada* llamada;
            while (llamadasActivas->avanzarCursor()&&(!encontrado)){
            	llamada = llamadasActivas->obtenerCursor();
            	if ((llamada->numeroEmisor==this->celularActual)&&(llamada->activa)){
            		encontrado = true;
            	}
            }
        if (encontrado){
        	llamada->duracionLlamada = (horaFinal-(llamada->horaInicio));
        	llamada->numeroEmisor->cambiarEstado(LIBRE);
        }
    }

    }



void redTelefonica::cambiarDeCelular(unsigned int celular){
    this->celularActual->asignarNumero(celular);
}



celular* redTelefonica::detalleCelular(int idCelular){
   this->celularesExistentes->iniciarCursor();
   bool encontrado;
   celular* celularActual;
   while ((this->celularesExistentes->avanzarCursor())&&(!encontrado))
    {
        celularActual=celularesExistentes->obtenerCursor();
        encontrado=celularActual->celularID()==idCelular;}
    if (!encontrado)
        {celularActual = 0;}
 return celularActual;
}

  antena* redTelefonica::detalleAntena(int idAntena){
   this->antenasExistentes->iniciarCursor();
   bool encontrado;
   antena* antenaActual;
   while ((this->antenasExistentes->avanzarCursor())&&(!encontrado))
    {   antenaActual=antenasExistentes->obtenerCursor();
        encontrado=antenaActual->obtenerID()==idAntena;}
    if (!encontrado)
        {
           antenaActual =0;
  }
    return antenaActual;}

 int redTelefonica::conectadosMax(int idAntena){
	    this-> antenasExistentes ->iniciarCursor();
	    bool encontrado = false;
	    int max =0;
	    antena* actual;
	    while (antenasExistentes->avanzarCursor()&&(!encontrado)){
	    	actual = antenasExistentes->obtenerCursor();
	    	encontrado = (actual->obtenerID()==idAntena);
	    }
	    if (encontrado){
	    	max = actual->obtenerMaxConexiones();
	    }
	    return max;
 }
 int redTelefonica::llamadasAnuladas(int idAntena){
	    this-> antenasExistentes ->iniciarCursor();
	    bool encontrado = false;
	    int max =0;
	    antena* actual;
	    while (antenasExistentes->avanzarCursor()&&(!encontrado)){
	    	actual = antenasExistentes->obtenerCursor();
	    	encontrado = (actual->obtenerID()==idAntena);
	    }
	    if (encontrado){
	    	max = actual->obtenerLlamadasAnuladas();
	    }
	    return max;
 }
 unsigned int redTelefonica::celularMasHablo(){
	this->antenasExistentes->iniciarCursor();
	this->celularesExistentes->iniciarCursor();
	int cantidadMaxima =0;
	celular* celularSupremo;
	while (celularesExistentes->avanzarCursor()){
		celular* actual = celularesExistentes->obtenerCursor();
		int cantidad =0;
		while (antenasExistentes->avanzarCursor()){
			antena* antenaActual = antenasExistentes->obtenerCursor();
			lista<estadisticas*>* stats = antenaActual->obtenerEstadisticas();
			stats->iniciarCursor();
			while (stats->avanzarCursor()){
				estadisticas* actualStats = stats->obtenerCursor();
				if (actualStats->numero == actual->numeroDeCelular()){
					cantidad+=actualStats->tiempoHablado;
				}
			}
		 }
		if (cantidad>cantidadMaxima){
			cantidadMaxima = cantidad;
			celularSupremo = actual;
		}
	}
	return celularSupremo->numeroDeCelular();
 }

 unsigned int redTelefonica::celularMasLlamo(){
	this->antenasExistentes->iniciarCursor();
	this->celularesExistentes->iniciarCursor();
	int cantidadMaxima =0;
	celular* celularSupremo;
	while (celularesExistentes->avanzarCursor()){
		celular* actual = celularesExistentes->obtenerCursor();
		int cantidad =0;
		while (antenasExistentes->avanzarCursor()){
			antena* antenaActual = antenasExistentes->obtenerCursor();
			lista<estadisticas*>* stats = antenaActual->obtenerEstadisticas();
			stats->iniciarCursor();
			while (stats->avanzarCursor()){
				estadisticas* actualStats = stats->obtenerCursor();
				if (actualStats->numero == actual->numeroDeCelular()){
					cantidad+=actualStats->tiempoHablado;
				}
			}
		 }
		if (cantidad>cantidadMaxima){
			cantidadMaxima = cantidad;
			celularSupremo = actual;
		}
	}
	return celularSupremo->numeroDeCelular();
 }

 unsigned int redTelefonica::celularMasLlamaron(){
	this->antenasExistentes->iniciarCursor();
	this->celularesExistentes->iniciarCursor();
	int cantidadMaxima =0;
	celular* celularSupremo;
	while (celularesExistentes->avanzarCursor()){
		celular* actual = celularesExistentes->obtenerCursor();
		int cantidad =0;
		while (antenasExistentes->avanzarCursor()){
			antena* antenaActual = antenasExistentes->obtenerCursor();
			lista<estadisticas*>* stats = antenaActual->obtenerEstadisticas();
			stats->iniciarCursor();
			while (stats->avanzarCursor()){
				estadisticas* actualStats = stats->obtenerCursor();
				if (actualStats->numero == actual->numeroDeCelular()){
					cantidad+=actualStats->tiempoHablado;
				}
			}
		 }
		if (cantidad>cantidadMaxima){
			cantidadMaxima = cantidad;
			celularSupremo = actual;
		}
	}
	return celularSupremo->numeroDeCelular();
 }

 unsigned int redTelefonica::celularMasOcupado(){
	this->antenasExistentes->iniciarCursor();
	this->celularesExistentes->iniciarCursor();
	int cantidadMaxima =0;
	celular* celularSupremo;
	while (celularesExistentes->avanzarCursor()){
		celular* actual = celularesExistentes->obtenerCursor();
		int cantidad =0;
		while (antenasExistentes->avanzarCursor()){
			antena* antenaActual = antenasExistentes->obtenerCursor();
			lista<estadisticas*>* stats = antenaActual->obtenerEstadisticas();
			stats->iniciarCursor();
			while (stats->avanzarCursor()){
				estadisticas* actualStats = stats->obtenerCursor();
				if (actualStats->numero == actual->numeroDeCelular()){
					cantidad+=actualStats->vecesOcupado;
				}
			}
		 }
		if (cantidad>cantidadMaxima){
			cantidadMaxima = cantidad;
			celularSupremo = actual;
		}
	}
	return celularSupremo->numeroDeCelular();
 }


 lista<llamada*>* redTelefonica::detalleLlamadasPor(unsigned int cel){
	 this->llamadasActivas->iniciarCursor();
	 lista<llamada*>* llamadasPorCel = new lista<llamada*>;
	 while(llamadasActivas->avanzarCursor()){
		 llamada* llamadaActual = llamadasActivas->obtenerCursor();
		 if (llamadaActual->numeroEmisor->numeroDeCelular()==cel){
			 llamadasPorCel->agregarDato(llamadaActual,0);
		 }
	 }
	 return llamadasPorCel;
 }
 lista<llamada*>* redTelefonica::detalleLlamadasPara(unsigned int cel){
	 this->llamadasActivas->iniciarCursor();
	 lista<llamada*>* llamadasPorCel = new lista<llamada*>;
	 while(llamadasActivas->avanzarCursor()){
		 llamada* llamadaActual = llamadasActivas->obtenerCursor();
		 if (llamadaActual->numeroReceptor->numeroDeCelular()==cel){
			 llamadasPorCel->agregarDato(llamadaActual,0);
		 }
	 }
	 return llamadasPorCel;
 }
 lista<llamada*>* redTelefonica::detalleLlamadasEntre(unsigned int cel1,unsigned int cel2){
	 lista<llamada*>* cel1Hechas = this->detalleLlamadasPor(cel1);
	 lista<llamada*>* cel2Hechas = this->detalleLlamadasPor(cel2);
	 lista<llamada*>* entreAmbos = new lista<llamada*>;
	 cel1Hechas->iniciarCursor();
	 while(cel1Hechas->avanzarCursor()){
		 llamada* actual = cel1Hechas->obtenerCursor();
		 if(actual->numeroReceptor->numeroDeCelular()==cel2){
			 entreAmbos->agregarDato(actual,0);
		 }
	 }
	 cel2Hechas->iniciarCursor();
	 while(cel2Hechas->avanzarCursor()){
	 		 llamada* actual = cel2Hechas->obtenerCursor();
	 		 if(actual->numeroReceptor->numeroDeCelular()==cel2){
	 			 entreAmbos->agregarDato(actual,0);
	 		 }
	 	}
	 return entreAmbos;
 }

 void redTelefonica::salir(){
	 this->modoActual = aDefinir;
	 this->celularActual = 0;
 }
 modo redTelefonica::obtenerModoActual(){
	 return this->modoActual;
 }
void redTelefonica::enviarMensaje(unsigned int destino,std::string texto, unsigned int hora){
	mensaje* mensajeTexto = new mensaje;
	mensajeTexto->emisor = this->celularActual->numeroDeCelular();
	mensajeTexto->receptor = destino;
	mensajeTexto->texto = texto;
	mensajeTexto->hora = hora;
	this->mensajesEnCola->agregarDato(mensajeTexto,0);
	this->mensajesHistorico->agregarDato(mensajeTexto,0);
}

lista<mensaje*>* redTelefonica::mensajesEntre(unsigned int cel1, unsigned int cel2){
	this->mensajesHistorico->iniciarCursor();
	lista<mensaje*>* entreAmbos = new lista<mensaje*>;
	while(this->mensajesHistorico->avanzarCursor()){
		mensaje* mensajeActual = this->mensajesHistorico->obtenerCursor();
		unsigned int a = mensajeActual->emisor;
		unsigned int b = mensajeActual->receptor;
		if ((a==cel1 and b == cel2)or(a==cel2 and b==cel1)){
			entreAmbos->agregarDato(mensajeActual,0);
		}

	}
	return entreAmbos;
}

void redTelefonica::procesarArchivoMaestro(){
	std::ofstream maestro ("TodasLasAcciones.txt");
	this->llamadasActivas->iniciarCursor();
	while(llamadasActivas->avanzarCursor()){
		llamada* actual = llamadasActivas->obtenerCursor();
		if (!actual->activa){
	maestro << ("LLAMADA: "+to_string(actual->numeroEmisor->numeroDeCelular())+ "a"
			+ to_string(actual->numeroReceptor->numeroDeCelular())+ " Duracion "
			+to_string(actual->duracionLlamada)) << std::endl;
	}}
	this->mensajesHistorico->iniciarCursor();
	while(this->mensajesHistorico->avanzarCursor()){
		mensaje* actual = this-> mensajesHistorico->obtenerCursor();
	maestro << ("MENSAJE: "+to_string(actual->emisor)+ "a"
			+ to_string(actual->receptor)+ " Hora "
			+to_string(actual->hora)) << std::endl;
	}
	maestro.close();
}
