/**
 * @file Nmer.h
 * @brief TDA Nmer
 *   Representa un conjunto de Nmer subsecuencias de tamaño 1 hasta N que se pueden obtener a partir de una cadena de ADN
 * @author alumno
 * @bug Por espeficicar
 */
#ifndef __NMER_H
#define __NMER_H

#include "ktree.h"
#include <string>
#include <map>
#include <set>

using namespace std;

class Nmer {


public:
  class ordenCrec;
  class ordenDecre;
  typedef unsigned int size_type;

private:
//estos son los metodos auxiliares
/** @brief convierte un carcater en la posicion a la que se refiere .
    @param carcater: es el caracter al que queremos saber a que posicion corresponde
    @return el entero al que corresponde el caracter
 */
int elemento(const char caracter)const;

/** @brief dado un nodo inserta una cadena a partir de ese nodo
    @param n:el nodo por el que se quiere conseguir el string hacia arriba
    @param adn:el adn que se quiere insertar en el arbol
 */
void insert_adn (ktree<pair<char,int>,4>::node n, const string & adn);
/** @brief dado un nodo va mostrando la subcadena desde el root hasta ese nodo
    @param n:el nodo por el que se recore en preorden para mostrarlo por pantalla
 */
void recorrido_preorden(ktree<pair<char,int>,4>::const_node n)const;
/** @brief dado un nodo va insertando todos los nodos que hay desde esta hasta la raiz
    @param n:el nodo a partir del cual se quiere insertar
    @param nmer:el arbol sobre el que se quiere insertar todos los nodos
 */
void insertarTodos(ktree<pair<char,int>,4>::node n, Nmer &nmer);
/** @brief va recorriendo en dos arboles y comprueba si valen las mismas las etiquetas
    @param n1:el nodo del primer arbol
    @param n2:el nodo del segundo arbol
    @return true si lo contiene false si no son iguales
 */
bool contenido(ktree<pair<char,int>,4>::const_node n1,ktree<pair<char,int>,4>::const_node n2)const;


void ranking(	ktree<pair<char,int>,4>::const_node n_act,set<pair<string,int>,ordenDecre> &myset);

/** @brief va a ir comparando si es menor/mayor que threshold y lo va a insertar en s
    @param n:para recorrer el arbol
    @param s:es el contendor set
 */
template <typename S, typename CMP>
void cmpNmer(ktree<pair<char,int>,4>::node n, int threshold, S &s);
/** @brief va buscando los que son justo iguales a threshold y lo va insertando en s
@param n:es el nodo para moverse sobre el arbol

    @param s:es el contendor set para almacenar las subcadenas
  @param l:es el entero threshold sobre el que va a ir a comparando
  @param lactual:es el entero para ir comparandolo con l

 */
void equalnmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, Nmer::ordenCrec > & s, int l, int lactual);

public:
  /** @brief dado un nodo va iendo hacia la raiz y lo va insertando en un string.
      @param n:el nodo por el que se quiere conseguir el string hacia arriba
      @return el string formado por las etiquetas concadenadas de los nodos hacia su raiz
   */
  string obtenerNmer(ktree<pair<char,int>,4>::const_node n)const;
  /** @brief Constructor primitivo .
   * Crea un Nmer de longitud maxima 0, con el valor ('-',0) en la raíz
   */
  Nmer();

/**
 *
 */
  Nmer(const Nmer & a);

/** @brief Imprime los Nmers
 *  @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
 */
  void list_Nmer() const;

/** @brief Máxima longitud de los Nmers almacenados
 */
  unsigned int length()const;

/** @brief Número de Nmers almacenados
 */
  size_type size() const;

/**
 *
 */
  Nmer & operator=(const Nmer & a); // operador de asignacion

/**
*@brief haya un subarbol a partir de la cadena dada
*@param:adn es la cadena para bejar sobre el arbol
 *@return  Devuelve el Nmer (subarbol) asociado a un prefijo. Por ejemplo, si adn es "ACT", devuelve el Nmer que representa todas las subcadenas que empiezan por "ACT" (ACT*)
 */
  Nmer Prefix(string adn); //

/**
*@brief hace la union de dos arboles
*@param:reference es el arbol sobre el que se hace la union
 *@return  Se devuelve un Nmer donde para cada nodo (representa una secuencia) se computa la suma de las frecuencias en *this y en referencia
 */
  Nmer Union(const Nmer reference);//
/**
*@brief mira a ver si esta contenida la cadena en el arbol
*@param:adn mira si esta la adn en el arbol
 *@return Devuelve true si la cadena adn está representada en el árbol
 */

  bool containsString(const string adn) const; //

/**
*@brief mira a ver si el arbol esta inluido en otro arbol
*@param:reference mira a ver si el arbol esta contenido en this
 *@return  Devuelve true si cada nodo de *this está también representado en reference, es decir, si todas las secuencias representadas en el árbol de *this están también incluidas en reference. False en otro caso.
 */

  bool included(const Nmer reference) const; //

/**
*@brief partir de una cadena va construyendo el arbol
*@param:l es sobre cuantas partes quieren que se haga la cadena
*@param:adn es la cadena del arbol
 *@return devuelve true si esta incluido el arbol en this
 */
  void sequenceADN(unsigned int l, const string & adn);

/** @brief lectura fichero serializado
 * @param nombre_fichero fichero serializado con extension .srl
 *
 * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
 *
 * La cadena original viene descrita en el fichero serializado
 */
  bool loadSerialized(const string & nombre_fichero);

/**
 *@brief calcula la distancia entre dos arboles
 *@param:x es el arbol sobre el cual se quiere hayar la distancia
 *@return la distancia entre ambos
 */
  float Distance(const Nmer & x);
/**
 *@brief calcula los nmers menos comunes en Nmer
 *@param: threshold es para calcular los nmer menores que threshold
 *@return un set con los elementos que cumplen esta propiedad de raro
 */
  set<pair<string,int>,ordenCrec > rareNmer(int threshold);

/**
 *@brief los nmers mas comunes dentro de Nmer
 *@param:threshold es para calcular los nmer mayores que threshold
 *@return un set con los elementos que cumplen esta propiedad de comun
 */
  set<pair<string,int>,ordenDecre > commonNmer(int threshold);

/**
 *@brief calula los nmers cuya tamaanio es exactamente l
 *@param:l es para ver los que son igual de nmers
 *@return un set con los elementos que cumplen esta propiedad de igualdad
 */
  set<pair<string,int>, ordenCrec > level(int l);



private:
  ktree<pair<char,int>,4> el_Nmer; // subsecuencias
  unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol

  /** @brief Functor para convertir un string en un pair<char,int>
   * se utiliza en loadSerialized
   */
  class String2Base {
  public:
    pair<char,int> operator()( const string & cad) {
	     pair<char,int> salida;
	     salida.first = cad[0];
	     salida.second = std::stoi(cad.substr(1));
	     return salida;
    }
  };
  /**
   *
   */
 public:
  class ordenCrec{
  public:
    bool operator()(const pair<string,int> &par1, const pair<string,int> &par2){
      bool correcto = false;

      if(par1.first < par2.first)
        correcto = true;
      else if(par1.second < par2.second)
        correcto = true;

      return correcto;
    }
  };



  /**
   *
   */
  class ordenDecre{
  public:
    bool operator()(const pair<string,int> &par1, const pair<string,int> &par2){
      bool correcto = false;

      if(par1.first > par2.first)
        correcto = true;
      else if(par1.second > par2.second)
        correcto = true;

      return correcto;
    }
  };

  class ordenRare{
    public:
      bool operator()(const pair<string,int> &par1, const pair<string,int> &par2){
        bool correcto = false;

        if(par1.second <= par2.second)
          correcto = true;

        return correcto;
      }
    };

    class ordenCommon{
    public:
      bool operator()(const pair<string,int> &par1, const pair<string,int> &par2){
        bool correcto = false;

        if(par1.second > par2.second)
          correcto = true;

        return correcto;
      }
    };

   /** @brief Functor para convertir un pair<char,int> en un string
    * Necesario para serializar un Nmer.
   */
  class Base2String {
   public:
     string operator()( const pair<char,int> & x) {
       string salida = string(1,x.first) + " " +std::to_string(x.second);
       return salida;
     }
  };

};

#endif
