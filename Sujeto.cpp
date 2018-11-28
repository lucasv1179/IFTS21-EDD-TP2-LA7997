// ------------------------------------------
// MATERIA: ESTRUCTURA DE DATOS
// PROFESOR: Ing. Pablo Akerman
// TP: Trabajo Práctico número 2
// GRUPO: LA7997
// INTEGRANTES: Varese, Lucas; Burgos, Alexis
// ------------------------------------------
// ARCHIVO: Sujeto.cpp
// Implementación de la clase Sujeto
// AUTOR: ver archivo Sujeto.h
// ------------------------------------------

#include "Encuesta.h"
#include "Sujeto.h"

unsigned int Sujeto::totalSujetos;

Sujeto::Sujeto()
{
    totalSujetos++;
    sujetoNumero = totalSujetos;
    respuestas = new int[Encuesta::numeroDePreguntas]; // Crea el array donde se guardan las respuestas del sujeto
    respondioEncuesta = false;
}

Sujeto::~Sujeto()
{
    if(respuestas)
    {
        delete[] respuestas;
    }
}

int* Sujeto::responderPregunta(unsigned int pregunta)
{
    // Devuelve la direccion de memoria donde
    // se debe guardar la respuesta a una pregunta determinada
    return &respuestas[pregunta];
}

int* Sujeto::getRespuestas() const
{
    return respuestas; // Devuelve un puntero al array de respuestas
}

unsigned int Sujeto::getTotalSujetos()
{
    return totalSujetos;
}

unsigned int Sujeto::getSujetoNumero() const
{
    return sujetoNumero;
}

bool Sujeto::getRespondioEncuesta() const
{
    return respondioEncuesta;
}

void Sujeto::setRespondioEncuesta(bool respondioEncuesta)
{
    this->respondioEncuesta = respondioEncuesta;
}
