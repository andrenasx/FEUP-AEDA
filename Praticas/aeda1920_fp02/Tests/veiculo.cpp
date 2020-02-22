#include "veiculo.h"
#include <iostream>
#include <utility>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a): marca(mc), mes(m), ano(a){}

int Veiculo::getAno() const {
    return ano;
}

string Veiculo::getMarca() const {
    return marca;
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil): Veiculo(mc,m,a), combustivel(c), cilindrada(cil) {}

string Motorizado::getCombustivel() const {
    return combustivel;
}

Automovel::Automovel(string mc, int m, int a, string c, int cil): Motorizado(mc,m,a,c,cil){}

Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm): Motorizado(mc,m,a,c,cil), carga_maxima(cm) {}

Bicicleta::Bicicleta(string mc, int m, int a, string t): Veiculo(mc,m,a), tipo(t) {}

int Veiculo::info() const {
    cout<<"Marca do veiculo: "<<marca<<endl;
    cout<<"Mes do veiculo: "<<mes<<endl;
    cout<<"Ano do veiculo: "<<ano<<endl;
    return 3;
}

int Motorizado::info() const {
    int n=Veiculo::info();
    cout<<"Combustivel: "<<combustivel<<endl;
    cout<<"Cilindrada: "<<cilindrada<<endl;
    return 2+n;
}

int Automovel::info() const {
    int n=Motorizado::info();
    return n;
}

int Camiao::info() const {
    int n=Motorizado::info();
    cout<<"Carga maxima do camiao: "<<carga_maxima<<endl;
    return 1+n;
}

int Bicicleta::info() const {
    int n= Veiculo::info();
    cout<<"Tipo da bicicleta: "<<tipo<<endl;
    return 1+n;
}

bool Veiculo::operator<(const Veiculo &v) const {
    if(ano == v.ano)
        return mes<v.mes;
    return ano<v.ano;
}

float Veiculo::calcImposto() const {
    return 0;
}

float Motorizado::calcImposto() const{
    if((combustivel == "gasolina" && cilindrada<=1000) || (combustivel != "gasolina" && cilindrada <=1500)) {
        if (ano > 1995)
            return 14.56;
        else
            return 8.10;
    }
    else if ((combustivel == "gasolina" && cilindrada>1000 && cilindrada<=1300) || (combustivel != "gasolina" && cilindrada > 1500 && cilindrada<=2000)) {
        if (ano > 1995)
            return 29.06;
        else
            return 14.56;
    }
    else if ((combustivel == "gasolina" && cilindrada>1300 && cilindrada<=1750) || (combustivel != "gasolina" && cilindrada > 2000 && cilindrada<=3000)) {
        if (ano > 1995)
            return 45.15;
        else
            return 22.65;
    }
    else if ((combustivel == "gasolina" && cilindrada>1750 && cilindrada<=2600) || (combustivel != "gasolina" && cilindrada > 3000)) {
        if (ano > 1995)
            return 113.98;
        else
            return 54.89;
    }
    else if (combustivel == "gasolina" && cilindrada>2600 && cilindrada<=3500) {
        if (ano > 1995)
            return 181.17;
        else
            return 87.13;
    }
    else if (combustivel == "gasolina" && cilindrada>3500) {
        if (ano > 1995)
            return 320.89;
        else
            return 148.37;
    }
    return Veiculo::calcImposto();
}

float Bicicleta::calcImposto() const {
    return Veiculo::calcImposto();
}

