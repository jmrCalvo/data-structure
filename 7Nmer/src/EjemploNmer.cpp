#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <utility>
#include <random>
#include <chrono>
#include <cmath>
#include "ktree.h"
#include "Nmer.h"
#include <stdio.h>
#include <fstream>


using namespace std;
int main(){
 Nmer arbol1,arbol2,arbol3,arbol4,arbol5,arbol6,arbol7,arbol8,arbol9,arbol10;
int tama=30;

ifstream ficha("../datos/1.txt");
if(ficha){
string seq;
getline(ficha,seq);
for(int i=0;i<seq.size();i++){
  seq[i]=toupper(seq[i]);}
arbol1.sequenceADN(tama,seq);}

ifstream fichz("../datos/2.txt");
if(fichz){
string seq;
getline(fichz,seq);
for(int i=0;i<seq.size();i++){seq[i]=toupper(seq[i]);}
arbol2.sequenceADN(tama,seq);}

ifstream fichb("../datos/3.txt");
if(fichb){
string seq;
getline(fichb,seq);for(int i=0;i<seq.size();i++){seq[i]=toupper(seq[i]);}
arbol3.sequenceADN(tama,seq);}

ifstream fichc("../datos/4.txt");
if(fichc){
string seq;
getline(fichc,seq);for(int i=0;i<seq.size();i++){seq[i]=toupper(seq[i]);}
arbol4.sequenceADN(tama,seq);}

ifstream fichd("../datos/5.txt");
if(fichd){
string seq;
getline(fichd,seq);for(int i=0;i<seq.size();i++){seq[i]=toupper(seq[i]);}

arbol5.sequenceADN(tama,seq);
}

ifstream fiche("../datos/6.txt");
if(fiche){
string seq;
getline(fiche,seq);for(int i=0;i<seq.size();i++){seq[i]=toupper(seq[i]);}
arbol6.sequenceADN(tama,seq);}

ifstream fichf("../datos/7.txt");
if(fichf){
string seq;
getline(fichf,seq);for(int i=0;i<seq.size();i++){seq[i]=toupper(seq[i]);}

arbol7.sequenceADN(tama,seq);
}
ifstream fichg("../datos/8.txt");
if(fichg){
string seq;
getline(fichg,seq);for(int i=0;i<seq.size();i++){seq[i]=toupper(seq[i]);}
arbol8.sequenceADN(tama,seq);}

ifstream fichh("../datos/9.txt");
if(fichh){
string seq;
getline(fichh,seq);for(int i=0;i<seq.size();i++){seq[i]=toupper(seq[i]);}
arbol9.sequenceADN(tama,seq);}

ifstream fichi("../datos/10.txt");
if(fichi){
string seq;
getline(fichi,seq);for(int i=0;i<seq.size();i++){seq[i]=toupper(seq[i]);}
arbol10.sequenceADN(tama,seq);}

cout<<"***********************lLIST_NMER**********************************"<<endl;
arbol1.list_Nmer();
cout<<"***********************Prefix**********************************"<<endl;
Nmer sol=arbol2.Prefix("AA");
sol.list_Nmer();
cout<<"***********************Union entre 1 y 2**********************************"<<endl;
Nmer solucion;
solucion=arbol1.Union(arbol2);
solucion.list_Nmer();
cout<<"***************containsString**********************"<<endl;
bool contiene;
string com="GTA";
contiene=arbol1.containsString(com);
if(contiene){cout<<"  esta correcto y contiene gta"<<endl;}
else{cout<<"es incorrecto y no contiene gta"<<endl;}
cout<<"***************include**********************"<<endl;
Nmer mi_arbol;
string mi="GTA";
mi_arbol.sequenceADN(3,mi);
contiene=arbol1.included(mi_arbol);
if(contiene){cout<<"esta bien"<<endl;}
else{cout<<"esta mal"<<endl;}
cout<<"************************Distance***********************************"<<endl;
      cout << "la distancia entre " << 1 << " y "<<2 <<" es de "<< arbol1.Distance(arbol2)<<endl;
       cout << "la distancia entre " << 2 << " y "<<3 <<" es de "<< arbol2.Distance(arbol3)<<endl;
       cout << "la distancia entre " << 3 << " y "<<4 <<" es de "<<arbol3.Distance(arbol4)<<endl;
      cout << "la distancia entre " << 4 << " y "<<5 <<" es de "<< arbol4.Distance(arbol5)<<endl;
       cout << "la distancia entre " << 5 << " y "<<6 <<" es de "<< arbol5.Distance(arbol6)<<endl;
      cout << "la distancia entre " << 6 << " y "<<7 <<" es de "<< arbol6.Distance(arbol7)<<endl;
       cout << "la distancia entre " << 7 << " y "<<8 <<" es de "<< arbol7.Distance(arbol8)<<endl;
      cout << "la distancia entre " << 8 << " y "<<9 <<" es de "<< arbol8.Distance(arbol9)<<endl;
      cout << "la distancia entre " << 9 << " y "<<10 <<" es de "<< arbol9.Distance(arbol10)<<endl;

cout<<"************************rareNmer***********************************"<<endl;
for(auto mit=arbol1.rareNmer(2).begin();mit!=arbol1.rareNmer(2).end();++mit){

  cout<<"la cadena es "<< (*mit).first<<" y la frecuencia  "<<(*mit).second<<endl;

}
cout<<"esta correcto"<<endl;
cout<<"************************commonNmer***********************************"<<endl;
for(auto mit=arbol1.commonNmer(20).begin();mit!=arbol1.commonNmer(20).end();++mit){

  cout<<"la cadena es "<< (*mit).first<<" y la frecuencia  "<<(*mit).second<<endl;

}
cout<<"esta correcto"<<endl;
cout<<"************************level***********************************"<<endl;
for(auto mit=arbol1.level(10).begin();mit!=arbol1.level(10).end();++mit){

cout<<"la cadena es "<< (*mit).first<<" y la frecuencia  "<<(*mit).second<<endl;

}
cout<<"esta correcto"<<endl;
return 0;
}
