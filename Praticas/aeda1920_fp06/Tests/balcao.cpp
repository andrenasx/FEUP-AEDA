#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

//a alterar DONE
Cliente::Cliente() {
    numPresentes = (rand() % 5) +1;
}

//a alterar DONE
int Cliente::getNumPresentes() const {
    return numPresentes;
}

//a alterar DONE
Balcao::Balcao(int te): tempo_embrulho(te) {
    tempo_atual=0;
    prox_chegada= (rand() % 20) +1;
    prox_saida=0;
    clientes_atendidos=0;
}

//a alterar
void Balcao:: proximoEvento()
{
    if(clientes.empty() || prox_chegada<prox_saida){
        tempo_atual=prox_chegada;
        chegada();
    }
    else{
        tempo_atual=prox_saida;
        saida();
    }
}

//a alterar DONE
void Balcao::chegada()
{
    Cliente c1;
    if(clientes.empty())
        prox_saida = tempo_atual+c1.getNumPresentes()*tempo_embrulho;
    clientes.push(c1);
    prox_chegada = (rand() % 20) +1;
    cout<<"tempo= "<<tempo_atual<<"\nchegou novo cliente com: "<<c1.getNumPresentes()<<" presentes"<<endl;
}

//a alterar DONE
void Balcao::saida()
{
    Cliente c1 = getProxCliente();
    clientes.pop();
    clientes_atendidos++;
    prox_saida = tempo_atual+c1.getNumPresentes()*tempo_embrulho;
    cout<<"tempo= "<<tempo_atual<<"\nsaiu cliente com: "<<c1.getNumPresentes()<<" presentes"<<endl;
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

//a alterar
ostream & operator << (ostream & out, const Balcao & b1)
{
    out<<"Clientes atendidos: "<<b1.clientes_atendidos<<", Clientes em espera: "<<b1.clientes.size();
     return out;
}

//a alterar DONE
int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

//a alterar DONE
int Balcao::getProxSaida() const { return prox_saida; }

//a alterar DONE
int Balcao::getClientesAtendidos() const { return clientes_atendidos; }

//a alterar DONE
Cliente & Balcao::getProxCliente() {
    if(clientes.empty())
        throw FilaVazia();
    return clientes.front();
}

      
