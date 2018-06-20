
#include "clinvar.h"
//**********************************************************************************************//
//**************Jose Manuel Rodríguez Calvo****************************************************//
//********************************************************************************************//

//***********************functor***********************************
bool ProbMutacion::operator()(const mutacion &a,const mutacion &b){
double valor1,valor2;
  if(a.getCaf().empty()){valor1=1.0;}
  else{valor1=a.getCaf()[0];}

  if(b.getCaf().empty()){valor2=1.0;}
  else{valor2=b.getCaf()[0];}

if(valor1==valor2){return a.getID()>b.getID();}
else{return (1.0-valor1>1.0-valor2);}
}
//______________________________________________________________//
//******************la clase iterator****************************
clinvar::iterator::iterator(){}
clinvar::iterator::iterator(const set<mutacion>::iterator &x){
  it=x;
}

mutacion clinvar::iterator::operator*(){
return (*it);
}
void clinvar::iterator::operator=(const set<mutacion>::iterator &x){
it=x;
}

bool clinvar::iterator::operator!=(const iterator &x){
return (x.it!=it);
}
clinvar::iterator clinvar::iterator::operator++(){
++it;
return(*this);
}
//_________________________________________________________________//
//***************la clase gen_iterator****************************//

clinvar::gen_iterator::gen_iterator(){
}

clinvar::gen_iterator clinvar::gen_iterator::operator++(){
if(it_map!=ptrclinvar->gen_map.end()){
  if(itlist==(*it_map).second.end()){
    ++it_map;
    itlist=(*it_map).second.begin();
    }
    else{
      ++itlist;
    }
}
return(*this);
}

mutacion clinvar::gen_iterator::operator*(){
  return(**itlist);
}
//___________________________________________________________________________//
//*****************la clase clinvar*****************************************//
clinvar::iterator clinvar::begin(){
//iterator it=
 return mutDB.begin();
}

clinvar::iterator clinvar::end(){
//iterator it=
return mutDB.end();
}

clinvar::iterator clinvar::lower_bound(string cromosoma,int posicion){
iterator solucion=mutDB.end();
bool pare=false;
mutacion m;
m.setPos(posicion);
m.setChr(cromosoma);
for(iterator it=mutDB.begin();it!=mutDB.end() &&!pare;++it){
  if(m==*it){
    pare=true;
    solucion=it;
  }
}

return solucion;
}

clinvar::iterator clinvar::upper_bound(string cromosoma,int posicion){
bool pare=false;
  iterator solucion=mutDB.end();
  mutacion m;
  m.setPos(posicion);
  m.setChr(cromosoma);
for(iterator it=mutDB.begin();it!=mutDB.end() &&!pare;++it){
  if(m==*it ||m>*it){
    pare=true;
    solucion=it;
  }

  return solucion;
}
}

clinvar::enfermedad_iterator clinvar::ebegin(){
enfermedad_iterator e_it;
e_it=EnfDB.begin();
return e_it;
}

clinvar::enfermedad_iterator clinvar::eend(){
enfermedad_iterator e_it;
e_it=EnfDB.end();
return e_it;
}

clinvar::gen_iterator clinvar::gbegin(){
gen_iterator g_it;
g_it.ptrclinvar=this;
g_it.it_map=g_it.ptrclinvar->gen_map.begin();
g_it.itlist=(*g_it.it_map).second.begin();
return (g_it);
}

clinvar::gen_iterator clinvar::gend(){
gen_iterator g_it;
g_it.ptrclinvar=this;
g_it.it_map=g_it.ptrclinvar->gen_map.end();
return (g_it);
}


clinvar::clinvar(){
  cout<< "se ha creado un clinvar"<<endl;
}

void clinvar::load(string nombreDB){
  ifstream fe;
  string cadena;

  cout << "Abrimos "<< nombreDB<< endl;
  fe.open(nombreDB.c_str(), ifstream::in);
  if (fe.fail()){
    cerr << "Error al abrir el fichero /datos/" << nombreDB << endl;
  }
  else {
     do{
       getline(fe,cadena,'\n');
     }while (cadena.find('#')!=string::npos && !fe.eof());

     while ( !fe.eof() ){
         mutacion mut = mutacion(cadena);
         insert(mut);

         getline(fe,cadena,'\n');
       }}
     fe.close();



}

void clinvar::insert(const mutacion &x){

  set<mutacion>::iterator it;
 pair<set<mutacion>::iterator,bool> ret;


ret=mutDB.insert(x);//inserta en mutdb si es repetido pone ret.second a false y no hace lo siguiente
if (ret.second){
  it = ret.first;



//es que lo ha inertado y entonces es diferente
  IDm_map.insert(pair<IDmut,set<mutacion>::iterator> (x.getID(),it));
//************//
  for(int i=0;i<(*it).getGenes().size() && !(*it).getGenes().empty();++i){
      gen_map[(*it).getGenes()[i]].push_back(it);
      }
//*****************//


 vector<enfermedad>::const_iterator vit;

    for(vit=((*it).getEnfermedades().begin());vit!=(*it).getEnfermedades().end() && !(*it).getEnfermedades().empty() && vit->getID() !="";++vit){
          EnfDB.insert(pair<IDenf,enfermedad>(vit->getID(),(*vit)));
          IDenf_map.insert(pair<IDenf,set<mutacion>::iterator> (vit->getID(),it));
    }
  }
}


bool clinvar::erase(IDmut ID){
unordered_map<IDmut,set<mutacion>::iterator>::iterator uit=IDm_map.find(ID);
set<mutacion>::iterator it=(*uit).second;
mutacion mu=(*(*uit).second);
//****borrar IDm_map***************//
IDm_map.erase(uit);

//*********************************//
//****borrar gen_map***************//
vector<IDgen>::const_iterator git;
for(git=mu.getGenes().begin();git!=mu.getGenes().end();++git){
  map<IDgen,list<set<mutacion>::iterator>>::iterator ggit=gen_map.find(*git);
  if((*ggit).second.size()==1){
    gen_map.erase(ggit);
  }
  else{ if((*ggit).second.size()>1){

        list<set<mutacion>::iterator>::iterator lit;
        bool encontrado=false;
        for(lit=(*ggit).second.begin();lit!=(*ggit).second.end() && !encontrado;++lit){
          if(*lit==it){encontrado=true;}
        }
        (*ggit).second.erase(lit);
        }
      }
}
//**********************************//
//****borrar enfermedad*************//
vector<enfermedad>::const_iterator eit;
for(eit=mu.getEnfermedades().begin();eit!=mu.getEnfermedades().end();++eit){

if(IDenf_map.count(eit->getID())==1){
  EnfDB.erase(eit->getID());
}

multimap<IDenf,set<mutacion>::iterator>::iterator miit;
miit=IDenf_map.find(eit->getID());
while((*miit).second !=it ){
  ++miit;
}
if((*miit).second==it){
IDenf_map.erase(miit);}

}
//*************************************//
//***borrar de IDmut*******************//
mutDB.erase(it);
//********finaliza********************//
return true;
}


clinvar::iterator clinvar::find_Mut(IDmut ID){
iterator mit(IDm_map[ID]);
return mit;
}

clinvar::enfermedad_iterator clinvar::find_Enf(IDenf ID){
      enfermedad_iterator e_it=EnfDB.find(ID);
      return e_it;
}

vector<enfermedad>getEnfermedades(mutacion &m){
      return m.getEnfermedades();
}

list<IDenf> clinvar::getEnfermedades(const string &keyword){
      list<IDenf> mylist;
      enfermedad_iterator miit;
    for(miit=EnfDB.begin();miit!=EnfDB.end();miit++){
    if((*miit).second.nameContains(keyword))
      mylist.push_back((*miit).first);
    }
  return mylist;
}

set<IDmut> clinvar::getMutacionesEnf(IDenf ID){
  set<IDmut> mymut;
  multimap<IDenf,set<mutacion>::iterator>::iterator e_it;
    for(e_it=IDenf_map.begin();e_it!=IDenf_map.end();e_it++){
    if((*e_it).first==ID)
      mymut.insert((*((*e_it).second)).getID());
  }
  return mymut;
}

set<IDmut> clinvar::getMutacionesGen (IDgen ID){
		set<IDmut> mymut ;
		gen_iterator g_it ;
		g_it.it_map = gen_map.find(ID) ;
		if(g_it.it_map != gen_map.end()){
			for(g_it.itlist = gen_map.find(ID)->second.begin(); g_it.itlist!=gen_map.find(ID)->second.end(); (g_it.itlist) ++){
			mymut.insert((**(g_it.itlist)).getID());
			}
		}

		return mymut ;
	}


set<mutacion,ProbMutacion> clinvar::topKMutaciones(int k,string keyword){
  list<IDenf>::iterator liit;
  set<IDmut>::iterator qit;
  unordered_set<IDmut> uset;

priority_queue<mutacion,vector<mutacion>,ProbMutacion> cola;
list<string>enfm=getEnfermedades(keyword);
int t=0;
  for(liit=enfm.begin();liit!=enfm.end();++liit){
    set<string> m=getMutacionesEnf(*liit);
      for(qit=m.begin();qit!=m.end();qit++){
        if(uset.find(*qit)==uset.end()){
          uset.insert(*qit);
          cola.push(*(IDm_map[*qit]));
          t++;
          if(t>k)cola.pop();
      }
      }
}

  set<mutacion,ProbMutacion> myset;
t=0;
  while(!cola.empty()){
  myset.insert(cola.top());
t++;
  cola.pop();

  }
return myset;
}
