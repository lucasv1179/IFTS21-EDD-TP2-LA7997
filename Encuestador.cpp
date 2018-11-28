// ------------------------------------------
// MATERIA: ESTRUCTURA DE DATOS
// PROFESOR: Ing. Pablo Akerman
// TP: Trabajo Práctico número 2
// GRUPO: LA7997
// INTEGRANTES: Varese, Lucas; Burgos, Alexis
// ------------------------------------------
// ARCHIVO: Encuestador.cpp
// Implementación de la clase Encuestador
// AUTOR: ver archivo Encuestador.h
// ------------------------------------------

#include "Encuesta.h"
#include "Sujeto.h"
#include "Encuestador.h"
#include <iostream>
#include <iomanip>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::right;

Encuestador::Encuestador()
{
    muestra = new Sujeto[encuesta.tamanio];

    resultadoEncuesta = new unsigned int*[encuesta.numeroDePreguntas];
    for(unsigned int i = 0; i < encuesta.numeroDePreguntas; ++i)
    {
        resultadoEncuesta[i] = new unsigned int[encuesta.numeroMaxDeOpciones]();
    }

    indicesResultadoEncuesta = new unsigned int*[encuesta.numeroDePreguntas];
    for(unsigned int i = 0; i < encuesta.numeroDePreguntas; ++i)
    {
        indicesResultadoEncuesta[i] = new unsigned int[encuesta.numeroMaxDeOpciones]();
    }

    ordenDeImpresion = DEFAULT; // El orden de impresion es descendente por defecto

    menuAMostrar = MENU_PPAL;

}

Encuestador::~Encuestador()
{
    if(muestra)
    {
        delete[] muestra;
    }

    for (unsigned int i = 0; i < encuesta.numeroDePreguntas; ++i)
    {
        if(resultadoEncuesta[i])
        {
            delete[] resultadoEncuesta[i];
        }

    }

    for (unsigned int i = 0; i < encuesta.numeroDePreguntas; ++i)
    {
        if(indicesResultadoEncuesta[i])
        {
            delete[] indicesResultadoEncuesta[i];
        }

    }

    if(resultadoEncuesta)
    {
        delete[] resultadoEncuesta;
    }

    if(indicesResultadoEncuesta)
    {
        delete[] indicesResultadoEncuesta;
    }
}

void Encuestador::realizarEncuesta()
{
    mostrarMenu();
    unsigned int sujeto = 0;
    int respuesta = encuesta.numeroMaxDeOpciones+1; // Inicializo en un numero de respuesta invalido
    bool respondioEncuesta = true;

    do
    {
        cout << "[ *** ENCUESTADO Nro " << muestra[sujeto].getSujetoNumero() << " *** ]" << endl << endl;

        for(unsigned int numeroDePregunta = 0; numeroDePregunta < encuesta.numeroDePreguntas; ++numeroDePregunta)
        {

            if(respuesta > 0)
            {
                menuAMostrar = MENU_PREGUNTA;
                mostrarMenu();

                cin >> respuesta;

                // Al sujeto siendo encuestado debo pasarle el numero de pregunta
                // a responder para que me devuelva la direccion donde guardar la respuesta.
                //
                // El menu muestra opciones de respuestas comenzando en 1, por eso se guarda respuesta - 1,
                // ya que en el resto del programa las respuestas comienzan en 0
                *muestra[sujeto].responderPregunta(numeroDePregunta) = respuesta-1;

                cout << endl;

                if(respuesta <= 0)
                {
                    respondioEncuesta = false;
                }
            }
        }

        // Cada sujeto sabe si respondio toda la encuesta para luego
        // poder ser contabilizado o no al momento de procesar la misma.
        muestra[sujeto].setRespondioEncuesta(respondioEncuesta);

    } while(++sujeto < encuesta.tamanio && respuesta > 0); // La encuesta termina con el ingreso de 0 o menor como respuesta

    procesarEncuesta(); // Se procesa la encuesta directamente ya que una encuesta sin procesar careceria de valor
}

void Encuestador::mostrarMenu() const
{
    static unsigned int numeroDePregunta = 0; // Se debe mantener el numero de pregunta entre cada llamada al metodo
    unsigned int pregunta = 0;
    unsigned int categoria = 1;

    if(menuAMostrar == MENU_PPAL)
    {
        cout << "ENCUESTA (" << encuesta.nombre << ")" << endl
             << "-------------------" << endl << endl;
    }
    else if(menuAMostrar == MENU_PREGUNTA)
    {
        cout << encuesta.preguntas[numeroDePregunta][pregunta] << endl << endl;

        cout << encuesta.preguntas[numeroDePregunta][categoria] << endl;

        // Para que la linea que subraya la categoria sea del mismo tamanio de esta
        for(unsigned int i = 0; i < encuesta.preguntas[numeroDePregunta][categoria].length(); ++i)
        {
            cout << "-";
        }

        cout << endl;

        // opcion refleja la posicion de la primera opcion en el array de preguntas, que es siempre 2
        for(unsigned int opcion = 2; opcion < encuesta.numeroMaxDeOpciones+2; ++opcion)
        {
            // Solo se deben mostrar los indices que contengan opciones
            if(encuesta.preguntas[numeroDePregunta][opcion].compare("") != 0)
            {
                cout << "[" << opcion-1 << "] " << encuesta.preguntas[numeroDePregunta][opcion] << endl;
            }

        }

        cout << endl
             << "Elija una opcion o ingrese 0 para terminar: "; // La encuesta termina ingresando 0 (cero)

        ++numeroDePregunta;

        // Cuando ya se hicieron todas las preguntas, se debe resetear la variable para el sujeto siguiente
        if(numeroDePregunta == encuesta.numeroDePreguntas)
        {
            numeroDePregunta = 0;
        }
    }
}

void Encuestador::procesarEncuesta()
{
    unsigned int sujeto = 0;

    // Solo se procesan los sujetos que respondieron todas las preguntas de la encuesta
    while(muestra[sujeto].getRespondioEncuesta() && sujeto < encuesta.tamanio)
    {
        for(unsigned int numeroDePregunta = 0; numeroDePregunta < encuesta.numeroDePreguntas; ++numeroDePregunta)
        {
            for(unsigned int opcion = 0; opcion < encuesta.numeroMaxDeOpciones; ++opcion)
            {
                if(muestra[sujeto].getRespuestas()[numeroDePregunta] == static_cast<int>(opcion))
                {
                    // ResultadoEncuesta acumula las opciones elegidas para cada pregunta
                    // el indice 0 de la primera dimension, representa la pregunta 1
                    // el indice 0 de la segunda dimension, representa la opcion 1
                    resultadoEncuesta[numeroDePregunta][opcion]++;
                }
            }
        }

        ++sujeto; // Proceso al sujeto siguiente
    }
}

void Encuestador::imprimirResultados(OrdenImpresion orden)
{
    ordenDeImpresion = orden;

    ordenarResultados(); // Deben ordenarse los resultados antes de imprimirlos

    string sOrden = "";

    if(ordenDeImpresion == DESC)
    {
        sOrden = "descendente";
    }
    else if(ordenDeImpresion == ASC)
    {
        sOrden = "ascendente";
    }

    cout << "\nRESULTADO DE LA ENCUESTA (en orden " << sOrden << ")" << endl
         << "-----------------------------------------------" << endl;

    int totalRespuestas = 0;
    for(unsigned int sujeto = 0; sujeto < Sujeto::getTotalSujetos(); ++sujeto)
    {
        if(muestra[sujeto].getRespondioEncuesta())
        {
            totalRespuestas++; // Calculo la cantidad de sujetos que respondieron la encuesta para poder imprimirlo
        }
    }

    cout << totalRespuestas << " de " << Sujeto::getTotalSujetos()
         << (totalRespuestas > 1 ? " respondieron" : " respondio")
         << " la encuesta." << endl << endl;

    unsigned int seccion = 1;
    for(unsigned int numeroDePregunta = 0; numeroDePregunta < encuesta.numeroDePreguntas; ++numeroDePregunta)
    {
        cout << setw(static_cast<int>(encuesta.maximaLongCampo("titulo_seccion"))) << left
             << encuesta.preguntas[numeroDePregunta][seccion] << endl << endl;

        for(unsigned int opcion = 0; opcion < encuesta.numeroMaxDeOpciones; ++opcion)
        {
            // Ya que cada pregunta tiene un numero diferente de opciones, solo se imprimen las opciones validas
            if(encuesta.preguntas[numeroDePregunta][indicesResultadoEncuesta[numeroDePregunta][opcion]+2].compare("") != 0)
            {
                cout << setw(static_cast<int>(encuesta.maximaLongCampo("opciones")+2)) << left
                     << encuesta.preguntas[numeroDePregunta][indicesResultadoEncuesta[numeroDePregunta][opcion]+2]
                     << " " << setw(4) << right << resultadoEncuesta[numeroDePregunta][opcion] << endl;
            }
        }
        cout << endl;
    }
}

void Encuestador::ordenarResultados()
{
    int aux;
    int indiceAux;
    bool huboCambios = true;

    // Se inicializa cada posicion del array de indices para que mantenga una correlacion
    // entre los indices y los valores del array de resultados
    for(unsigned int numeroDePregunta = 0; numeroDePregunta < encuesta.numeroDePreguntas; ++numeroDePregunta)
    {
        for(unsigned int opcion = 0; opcion < encuesta.numeroMaxDeOpciones; ++opcion)
        {
            indicesResultadoEncuesta[numeroDePregunta][opcion] = opcion;
        }
    }

    // Se utiliza un algoritmo de ordenamiento bubble sort para ordenar los resultados de cada pregunta
    for(unsigned int numeroDePregunta = 0; numeroDePregunta < encuesta.numeroDePreguntas; ++numeroDePregunta)
    {
        while(huboCambios)
        {
            huboCambios = false;
            for (unsigned int opcion = 0; opcion < encuesta.numeroMaxDeOpciones - 1; ++opcion)
            {
                if(ordenDeImpresion == ASC)
                {
                    if (resultadoEncuesta[numeroDePregunta][opcion + 1] < resultadoEncuesta[numeroDePregunta][opcion])
                    {
                        // Los cambios en el array resultado se espejan en el array indices
                        // asi se mantiene una relacion entre la nueva posicion del valor y el indice
                        // al que pertenece. (el indice representa la opcion)
                        aux = resultadoEncuesta[numeroDePregunta][opcion];
                        indiceAux = indicesResultadoEncuesta[numeroDePregunta][opcion];

                        resultadoEncuesta[numeroDePregunta][opcion] = resultadoEncuesta[numeroDePregunta][opcion + 1];
                        indicesResultadoEncuesta[numeroDePregunta][opcion] = indicesResultadoEncuesta[numeroDePregunta][opcion + 1];

                        resultadoEncuesta[numeroDePregunta][opcion + 1] = aux;
                        indicesResultadoEncuesta[numeroDePregunta][opcion + 1] = indiceAux;

                        huboCambios = true;
                    }
                }
                else if(ordenDeImpresion == DESC)
                {
                    if (resultadoEncuesta[numeroDePregunta][opcion + 1] > resultadoEncuesta[numeroDePregunta][opcion])
                    {
                        aux = resultadoEncuesta[numeroDePregunta][opcion];
                        indiceAux = indicesResultadoEncuesta[numeroDePregunta][opcion];

                        resultadoEncuesta[numeroDePregunta][opcion] = resultadoEncuesta[numeroDePregunta][opcion + 1];
                        indicesResultadoEncuesta[numeroDePregunta][opcion] = indicesResultadoEncuesta[numeroDePregunta][opcion + 1];

                        resultadoEncuesta[numeroDePregunta][opcion + 1] = aux;
                        indicesResultadoEncuesta[numeroDePregunta][opcion + 1] = indiceAux;

                        huboCambios = true;
                    }
                }
            }
        }

        huboCambios = true;
    }
}

Sujeto* Encuestador::getMuestra() const
{
    return muestra;
}
