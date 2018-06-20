/**
 @file TDA clinvar
**/
//**********************************************************************************************//
//**************Jose Manuel Rodríguez Calvo****************************************************//
//********************************************************************************************//
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "enfermedad.h"
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include"mutacion.h"
#include <set>
#include <map>
#include <unordered_map>
#include <list>
#include<queue>
#include<unordered_set>


typedef string IDgen;
typedef string IDmut;
typedef string IDenf;
//!clase ProbMutacion,es el functor que
/*!ProbMutacion
*
@esta clase sirve para ordenar mutaciones segun su existencia
*/
class ProbMutacion{
  /**
  @brief sobrecarga del operador () que compara si la mutacion a es mas comun que la mutacion b
  @param a: es la primera mutacion
  @param b: es la segunda mutacion
  @return verdadero si el caf[0] de mutacion a es mayor que caf [0] de b, si a==b se compara los ID
  **/
public:bool operator()(const mutacion &a,const mutacion &b);
};

//!clase clinvar
/*!clinvar
*
@esta es la clase principal que contiene todo
*/

class clinvar{
  int b=0;
  friend class gen_iterator;

public:
  typedef map<IDenf,enfermedad>::iterator enfermedad_iterator;
  //!clase iterator
  /*!iterator
  *
  @esta es la clase iterator
  */
  class iterator{
  private:
  set<mutacion>::iterator it;
  public:
    iterator();
    /**
    @brief es el constructor de copia
    @param x:es un iterador al set<mutacion>
    **/
    iterator(const set<mutacion>::iterator &x);
    /**
    @brief sobrecarga del operator *()
    @return una mutacion al que apunta en set mutDB
    **/
    mutacion operator*();
    /**
    @brief sobrecarga del operator =
    @param x:es un iterator de mutDB
    **/
    void operator =(const set<mutacion>::iterator &x);
    /**
    @brief sobrecarga del operator !=
    @param x:es un iterator de mutDB
    @param y:es otro iterator de mutDb
    @return true si son diferentes
    **/
    bool operator !=(const iterator &x);

    iterator operator++();
  };
  //!clase gen_iterator
  /*!gen_iterator
  *
  @esta es la clase gen_iterator
  */
  class gen_iterator{
    friend class clinvar;
  private:
  map<IDgen,list<set<mutacion>::iterator>>::iterator it_map;
  list<set<mutacion>::iterator>::iterator itlist;
  clinvar *ptrclinvar;
  public:
    /**
    @brief constructor por defecto vacio
    **/
    gen_iterator( );
    /**
    @brief sobrecarga del operador ++
    @return un gen_iterator al siguiente elemento de itlist o al principio del siguiente it_map
    **/
    gen_iterator operator++();
    /**
    @brief sobrecarga del operator *()
    @return la mutacion que se corresponde con el elemento al que apunta de el iterador de itlist
      **/
    mutacion operator*();
  };
private:
set<mutacion>mutDB;//base de datos que contiene toda la informacion asociada a una mutacion
unordered_map <IDmut,set<mutacion>::iterator>IDm_map;//Asocia IDmutacion con mutacion
map<IDgen,list<set<mutacion>::iterator>>gen_map;//Asocia genes con mutaciones
map<IDenf,enfermedad>EnfDB;//Base de datos de enfermedades
multimap<IDenf,set<mutacion>::iterator>IDenf_map;//Asocia enfermedad con mutacion
public:
  iterator begin();
  /**
@brief se pone al final de mutDB
@return un iterator final de mutDB
  **/
  iterator end();
/**
@brief apunta a la primera mutacion que es igual o el end
@param cromosoma:es el cromosoma de la mutacion
@param posicion:es la posicion de la mutacion
@return un iterador a la primera mutacion que es igual o el end
**/
  iterator lower_bound(string cromosoma,int posicion);
  /**
  @brief apunta a la primera mutacion que es igual o a la siguiente mayor
  @param cromosoma:es el cromosoma de la mutacion
  @param posicion:es la posicion de la mutacion
  @return un iterador a la primera mutacion que es igual o a la siguiente si no se encuentra
  **/
  iterator upper_bound(string cromosoma,int posicion);
  /**
@brief se pone al principio de gen_iterator poniendo it_map a begin()
@return un gen_iterator al principio de gen_map
  **/
  gen_iterator gbegin();
  /**
@brief se pone al final de gen_iterator poniendo it_map a end()
@return un gen_iterator final de gen_map
  **/
  gen_iterator gend();
  /**
@brief se pone a principio de EnfDB
@return un iterator al principio de  EnfDB
  **/
  enfermedad_iterator ebegin();
  /**
@brief se pone al final de EnfDB
@return un iterator al final de EnfDB
  **/
  enfermedad_iterator eend();
  /**
  @brief es el constructor vacio por defecto
  **/
  clinvar();
  /**
  @brief carga un fichero en el programa usa el metodo insert(string  nombreDB)
  @param nombreDB: Debe ser el redirecionamiento entero
  **/
  void load(string nombreDB);
  /**
  @brief inserta en mutDB un la mutacion, IDM_map guarda el ID de la mutacion y un puntero al mutDB, en gen_map guarda el id de los genes asociados a la mutacion y una lista con  punteros a mutDB de la mutacion que contiene ese gen, en EnfDB guarda el nombre de las enfermedades y la enfermedad y por ultimo en IDenf_map guarda el nombre y un iterador a set de la mutacion asociada
  @param x:la mutacion que vamos almacenar en los distintos contenedores
  **/
  void insert(const mutacion &x);
  /**
@brief borra todo lo que tiene que ver con la mutacion que tiene el nombre ID,borra todo lo que yace de él
@param ID:el nombre de la mutacion
@return true si consigue hacer todo
  **/
  bool erase(IDmut ID);
  /**
@brief busca la mutacion con el ID
@param ID:el nombre de la mutacion
@return un iterator a mutDB que tiene el ID
  **/
  iterator find_Mut(IDmut ID);
  /**
@brief busca la enfermedad con el ID
@param ID:el nombre de la enfermedad
@return un enfermedad_iterator que apunta a EnfDB con la enferemedad
  **/
  enfermedad_iterator find_Enf(IDenf ID);
  /**
@brief consigue todas las enfermedades de una mutacion
@param m:la mutacion a la que queremos conseguir las enfermedades
@return un vector de enfermedades que contiene m
  **/
  vector<enfermedad>getEnfermedades(mutacion &m);
  /**
@brief consigue las enfermedades que contiene keyword
@param keyword:la palabra o parte de ella que queremos buscar en el nombre de las enferemedades
@return una lista con el ID de las enferemedades que contiene keyword
  **/
  list<IDenf>getEnfermedades(const string &keyword);
  /**
@brief dada el nombre de una enferemedad busca todas las mutaciones que contiene esa enfermedad
@param ID:nombre de la enfermedad
@return un set con el ID de las mutaciones que contiene la enfermedad con el nombre ID
  **/
  set<IDmut>getMutacionesEnf(IDenf ID);
  /**
@brief dada el nombre de un gen busca todas las mutaciones que contiene ese gen
@param ID:nombre del gen
@return un set con el ID de las mutaciones que contiene el gen con el nombre ID
  **/
  set<IDmut>getMutacionesGen(IDgen ID);
  /**
@brief dado un entero y un nombre que con el consigue todas las mutaciones cuyas enfermedades contengan keyword las almacena segun ProbMutacion y devuelve solo hasta las dadas por el entero
@param k:el entero del numero maximo de mutacion que va Almacenar
@param keyword:el nombre o parte del nombre de la enfermedad a la que buscaremos sus mutaciones asociadas
@return un set con las mutaciones ordenadas segun ProbMutacion
  **/
  set<mutacion,ProbMutacion>topKMutaciones(int k,string keyword);
  /**
@brief se pone a principio de mutDB
@return un iterator al principio de mutDB
  **/

};
