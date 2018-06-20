#include "enfermedad.h"
#include "iostream"
#include"mutacion.h"
#include "clinvar.h"
#include "string"
//**********************************************************************************************//
//**************Jose Manuel Rodríguez Calvo****************************************************//
//********************************************************************************************//
using namespace std;

int main(){
  clinvar c;
  cout<<" paso1: load"<<endl;
  c.load("../datos/clinvar_20160831.vcf");

  cout<<" paso2: find_Mut"<<endl;
  cout <<*c.find_Mut("rs201073369")<<endl;

  cout<<" paso3: find_Enf"<<endl;
  cout << c.find_Enf("CN221808:616126") -> first <<"  "<< c.find_Enf("CN221808:616126") ->second << endl;

  cout << "paso4: getEnfermedades"<< endl;
  list<IDenf> lista = c.getEnfermedades ("defi");
  int i=1;
  for(auto it: lista){cout << " el elemento "<<i<<" es: "<<endl << it << endl;i++;}

  cout << "paso5: getMutacionesEnf"<< endl;
  set<IDmut> myset = c.getMutacionesEnf ("CN196688:615897");
  i=1;
  for(auto it: myset){cout << " el elemento "<<i<<" es: "<<endl << it<< endl;i++;}

  cout << "paso6:  getMutacionesGen"<< endl;
  set<IDmut> miset= c.getMutacionesGen ("ISG15:9636");
   i=1;
  for(auto it: miset){cout << " el elemento"<<i<<" es: "<<endl<< it << endl;i++;};

  cout <<"paso7: begin "<< endl;
  cout << *(c.begin()) << endl;

  cout << " paso8: end "  << endl;
  c.end();cout<<"lo ha hecho"<<endl;

cout<<"paso9: lower_bound(cromosoma,posicion)"<<endl;
string t="10";
cout<<*c.lower_bound(t,94574092)<<endl;

cout<<"paso10: upper_bound(cromosoma,posicion)"<<endl;
cout<<*c.upper_bound(t,94574092)<<endl;

  cout << "paso11: ebegin()"  << endl;
  cout << c.ebegin()->second << endl;

  cout << "paso11: eend()"  << endl;
 c.eend();cout<<"lo ha hecho"<<endl;

  cout << "paso12: gbegin()"  << endl;
  cout << *(c.gbegin()) << endl;

  cout<<"paso13: operator ++gen_iterator()"<<endl<<*(++(c.gbegin()))<<"lo ha hecho"<<endl;


cout<<"paso14: gend()"<<endl;
c.gend();cout<<"lo ha hecho"<<endl;

cout << "paso15:topKMutaciones()"<< endl;
  i=1;
  auto mised = c.topKMutaciones(5, "ganglia");
  for(auto it: mised){cout << " el elemento"<<i<<" es: "<<endl<< it<< endl;}
  cout<<"paso 16: erase()"<<endl;
  bool comprobacion = c.erase("rs201073369");
if(comprobacion){cout<<"ha terminado de borrar"<<endl;}
  return 0 ;


}
