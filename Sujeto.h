// ----------------------------------------------
// MATERIA: ESTRUCTURA DE DATOS
// PROFESOR: Ing. Pablo Akerman
// TP: Trabajo Práctico número 2
// GRUPO: LA7997
// INTEGRANTES: Varese, Lucas; Burgos, Alexis
// ----------------------------------------------
// ARCHIVO: Sujeto.h
// Contiene la definición de la clase Sujeto
// AUTOR: Lucas Varese (excepto donde mencionado)
// ----------------------------------------------

#pragma once
#include "Encuesta.h"

// La clase Sujeto representa a un encuestado
// que responde preguntas y guarda sus respuestas.
class Sujeto
{
public:
    Sujeto(); //Constructor
    ~Sujeto(); //Destructor

    // Devuelve el numero de objetos de la clase que fueron instanciados
    // AUTOR: Burgos, Alexis
    static unsigned int getTotalSujetos();

    // Devuelve el numero que identifica a una instancia de la clase
    // AUTOR: Burgos, Alexis
    unsigned int getSujetoNumero() const;

    // Devuelve un puntero hacia la posicion de memoria donde almacenar la respuesta a una pregunta
    // ENTRADA: numero que identifica a una pregunta
    // SALIDA: puntero hacia un entero
    int* responderPregunta(unsigned int pregunta);

    // Devuelve un puntero hacia el array respuestas
    int* getRespuestas() const;

    // Guarda si el sujeto respondio a cada pregunta de una encuesta
    // ENTRADA: booleano que indica si el sujeto respondio a todas las preguntas o no
    // AUTOR: Burgos, Alexis
    void setRespondioEncuesta(bool respondioEncuesta);

    // Devuelve si el sujeto respondio a todas las preguntas de una encuesta o no
    // AUTOR: Burgos, Alexis
    bool getRespondioEncuesta() const;
private:
    static unsigned int totalSujetos; // Guarda el numero de objetos de la clase que fueron instanciados
    unsigned int sujetoNumero; // Identifica univocamente a cada sujeto
    bool respondioEncuesta; // Guarda si el sujeto respondio a todas las preguntas de una encuesta
    int* respuestas; // Array que guarda las respuestas del sujeto a cada pregunta
};
