/** @brief fichero de implementacion de la clase enfermedad

*/
//**********************************************************************************************// 
//**************Jose Manuel Rodríguez Calvo****************************************************//
//********************************************************************************************//
#include "enfermedad.h"


enfermedad::enfermedad(){
  // @todo implementar esta funcion
	name= "";
	ID= "" ;
	database= "";
}

enfermedad::enfermedad(const string & name, const string & ID, const string & database){
 // @todo implementar esta funcion
	this->name=name;
	this->ID=ID;
	this->database=database;
}

// @todo implementar el resto de métodos especificados en enfermedad.h

 void enfermedad:: setName(const string & name){
	this->name=name;
}
 void enfermedad:: setID(const string & ID){
	this->ID= ID;
}
 void enfermedad:: setDatabase(const string & database){
	this->database=database;
}

 string enfermedad:: getName( ) const{
	return name;
}
 string enfermedad:: getID( ) const{
	return ID;
}
 string enfermedad:: getDatabase( ) const{
	return database;
}

 enfermedad & enfermedad:: operator=(const enfermedad & e){
	if ( this != &e){
	 this->name =e.name;
         this->ID=e.ID;
         this->database=e.database;
	}

 	return (*this) ;
}

 string enfermedad:: toString() const{

     string s1=name +"	"+ID +"	" +database;

    return s1;
}

// Operadores relacionales
 bool enfermedad:: operator==(const enfermedad & e) const{

	return (this->ID==e.ID)? true:false;

}

 bool enfermedad:: operator!=(const enfermedad & e) const{

	return (this->ID == e.ID)? false:true;

}
 bool enfermedad:: operator<(const enfermedad & e) const{	//Orden alfabético por campo name.

	return ((this->name< e.name)?true:false);

}

 bool enfermedad:: operator>(const enfermedad & e) const{

	return ((this->name> e.name)?true:false);

}
 bool enfermedad:: nameContains(const string & str) const{

 	//return  ((this->name.find(str)<0)? false:true);

	if(this->name.find(str)==string::npos){

		return false;

	}else{

		return true;

	}

}

 ostream& operator<< ( ostream& os, const enfermedad & e){
   // @todo implementa esta funcion

	 os<<e.toString();

   return os;
   // os << e.getName() ;
   //...
 }
