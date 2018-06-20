	#include "Nmer.h"
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;
//sobrecarga de operadores
bool operator<(const pair<string,int> &p1,const pair<string,int> &p2){
	return p1.second<p2.second;
}
bool operator>(const pair<string,int> &p1,const pair<string,int> &p2){
	return p1.second>p2.second;
}

 int Nmer::elemento(char caracter)const{
    if(caracter=='A') return 0;
    else if(caracter=='G') return 1;
    else if(caracter=='C') return 2;
    else if (caracter=='T')return 3;
  }

string Nmer::obtenerNmer(ktree<pair<char,int>,4>::const_node n)const{
	string cadena;
	if(((*n).second)==0){
		cadena="";}
	else{
	  while(!n.parent().null()){
	    cadena.push_back((*n).first);
	  	n=n.parent();
	  }
	reverse(cadena.begin(),cadena.end());
	return cadena;
	}
}

  void Nmer::insert_adn (ktree<pair<char,int>,4>::node n, const string & adn){
    ktree<pair<char,int>,4>::node hijo;
    if(adn.size()!=0){
      int pos=elemento(adn[0]);
      hijo=n.k_child(pos);
      if(hijo.null()){
				pair<char,int> t(adn[0],0);
        el_Nmer.insert_k_child(n,pos,t);
        hijo=n.k_child(pos);
    	}
    (*hijo).second++;
		string mi_adn=adn.substr(1,adn.size());
		insert_adn(hijo,mi_adn);
	  }
}
void  Nmer::recorrido_preorden(ktree<pair<char,int>,4>::const_node n)const{
if (!n.null()){

cout<<"la rama es: "<<obtenerNmer(n)<<" y su frecuecnia "<<(*n).second<<endl;
ktree<pair<char,int>,4>::const_node::child_iterator ini = n.begin();
ktree<pair<char,int>,4>::const_node::child_iterator fin = n.end();
  while (ini!=fin){
     recorrido_preorden(*ini);
     ++ini;
   }
 }
}

void Nmer::insertarTodos(ktree<pair<char,int>,4>::node n, Nmer &nmer){
	if(!n.null()){
				string cadena=obtenerNmer(n);
				if(cadena.size() == max_long) {
						insert_adn(nmer.el_Nmer.root(),cadena);
				}

				ktree<pair<char,int>,4>::node::child_iterator inicio = n.begin();
				ktree<pair<char,int>,4>::node::child_iterator final = n.end();
				while(inicio!=final){
				insertarTodos(*inicio,nmer);
				++inicio;
				}
	}
					}

bool Nmer::contenido(ktree<pair<char,int>,4>::const_node n1,ktree<pair<char,int>,4>::const_node n2)const{
	bool resultado=true;
		if(!n1.null()){
			if(n2.null()){
				resultado=false;}
			else{
				for(int i=0;i<4 && resultado;i++){
										resultado=contenido(n1.k_child(i),n2.k_child(i));
				}
			}
		}
	return resultado;
}

void Nmer::ranking(	ktree<pair<char,int>,4>::const_node n_act,set<pair<string,int>,ordenDecre> &myset)
{
if(!n_act.null()){
string rama=obtenerNmer(n_act);
pair<string,int> t(rama,(*n_act).second);
myset.insert(t);
for(auto aux: n_act){
	ranking(aux,myset);
}
}

}
template <typename S, typename CMP>
  void Nmer::cmpNmer(ktree<pair<char,int>,4>::node n, int threshold, S &s){
    if(!n.null()){
      CMP cmp;
      pair <string, int> p1( string(1, (*n).first), (*n).second), p2(string(1,(*n).first), threshold);
      if(cmp(p1,p2)){
        string adn = obtenerNmer(n);
        s.insert(make_pair(adn, (*n).second));

        }
				for(auto it = n.begin();it != n.end();it++){
          cmpNmer<S, CMP>(*it, threshold, s);
      }
    }
  }
	void Nmer::equalnmer(ktree<pair<char,int>,4>::const_node n, set<pair<string,int>, Nmer::ordenCrec > & s, int l, int lactual){
			if(!n.null()){
				if(l == lactual) {
					string adn = obtenerNmer(n);
					s.insert(make_pair(adn, (*n).second));
				}
				else if(l > lactual) {
					for(auto it = n.begin();it != n.end();it++){
						equalnmer(*it, s, l, lactual+1);
					}
				}
			}
		}

//*************************************************************************************************
//Metodos publicos
Nmer::Nmer() {
  max_long = 0;
  el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
}

Nmer::Nmer(const Nmer & a){
	this->el_Nmer=a.el_Nmer;
	this->max_long=a.max_long;
}

void Nmer::list_Nmer() const {
    recorrido_preorden(el_Nmer.root());
}

unsigned int Nmer::length() const {
   return max_long;
}

Nmer::size_type Nmer::size() const{
  return el_Nmer.size()-1;
}

Nmer & Nmer::operator=(const Nmer & a){
if(this != &a)
{
	this->el_Nmer=a.el_Nmer;
	this->max_long=a.max_long;
}
return *this;
}

Nmer Nmer::Prefix(string adn){
Nmer mi_arbol;
int pos=0;
ktree<pair<char,int>,4>::node mi_nodo=el_Nmer.root();
while(pos<adn.size()){
	mi_nodo=mi_nodo.k_child(elemento(adn[pos]));
	pos++;
}
(mi_arbol.el_Nmer).assing(el_Nmer,mi_nodo);
mi_arbol.max_long=max_long-(adn.size());
(*(mi_arbol.el_Nmer.root())).second=0;

return mi_arbol;
}


Nmer Nmer::Union(const Nmer reference){
	Nmer resultado(reference);
	insertarTodos(el_Nmer.root(),resultado);
	resultado.max_long=max(resultado.max_long,max_long);
	return resultado;
}

bool Nmer::containsString(const string adn) const{
bool esta=true;
int pos=0;
ktree<pair<char,int>,4>::const_node mi_nodo=el_Nmer.root();
while(pos<adn.size() && !mi_nodo.null() && esta ){
	mi_nodo=mi_nodo.k_child(elemento(adn[pos]));
	esta=(mi_nodo.null()==false && adn[pos]==(*mi_nodo).first);
	pos++;
	}
	return esta;
}

bool Nmer::included(const Nmer reference) const{
bool result=contenido(el_Nmer.root(),reference.el_Nmer.root());
return !result;
}

void Nmer::sequenceADN(unsigned int tama, const string & adn){//subsecuencias de la longitud
  string mi_adn;
	max_long=tama;
  for(int i= 0; i<=adn.size()-tama;i++){
    mi_adn=adn.substr(i, tama);
    insert_adn(el_Nmer.root(),mi_adn);
  }
}

bool Nmer::loadSerialized(const string & fichero) {
 string cadena;
 ifstream fe;
 pair<char,int> nulo('x',-1);
 Nmer::String2Base stb;

 fe.open(fichero.c_str(), ifstream::in);
 if (fe.fail()){
    cerr << "Error al abrir el fichero " << fichero << endl;
 }
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{
      getline(fe,cadena,'\n');
    } while (cadena.find("#")==0 && !fe.eof());
    // leemos Nmer_length
     max_long = cadena.size();
     // leemos cadena serializada
    getline(fe,cadena,'\n');
    el_Nmer.deserialize(cadena,nulo,';',stb);
    fe.close();

    return true;
 } // else
 fe.close();
 return false;
}

float Nmer::Distance(const Nmer & x){
	float distancia=0.0;
	ktree<pair<char,int>,4>::const_node n_X=el_Nmer.root();
	ktree<pair<char,int>,4>::const_node n_Y=x.el_Nmer.root();
	map <string,int> mapX,mapY;
	map<string,int>::iterator it;
int posX,posY,valor,xi=0,yj=0 ;
set<pair<string,int>,ordenDecre> setX,setY;

ranking(n_X,setX);
ranking(n_Y,setY);

for(auto x:setX){
	mapX.insert(pair<string,int>(x.first,xi));
	xi++;
}
for(auto y:setY){
	mapY.insert(pair<string,int>(y.first,yj));
	yj++;
}

for(map <string,int>::iterator lit=mapX.begin();lit!=mapX.end();++lit){
	valor=1;
	if((it=mapY.find((*lit).first))!=mapY.end()){
		posX=(*lit).second;
		posY=((*it).second);
		if(mapX.size()>mapY.size()){
			valor=abs(posX-posY)/mapX.size();
		}
		else{
			valor=abs(posX-posY)/mapY.size();
		}
	}
	distancia+=valor;
}
return distancia/mapX.size();
}

set<pair<string,int>, Nmer::ordenCrec > Nmer::rareNmer(int threshold){
	set<pair<string,int>, Nmer::ordenCrec> s;
   cmpNmer<set<pair<string,int>, Nmer::ordenCrec >, Nmer::ordenRare>(el_Nmer.root(), threshold,s);
   return s;
}

set<pair<string,int>, Nmer::ordenDecre > Nmer::commonNmer(int threshold){
	set<pair<string,int>, Nmer::ordenDecre> s;
   cmpNmer<set<pair<string,int>, Nmer::ordenDecre >, Nmer::ordenCommon>(el_Nmer.root(), threshold,s);
   return s;
}

	set<pair<string,int>, Nmer::ordenCrec > Nmer::level(int l){
		set<pair<string,int>, Nmer::ordenCrec > s;
	  equalnmer(el_Nmer.root(), s, l, 0);
	   return s;
	}
