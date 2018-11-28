// --------------------------------------------------------------
// MATERIA: ESTRUCTURA DE DATOS
// PROFESOR: Ing. Pablo Akerman
// TP: Trabajo Práctico número 2
// GRUPO: LA7997
// INTEGRANTES: Varese, Lucas; Burgos, Alexis
// --------------------------------------------------------------
// ARCHIVO: Encuestador.h
// Contiene la definición de la clase Encuestador
// Esta clase se encarga de mostrar las preguntas de una encuesta
// y procesar las respuestas. También se encarga de ordenar
// e imprimir los resultados de la encuesta.
// USO: Encuestador e;
//      e.realizarEncuesta();
//      e.imprimirResultados(ordenDeImpresion)
// AUTOR: Varese, Lucas (excepto donde mencionado)
// --------------------------------------------------------------

#pragma once
#include "Encuesta.h"
#include "Sujeto.h"

class Encuestador
{
public:
    Encuestador(); // Constructor
    ~Encuestador(); // Destructor
    enum OrdenImpresion {DESC, ASC, DEFAULT = 0}; // Representa los ordenes de impresion disponibles

    // Devuelve el array donde se encuentran los Sujetos
    // que potencialmente participaran de la encuesta
    Sujeto* getMuestra() const;

    // Interactua con otros metodos de la clase para realizar la encuesta
    void realizarEncuesta();

    // Imprime en pantalla los resultados obtenidos en la encuesta
    // ENTRADA: el orden de impresion a realizar. Los valores posibles son
    // DEFAULT, ASC, DESC.
    void imprimirResultados(OrdenImpresion orden);
private:
    enum Menu {MENU_PPAL, MENU_PREGUNTA}; // Representa los menus disponibles
    OrdenImpresion ordenDeImpresion; // Guarda el orden en que se imprimiran los resultados
    Menu menuAMostrar; // Guarda el proximo menu a mostrar en pantalla

    // Realiza el display en pantalla de los datos de la encuesta
    // y de las preguntas y opciones de la misma.
    // AUTOR: Burgos, Alexis
    void mostrarMenu() const;

    // Por cada sujeto que participo de la encuesta,
    // almacena sus respuestas a cada pregunta en un
    // acumulador general para la encuesta (resultadoEncuesta).
    void procesarEncuesta();

    // Ordena los resultados de la encuesta de forma
    // ascendente o descendente. Utiliza el algoritmo
    // de ordenamiento bubble sort.
    void ordenarResultados();

    Encuesta encuesta; // Guarda los datos de la encuesta
    Sujeto* muestra; // Guarda la muestra de Sujetos a ser encuestados
    unsigned int** resultadoEncuesta; // Acumula la cantidad de veces que se elije cada respuesta

    // Elemento auxiliar que mantiene la relacion
    // entre el indice y el contenido de resultadoEncuesta
    unsigned int** indicesResultadoEncuesta;
};
