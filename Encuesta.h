// -------------------------------------------------------------------------------------------------------
// MATERIA: ESTRUCTURA DE DATOS
// PROFESOR: Ing. Pablo Akerman
// TP: Trabajo Práctico número 2
// GRUPO: LA7997
// INTEGRANTES: Varese, Lucas; Burgos, Alexis
// -------------------------------------------------------------------------------------------------------
// ARCHIVO: Encuesta.h
// Declara una estructura que compone el esqueleto de una encuesta
// Se deben modificar los datos de este archivo para realizar otro tipo de encuesta
// EJEMPLO: Para una encuesta a 200 sujetos, con 7 preguntas y, como máximo, 12 opciones por pregunta
//          se debe modificar (aparte del nombre y la población): tamaño = 200, numeroDePreguntas = 7,
//          numeroMaxDeOpciones = 12, y crear una dimensión en el array preguntas por cada una
//          de las 7 preguntas, respetando el siguiente formato:
//          { "Pregunta 1", "Categoría de las respuestas", "opción 1", "opción 2", ... , "opción n" },
//          { "Pregunta 2", "Categoría de las respuestas", "opción 1", "opción 2", ... , "opción n" },
//          { "Pregunta N", "Categoría de las respuestas", "opción 1", "opción 2", ... , "opción n" },
//          { "Pregunta Última", "Categoría de las respuestas", "opción 1", "opción 2", ... , "opción n" }
//          Cada dimensión debe terminar con una coma, excepto la última.
// AUTOR: Varese, Lucas
// -------------------------------------------------------------------------------------------------------

#pragma once
#include <string>

struct Encuesta
{
    const std::string nombre = "en1823CJ";
    const std::string poblacion = "Personas entre 18 y 23 anios";
    const unsigned int tamanio = 500; //TAMANIO DE LA MUESTRA (n° de personas a encuestar)
    static const unsigned int numeroDePreguntas = 2; //NUMERO DE PREGUNTAS DE SU ENCUESTA
    static const unsigned int numeroMaxDeOpciones = 8; //NUMERO DE OPCIONES DE LA PREGUNTA CON MAS OPCIONES
    const std::string preguntas[numeroDePreguntas][numeroMaxDeOpciones+2] = // VECTOR CON LAS PREGUNTAS
    {
        { "Cual es su comida favorita?", "COMIDAS", "Pizza", "Hamburguesa", "Milanesa", "Fideos", "Pescado", "Ensalada", "Empanada", "Otra" },
        { "Cual es su juego favorito?", "JUEGOS", "Cartas", "Juego de Mesa", "Video Juegos", "Deportes", "Otro" }/*,
        { "Cual es su mascota favorita?", "MASCOTAS", "Gato", "Perro", "Hamster" },
        { "Cual es su bebida favorita?", "BEBIDAS", "Coca-Cola", "Pepsi", "Seven-Up", "Fanta", "Cerveza", "Vino" }*/
    };

    // NO MODIFICAR ESTA SECCION ////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Devuelve la longitud de la opcion o del titular de seccion con la
    // mayor longitud en cada dimension del vector preguntas.
    // ENTRADA: string que indica la seccion para calcular la longitud,
    // los valores posibles son "titulo_seccion" y "opciones".
    unsigned int maximaLongCampo(std::string seccion) const
    {
        unsigned int max = 15;

        if(seccion.compare("titulo_seccion") == 0)
        {
            max = preguntas[0][1].length();
            for(unsigned int i = 0; i < numeroDePreguntas; ++i)
            {
                if(preguntas[i][1].length() > max)
                {
                    max = preguntas[i][1].length();
                }
            }
        }
        else if(seccion.compare("opciones") == 0)
        {
            max = preguntas[0][2].length();
            for(unsigned int i = 0; i < numeroDePreguntas; ++i)
            {
                for(unsigned int j = 2; j < numeroMaxDeOpciones+2; ++j)
                {
                    if(preguntas[i][j].length() > max)
                    {
                        max = preguntas[i][j].length();
                    }
                }

            }
        }
        return max;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
