// ------------------------------------------
// MATERIA: ESTRUCTURA DE DATOS
// PROFESOR: Ing. Pablo Akerman
// TP: Trabajo Práctico número 2
// GRUPO: LA7997
// INTEGRANTES: Varese, Lucas; Burgos, Alexis
// ------------------------------------------
// ARCHIVO: Main.cpp
// AUTOR: Burgos, Alexis
// ------------------------------------------

#include "Encuesta.h"
#include "Sujeto.h"
#include "Encuestador.h"

const Encuestador::OrdenImpresion ORDEN_DE_IMPRESION = Encuestador::DEFAULT; // DEFAULT / ASC / DESC

int main()
{
    Encuestador e;
    e.realizarEncuesta();
	e.imprimirResultados(ORDEN_DE_IMPRESION);
    return 0;
}
