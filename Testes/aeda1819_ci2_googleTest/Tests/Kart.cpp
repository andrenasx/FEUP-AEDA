#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}
 
//Exercicio 1 a)    DONE

bool CKart::operator<(CKart &c) {
    return numero<c.getNumero();
}

vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> vord;
	for(int i=0;i<pistasG.size();i++){
	    for(int j=0; j<pistasG.at(i).getFrotaActual().size();j++){
	            vord.push_back(pistasG.at(i).getFrotaActual().at(j));
	    }
	}
	sort(vord.begin(),vord.end());
	return vord;
    
}

//Exercicio 1 b)    DONE
int CGrupo::numAvariados(int cilind)
{
    int total = 0;
    for(int i=0;i<pistasG.size();i++){
        CPista pista = pistasG.at(i);
        for(int j=0;j<pista.getKartsAvariados().size();j++){
            if(pista.getKartsAvariados().at(j).getCilindrada()==cilind)
                total+=1;
        }
    }
    return total;
}

//Exercicio 1 c)    DONE
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    //vector <CKart> c;
    for(auto it=frotaKartsPista.begin();it!=frotaKartsPista.end();it++){
        if((*it).getCilindrada()==cilind && !(*it).getAvariado())
            //c.push_back(*it);
            kartsLinhaPartida.push(*it);
    }
    return kartsLinhaPartida.size() >= numeroKarts;

    /*for(int i=0;i<numeroKarts;i++){
        try{
            kartsLinhaPartida.push(c.at(i));
        }
        catch(out_of_range){
            return false;
        }
    }
    return true;*/
}

//Exercicio 1 d)    DONE
int CPista::inicioCorrida()
{
    int size = kartsLinhaPartida.size();
    for(int i=0;i<size;i++){
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    return kartsEmProva.size();
}

