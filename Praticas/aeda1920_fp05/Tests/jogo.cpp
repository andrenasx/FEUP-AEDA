/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

// a implementar DONE
Jogo::Jogo(): criancas()
{
}

// a implementar DONE
Jogo::Jogo(list<Crianca>& lc2): criancas(lc2)
{
}

// a implementar DONE
void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

// a implementar DONE
list<Crianca> Jogo::getCriancasJogo() const
{
    list<Crianca> res = criancas;
    return res;
}

// a implementar
string Jogo::escreve() const
{
    string res;

    for (auto it = criancas.begin(); it!= criancas.end(); it++){
        res += it->escreve() + "\n";
    }

    return res;
}

// a implementar DONE
Crianca& Jogo::perdeJogo(string frase)
{
    Crianca *c1 = new Crianca();
    list<Crianca> hihi = criancas;
    unsigned int num_pal = numPalavras(frase);
    auto it=hihi.begin();
    while(hihi.size()>1){
        for(int i=1;i<num_pal;i++){
            it++;
            if(it==hihi.end()){
                it=hihi.begin();
            }
        }
        it = hihi.erase(it);
        if(it==hihi.end()){
            it=hihi.begin();
        }
    }
    *c1= *hihi.begin();
    return *c1;
}

// a implementar DONE
list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

// a implementar DONE
list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca>res=criancas;

    for(auto it = res.begin();it!=res.end();it++){
        if(it->getIdade()<=id){
            it = res.erase(it);
            it--;
        }
    }
    return res;
}

// a implementar DONE
void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    criancas=l1;
}

// a implementar
bool Jogo::operator==(Jogo& j2)
{
    if(criancas.size()!=j2.criancas.size()){
        return false;
    }

    auto j=j2.criancas.begin();
    for(auto i=criancas.begin();i!=criancas.end();i++){
        if(*i == *j) {
            j++;
        }
        else
            return false;
    }
	return true;
}

// a implementar
list<Crianca> Jogo::baralha() const
{
    list<Crianca> res;
    return res;
}
