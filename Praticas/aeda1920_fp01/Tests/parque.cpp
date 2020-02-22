#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot) , numMaximoClientes(nMaxCli){
    vagas=lotacao;
    clientes={};
}

unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const{
    for (int i=0;i<clientes.size();i++) {
        if (nome == clientes[i].nome)
            return i;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome){
    if (numMaximoClientes==clientes.size())
        return false;

    if (posicaoCliente(nome)!=-1)
        return false;

    InfoCartao novo_cliente;
    novo_cliente.nome=nome;
    novo_cliente.presente= false;
    clientes.push_back(novo_cliente);

    return true;
}

bool ParqueEstacionamento::entrar(const string & nome){
    if(posicaoCliente(nome)==-1 || clientes[posicaoCliente(nome)].presente || vagas==0)
        return false;

    vagas-=1;
    clientes[posicaoCliente((nome))].presente=true;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string &nome){
    if(posicaoCliente(nome)==-1 || clientes[posicaoCliente(nome)].presente)
        return false;

    clientes.erase(clientes.begin()+posicaoCliente(nome));
    return true;
}
bool ParqueEstacionamento::sair(const string & nome){
    if(posicaoCliente(nome)==-1 || !clientes[posicaoCliente(nome)].presente)
        return false;

    vagas++;
    clientes[posicaoCliente(nome)].presente=false;
    //retiraCliente(nome);
    return true;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{
    return lotacao-vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
    return clientes.size();
}