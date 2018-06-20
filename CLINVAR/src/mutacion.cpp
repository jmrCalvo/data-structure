/** @brief fichero de implementacion de la clase mutacion

*/
//**********************************************************************************************//
//**************Jose Manuel Rodríguez Calvo****************************************************//
//********************************************************************************************//
#include "mutacion.h"
  mutacion::mutacion(){
		ID= "  ";
		chr=" ";
		pos= 0;
	}
  mutacion::mutacion(const mutacion& m){

		this->ID=m.ID;
  		this->chr=m.chr;
		this->pos=m.pos;
  		this->ref_alt=m.ref_alt;
		this->genes=m.genes;
		this->common=m.common;
		this->caf=m.caf;
		this->enfermedades=m.enfermedades;
		this->clnsig=m.clnsig;


	}

  mutacion::mutacion(const string & str){   //para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada

		string subcadena_genes,subcadena_caf,subcadena_clnsig,subcadena_nombre, subcadena_id, subcadena_datos, nombre, id, database;
		int contador_barras=0, cuenta_enfermedades=0, pos_inicial_n=0, pos_inicial_id=0, pos_inicial_d=0;
		size_t pos_ini;
		string chr, ID;
	  int pos;

  	stringstream aux;
	  aux.str(str);
	  aux>>this->chr;
	  aux>>this->pos;
	  aux>>this->ID;

	  string ref;
	  aux>>ref;
	  this->ref_alt.push_back(ref);
	  string alt;
	  aux>>alt;
	  int mi_pos;

	  int g=alt.size();
	  bool comproba=false;
	  while(g>0){
			int i=0;
			mi_pos=alt.find(","); //devuelve npos en caso de no encontrar el caracter ,
				if(mi_pos<alt.size() && mi_pos >0){comproba=true;}  //en caso de encontrar el caracter ,
					this->ref_alt.push_back(alt.substr(i,mi_pos));
					alt=alt.substr(mi_pos+1,alt.size());
					g=alt.size()-1;

				if(mi_pos<0){comproba=true;}	// en cualquier otro caso
					this->ref_alt.push_back(alt.substr(i,alt.size()));
					g=0;

	  }
	  if(comproba)
			this->ref_alt.push_back(alt.substr(0,alt.size()));


		subcadena_genes=subcadena(str, "GENEINFO=", ";");


		if(subcadena_genes.find("|")== -1){
			this->genes.push_back(subcadena_genes);
		}
		else{
			this->genes.push_back(subcadena_genes.substr(0,subcadena_genes.find("|")-1));
			this->genes.push_back(subcadena_genes.substr(subcadena_genes.find("|")+1,subcadena_genes.size()));
		}

		this->common=stoi(subcadena(str, "COMMON=", ";"));

		subcadena_caf= subcadena(str, "CAF=", ";");

		caf.push_back(atof(subcadena_caf.substr(0,subcadena_caf.find(",")-1).c_str()));
		caf.push_back(atof(subcadena_caf.substr(subcadena_caf.find(",")+1,subcadena_caf.size()).c_str()));


		subcadena_clnsig= subcadena(str, "CLNSIG=", ";");

			for(int i=0; i< subcadena_clnsig.size();i++){
				if(subcadena_clnsig[i]=='|')
	 				contador_barras++;
			}

			cuenta_enfermedades = contador_barras + 1;

			subcadena_nombre= subcadena(str, "CLNDBN=", ";");
			transform(subcadena_nombre.begin(),subcadena_nombre.end(),subcadena_nombre.begin(),::tolower);
			subcadena_id= subcadena(str, "CLNDSDBID=", ";");
			subcadena_datos= subcadena(str, "CLNDSDB=", ";");


		for(int i=0; i< cuenta_enfermedades;i++){
		 	this->clnsig.push_back(stoi(subcadena_clnsig.substr(pos_inicial_n,(subcadena_clnsig.find("|",pos_inicial_n)-pos_inicial_n))));
			pos_inicial_n= subcadena_clnsig.find("|",pos_inicial_n) + 1;
		}

		for(int i=0; i< cuenta_enfermedades;i++){
			nombre = subcadena_nombre.substr(pos_inicial_n,(subcadena_nombre.find("|",pos_inicial_n)-pos_inicial_n));
		  id = subcadena_id.substr(pos_inicial_id,(subcadena_id.find("|",pos_inicial_id)-pos_inicial_id));
		  database = subcadena_datos.substr(pos_inicial_d,(subcadena_datos.find("|",pos_inicial_d)-pos_inicial_d));
			pos_inicial_n= subcadena_nombre.find("|",pos_inicial_n) + 1;
		  pos_inicial_id= subcadena_id.find("|",pos_inicial_id) + 1;
		  pos_inicial_d= subcadena_datos.find("|",pos_inicial_d) + 1;

			enfermedad ed(nombre, id, database);

			enfermedades.push_back(ed);

		}


	}
		void mutacion:: setID(const string & id){
			this->ID=id;
		}
		void mutacion:: setChr(const string & chr){
			this->chr=chr;
		}
		void mutacion:: setPos(const unsigned int & pos){
			this->pos=pos;
		}
		void mutacion:: setRef_alt(const vector<string> & ref_alt){
			this->ref_alt=ref_alt;
		}
		void mutacion:: setGenes (const vector<string> & genes){
			this->genes=genes;
		}
		void mutacion:: setCommon (const bool & common){
			this->common=common;
		}
		void mutacion:: setCaf (const vector<float> & caf){
			this->caf=caf;
		}
		void mutacion:: setEnfermedades (const vector<enfermedad> & enfermedades){
			this->enfermedades=enfermedades;
		}
		void mutacion:: setClnsig (const vector<int> & clnsig){
			this->clnsig=clnsig;
		}
		string mutacion:: getID( ) const{
			return ID;
		}
		string mutacion:: getChr( ) const{
			return chr;
		}
		unsigned int mutacion:: getPos( ) const{
			return pos;
		}
		const vector<string> & mutacion:: getRef_alt () const{
			return ref_alt;
		}
		const vector<string> & mutacion:: getGenes () const{
			return genes;
		}
		bool mutacion:: getCommon () const{
			return common;
		}
		const vector<float> & mutacion:: getCaf () const{
			return caf;
		}
		const vector<enfermedad> & mutacion:: getEnfermedades () const{
			return enfermedades;
		}
		const vector<int> & mutacion:: getClnsig () const{
			return clnsig;
		}

  string mutacion:: subcadena (const string  inicial, string  buscado, string  del){
		size_t pos_ini, pos_fin;
		int found,found2, longitud;
		string resultado;
		string mal= "-1";


	 	found = inicial.find(buscado);

			if(found<0){
				return mal;
			}

		pos_ini = found + buscado.size();


		found2=inicial.find(del,pos_ini);
		pos_fin=found2;

		longitud= pos_fin - pos_ini;

		resultado=inicial.substr(pos_ini,longitud);

		return resultado;

	}

  const vector<string> mutacion:: subcadena_ref(string inicial, string  buscado, int pos){
	int x;
	int longitud;
	size_t delimiter= inicial.find_first_of("	", pos);
	vector<string> resultado;

	longitud= delimiter-pos;
	resultado.push_back(inicial.substr(pos,longitud));

 	do{
		 x =inicial.find_first_of("	,", delimiter+1);
		 resultado.push_back(inicial.substr(delimiter+1, (x-delimiter)-1));
		delimiter+= (x-delimiter);
	 }while (inicial[x]!='	');

	return resultado;
	}

  mutacion & mutacion:: operator=(const mutacion & m){

		if ( this != &m){

			this->ID=m.ID;
  			this->chr=m.chr;
			this->pos=m.pos;
  			this->ref_alt=m.ref_alt;
			this->genes=m.genes;
			this->common=m.common;
			this->caf=m.caf;
			this->enfermedades=m.enfermedades;
			this->clnsig=m.clnsig;
		}

	 	return (*this) ;

	}

  bool mutacion:: operator==(const mutacion & m) const{
		if (chr==(m.getChr()) && (pos == m.getPos())){
      return  true;}
    else{
      return false;}

	}

  bool mutacion:: operator<(const mutacion & m) const{      //El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posición, de menor posición a mayor (orden natural de enteros).
	 int chr_aux=0, mchr_aux=0 ;

  if(chr == "X"){
  	chr_aux = 23;
	}

  if(chr == "Y"){
 	 chr_aux = 24;
	}

  if(chr == "MT"){
 	 chr_aux = 25;
	}

  if(m.chr == "X"){
  	mchr_aux = 23;
	}

  if(m.chr == "Y"){
  	mchr_aux= 24;
	}

  if(m.chr == "MT"){
  	mchr_aux= 25;
	}

 if(chr_aux == 0 ){
	chr_aux = atoi(chr.c_str());
 }

 if(mchr_aux ==0 ){
	mchr_aux = atoi(m.chr.c_str());
 }

 if(chr_aux<mchr_aux) return true;

 if(chr_aux==mchr_aux && pos < m.pos)return true;

 else return false;

}
  bool mutacion:: operator>(const mutacion & m) const{

	 int chr_aux=0, mchr_aux=0 ;

  if(chr == "X"){
  	chr_aux = 23;
	}

  if(chr == "Y"){
 	 chr_aux = 24;
	}

  if(chr == "MT"){
 	 chr_aux = 25;
	}

  if(m.chr == "X"){
  	mchr_aux = 23;
	}

  if(m.chr == "Y"){
  	mchr_aux= 24;
	}

  if(m.chr == "MT"){
  	mchr_aux= 25;
	}

 if(chr_aux == 0 ){
	chr_aux = atoi(chr.c_str());
 }

 if(mchr_aux ==0 ){
	mchr_aux = atoi(m.chr.c_str());
 }

 if(chr_aux>mchr_aux) return true;

 if(chr_aux==mchr_aux && pos > m.pos)return true;

 else return false;

  }


  ostream& operator<< ( ostream& os, const mutacion& m ){  //Imprimir TODOS los campos del objeto mutación.

  os<<"Cromosoma:"<<m.getChr()<<endl;
  os<<"Posición:"<<m.getPos()<<endl;
  os<<"ID:"<<m.getID()<<endl;

  vector<string> ref_alt =m.getRef_alt();
		os<<"Referencia: "<< ref_alt[0]<<endl;
  	os<<"Alternativa: "<< ref_alt[1]<<endl;


 vector<string> genes =m.getGenes();
		for(int i = 0 ;i<genes.size();i++){
		 os <<"Genes "<< i<<":"<< genes[i]<< endl;
	}

  vector<float> caf =m.getCaf();
		 for(int i = 0 ;i<caf.size();i++){
		 os<<"caf "<< i<<":"<< caf[i]<< endl;
	}

  os<< "Common :" << m.getCommon()<< endl;

  vector<enfermedad> enfermed =m.getEnfermedades();
		for(int i = 0 ;i<enfermed.size();i++){
		 os <<"Enfermedad "<< i<<":"<< enfermed[i].toString()<< endl;
	}

  vector<int > clnsig =m.getClnsig();
	for(int i = 0 ;i<clnsig.size();i++){
 		os <<"clnsig "<< i<<":"<< clnsig[i]<< endl;
	}

		return os;
}
