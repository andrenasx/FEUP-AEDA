#include "frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1){
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const{
    return veiculos.size();
}

int Frota::menorAno() const{
    if (veiculos.empty())
        return 0;
    else{
        int menor=veiculos.at(0)->getAno();

        for (int i=1;i<veiculos.size();i++){
            if(veiculos.at(i)->getAno()<menor)
                 menor=veiculos.at(i)->getAno();
        }
        return menor;
    }
}

/*ostream& Frota::operator<<(ostream &o, const Frota &f) {
    auto it=f.veiculos.begin();
    while(it!=f.veiculos.end()) {
        (*it)->info();
        it++;
    }
    return o;
}*/

vector<Veiculo *> Frota::operator()(int anoM) const {
    vector<Veiculo *> v;
    for(int i=0;i<veiculos.size();i++)
    {
        if(veiculos.at(i)->getAno()==anoM)
            v.push_back(veiculos.at(i));
    }
    return v;
}

float Frota::totalImposto() const{
    float total=0;
    for(int i=0;i<veiculos.size();i++){
        total+=veiculos.at(i)->calcImposto();
    }
    return total;
}


