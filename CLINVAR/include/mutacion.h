/**
 @file TDA clinvar
**/
/*
 * mutacion.h
 *
 * Copyright  (C) Juan F. Huete y Carlos Cano
*/
//**********************************************************************************************// 
//**************Jose Manuel Rodríguez Calvo****************************************************//
//********************************************************************************************//
#ifndef __MUTACION_H
#define __MUTACION_H

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "enfermedad.h"
#include <algorithm>
#include <stdlib.h>
#include <sstream>

using namespace std;

//! Clase mutacion, asociada a la definición de una mutación/SNP
/*! mutacion::mutacion,  .....
 *
 @todo Implementa esta clase, junto con su documentación asociada

*/


class mutacion {
 private:
  string ID;
  string chr;
  unsigned int pos;
  vector<string> ref_alt;
  vector<string> genes;
  bool common;
  vector<float> caf;
  vector<enfermedad> enfermedades;
  vector<int> clnsig;

 public:

/**
@brief constructor por defecto
**/
  mutacion();
/**
@brief constructor con un parametro mutacion
@param m:le pasa una mutacion y se la asigna a otra
**/
  mutacion(const mutacion& m);
/**
@brief constructor con un parametro string
@param str:le pasa un string con toda la informacion
**/
  mutacion(const string & str);   //para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada
  /**
@brief asigna a una mutacion la id
@param id:asigna id a la mutacion
**/
  void setID(const string & id);
/**
@brief asigna a una mutacion el cromosoma
@param chr:asigna chr a la mutacion
**/
  void setChr(const string & chr);
/**
@brief asigna a una mutacion la posicion
@param pos:asigna pos a la mutacion
**/
  void setPos(const unsigned int & pos);
/**
@brief asigna a una mutacion un vector con la referencia y la  alterntiva
@param ref:asigna ref_alt a la mutacion
**/
  void setRef_alt(const std::vector<string> & ref_alt);
/**
@brief asigna a una mutacion un vector con los genes
@param genes: asigna genes a la mutacion
**/
  void setGenes (const std::vector<string> & genes);
/**
@brief asigna a una mutacion un bool que dice si es comun en la poblacion
@param common: asigna common a la mutacion
**/
  void setCommon (const bool & common);
/**
@brief asigna a una mutacion la frecuencia con que se observa cada base descrita
@param caf: asigna caf a la mutacion
**/
  void setCaf (const std::vector<float> & caf);
/**
@brief asigna a una mutacion un vector con las enfermedades posibles que pueden ocurrir
@param enfermedades: asigna enfermedades  a la mutacion
**/
  void setEnfermedades (const std::vector<enfermedad> & enfermedades);
/**
@brief asigna a una mutacion un vector relevancia clínica del SNP
@param clnsig: asigna enfermedades clnsig a la mutacion
**/
  void setClnsig (const std::vector<int> & clnsig);
  /**
@brief devuelve el ID de una mutacion
@return el ID de la mutacion
**/
  string getID( ) const;
  /**
@brief devuelve el cromosoma de una mutacion
@return el cromosoma de la mutacion
**/
  string getChr( ) const;
  /**
@brief devuelve la posicion de una mutacion
@return la posicion de la mutacion
**/
  unsigned int getPos( ) const;
 /**
@brief devuelve un vector con la referencia y la alternativas a la mutacion
@return un vector con la referencia y la alternativa
**/
  const vector<string> & getRef_alt () const;
/**
@brief devuelve un vector con los genes de  la mutacion
@return un vector con los genes de la mutacion
**/
  const vector<string> & getGenes () const;
/**
@brief devuelve true o false  si la enfermedad es comun en la poblacion
@return un bool siendo true si la enfermedad es comun
**/
  bool getCommon () const;
/**
@brief devuelve un vector con la frecuencia con que se observa cada base descrita
@return un vector con las frecuencias float de las estadisticas
**/
  const vector<float> & getCaf () const;
/**
@brief devuelve un vector con las enfermedades que puede causar la mutacion
@return un vector de enfermedades correlacionadas con la mutacion
**/
  const vector<enfermedad> & getEnfermedades () const;
/**
@brief devuelve un vector con relevancia clínica del SNP
@return un vector de int segun su relevancia 0/1 - Incierta, Desconocida, 2 - Benigno, 3 - Probablemente be-
nigno, 4 - Probablemente patógeno, 5 - Patógeno, 6 - Relevante en respuesta a fármaco, 7 - Histocom-
patibilidad, 255 - Otro.
**/
  const vector<int> & getClnsig () const;


  string subcadena (const string inicial, string  buscado, string  del);
  const vector<string> subcadena_ref (const string inicial, string buscado, int pos);
/**
@brief sobrecarga de la operacion igual
@param m:la mutacion a la que se quiere igualar
@return this una referencia a la mutacion

**/
  mutacion & operator=(const mutacion & m);
/**
@brief sobrecarga de la comparacion igualitud
@param m:la mutacion la que se quiere comprobar
@return true si es igual o false si no lo es

**/
  bool operator==(const mutacion & m) const;
/**
@brief sobrecarga de la comparacion menor
@param m:la mutacion la que se quiere comprobar
@return true si es menor o false si no lo es

**/
  bool operator<(const mutacion & m) const;      //El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posición, de menor posición a mayor (orden natural de enteros).
  bool operator>(const mutacion & m) const;

};
/**
@brief sobrecarga de la sobrecarga de flujo
@param os:el fichero sobre el que se quiere poner
@param m:la mutacion la que se quiere comprobar
@return os sobre la que se quiere poner la mutacion

**/
  ostream& operator<< ( ostream& os , const mutacion& m);   //Imprimir TODOS los campos del objeto mutación.



#endif
