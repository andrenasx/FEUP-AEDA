#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;



ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    vector<string> nomes;

    for(int i=0;i<clientes.size();i++) {
        nomes.push_back(clientes.at(i).nome);
    }

    return sequentialSearch(nomes, nome);
}

int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int pos = posicaoCliente(nome);
    if(pos==-1){
        throw ClienteNaoExistente(nome);
    }
    return clientes[pos].frequencia;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}


void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}


void ParqueEstacionamento::ordenaClientesPorNome()
{
    sort(clientes.begin(),clientes.end(),cmpNome);
}


vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    vector<string> nomes;

    ordenaClientesPorFrequencia();

    for(int i=0;i<clientes.size();i++){
        if(clientes.at(i).frequencia >=n1 && clientes.at(i).frequencia <=n2){
            nomes.push_back(clientes.at(i).nome);
        }
    }

    return nomes;
}


ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    for(int i=0;i<pe.getClientes().size();i++){
        os<<"Nome do Cliente: " << pe.getClientes().at(i).nome << endl;
        os<<"Presente: " << pe.getClientes().at(i).presente << endl;
        os<<"Numero de vezes que utilizou o parque: " << pe.getClientes().at(i).frequencia << endl;
    }
    return os;
}


InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;

    if(p>=clientes.size() || p<0){
        throw PosicaoNaoExistente(p);
    }

    info=clientes.at(p);
    return info;
}


//Excecao ClienteNaoExistente
string ClienteNaoExistente::getNome() {
    return nome;
}
std::ostream & operator<<(std::ostream &out, ClienteNaoExistente &cne){
    out<< "Apanhou excecao. Cliente nao existente: " << cne.getNome() <<endl;
    return out;
}


bool InfoCartao::operator<(const InfoCartao c) {
    if (this->frequencia > c.frequencia){
        return true;
    }
    else if (this->frequencia == c.frequencia && this->nome < c.nome){
        return true;
    }
    else{
        return false;
    }
}

bool cmpNome(const InfoCartao c1, InfoCartao c2) {
    return c1.nome<c2.nome;
}


//Excecao PosicaoNaoExistente
int PosicaoNaoExistente::getValor() {
    return pos;
}
std::ostream & operator<<(std::ostream &out, PosicaoNaoExistente &pne){
    out<< "Apanhou excecao. Posicao nao existente:" << pne.getValor() <<endl;
    return out;
}
