/**
 @file TDA clinvar
**/
/*
 * enfermedad.h
 *
 * Copyright  (C) Juan F. Huete y Carlos Cano
*/
//**********************************************************************************************// 
//**************Jose Manuel Rodríguez Calvo****************************************************//
//********************************************************************************************//
#ifndef __ENFERMEDAD_H
#define __ENFERMEDAD_H

#include <string>
#include <cstring>
#include <iostream>


using namespace std;

//! Clase enfermedad, asociada al TDA enfermedad
/*! enfermedad::enfermedad,  .....
 * Descripción contiene toda la información asociada a una enfermedad almacenada en la BD ClinVar-dbSNP (nombre de la enfermedad, id, BD que provee el id)

 @todo Implementa esta clase, junto con su documentación asociada

*/

class enfermedad {
private:
  string  name;       // nombre de la enfermedad. Almacenar completo en minúscula.
  string  ID;         // ID único para la enfermedad
  string  database;   // Base de datos que provee el ID

public:
/**
@brief constructor por defecto
**/
 enfermedad(); //Constructor de enfermedad por defecto
 /**
     @brief construye una enfermedad
     @param name: el nuevo nombre de la enfermedad
     @param ID: el nuevo ID de la enfermedad
     @param database: el nuevo database de la enfermedad
   **/
 enfermedad(const string & name, const string & ID, const string & database);
 /**
     @brief Modifica el nombre de la enfermdad
     @param name: el nuevo nombre de la enfermedad
   **/
 void setName(const string & name);
  /**
     @brief Modifica el ID de la enfermdad
     @param ID: el nuevo ID de la enfermedad
   **/
 void setID(const string & ID);
  /**
     @brief Modifica la database de la enfermdad
     @param database: el nuevo database de la enfermedad
   **/
 void setDatabase(const string & database);
/**
   @brief Devuelve el nombre de la enfermedad
   @return nombre de la enfermedad
 **/
 string getName( ) const;
/**
   @brief Devuelve el ID de la enfermedad
   @return ID de la enfermedad
 **/
 string getID( ) const;
/**
   @brief Devuelve el Database de la enfermedad
   @return database de la enfermedad
 **/
 string getDatabase( ) const;
 /**
    @brief Se asigna una enfermedad
    @param e: la enfermedad que se asigna
    @return una referencia a la enfermdad
 **/
 enfermedad & operator=(const enfermedad & e);
 /**
    @brief Convierte una enfermedad a string

    @return string de la enfermedad
 **/
 string toString() const;
 /**
    @brief Sobrecarga del operador == para ver si es igual
    @param e: la enfermedad que se compara
    @return true si es igual y false si es diferente
 **/

// Operadores relacionales
 bool operator==(const enfermedad & e) const;
/**
    @brief Sobrecarga del operador != para ver si es diferente
    @param e: la enfermedad que se compara
    @return true si es diferente y false si es igual
 **/
 bool operator!=(const enfermedad & e) const;
 /**
    @brief Sobrecarga del operador < para ver si es diferente
    @param e: la enfermedad que se compara
    @return true si el nombre es menor y false si es mayor
 **/
 bool operator<(const enfermedad & e) const;	//Orden alfabético por campo name.
 /**
    @brief Comprueba si el string que le pasa esta contenido
    @param str: el string que hay que buscar
    @return true si esta contenido
 **/

 bool operator>(const enfermedad & e) const;
 bool nameContains(const string & str) const;   //Devuelve True si str está incluido en el nombre de la enfermedad, aunque no se trate del nombre completo. No debe ser sensible a mayúsculas/minúsculas.



};
 /**
    @brief sobrecarga el operador de salida
    @param os: el ostream sobre el que mostra la enfermedad
    @param e: enfermedad que se va a mostrar
    @return ostream del archivo ya volcado
 **/
 ostream& operator<< ( ostream& os, const enfermedad & e); //imprime enfermedad (con TODOS sus campos)


#endif
