#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const
{
    return numeros.find(num) != numeros.end();
}

//a alterar DONE
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
     int counter=0;
     for(int i=0;i<valores.size();i++){
         if(numeros.find(valores.at(i)) == numeros.end()){
             numeros.insert(valores.at(i));
             counter++;
         }
         if(counter==n)
             break;
     }
    /*unordered_set<unsigned> naoRepetidos;
    for(int i=0;i<valores.size();i++){
        naoRepetidos.insert(valores.at(i));
    }
    int size=n, counter=0;
    if(naoRepetidos.size()<n)
        size=naoRepetidos.size();
    auto it=naoRepetidos.begin();
    while(counter!=size){
        numeros.insert(*it);
        it++;
        counter++;
    }*/
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    unsigned counter =0;
    for(auto it=sorteio.begin();it!=sorteio.end();it++){
        if(numeros.find(*it)!=numeros.end())
            counter++;
    }
    return counter;
}





