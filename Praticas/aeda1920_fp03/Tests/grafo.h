#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N> class NoRepetido;
template <class N> class NoInexistente;
template <class N> class ArestaRepetida;
template <class N> class ArestaInexistente;

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo(){
        nos={};
    }
    ~Grafo(){
        for (int i=0; i<nos.size();i++){
            free(nos.at(i));
        }
    }

    Grafo & inserirNo(const N &dados){
        for (int i=0; i<nos.size();i++){
            if(dados==nos.at(i)->info)
                throw NoRepetido<N>(dados);
        }

        No<N,A>* new_no = new No<N,A>(dados);
        nos.push_back(new_no);
        return *this;
    }

    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val){
        int pos_i = -1;
        int pos_f = -1;

        for (int i=0; i<nos.size();i++){
            if(nos.at(i)->info == inicio) {
                pos_i = i;
            }
            if(nos.at(i)->info == fim){
                pos_f = i;
            }
        }

        if(pos_i == -1){
            throw NoInexistente<N>(inicio);
        }
        else if(pos_f == -1){
            throw NoInexistente<N>(fim);
        }

        for(int j=0; j<nos.at(pos_i)->arestas.size();j++){
            if(nos.at(pos_f) == nos.at(pos_i)->arestas.at(j).destino)
                throw ArestaRepetida<N>(inicio,fim);
        }

        Aresta<N,A> new_a = Aresta<N,A>(nos.at(pos_f),val);
        nos.at(pos_i)->arestas.push_back(new_a);

        return *this;
    }

    Grafo & eliminarAresta(const N &inicio, const N &fim){
        int pos_i = -1, pos_f = -1;

        for (int i=0; i<nos.size();i++){
            if(nos.at(i)->info == inicio) {
                pos_i = i;
            }
            if(nos.at(i)->info == fim){
                pos_f = i;
            }
        }

        if(pos_i == -1){
            throw NoInexistente<N>(inicio);
        }
        else if(pos_f == -1){
            throw NoInexistente<N>(fim);
        }

        for(int j=0; j<nos.at(pos_i)->arestas.size();j++){
            if(nos.at(pos_f) == nos.at(pos_i)->arestas.at(j).destino){
                nos.at(pos_i)->arestas.erase(nos.at(pos_i)->arestas.begin() + j);
                return *this;
            }
        }

        throw ArestaInexistente<N>(inicio, fim);
    }

    A & valorAresta(const N &inicio, const N &fim){
        int pos_i = -1 , pos_f = -1;
        A val;

        for (int i=0; i<nos.size();i++){
            if(nos.at(i)->info == inicio) {
                pos_i = i;
            }
            if(nos.at(i)->info == fim){
                pos_f = i;
            }
        }

        if(pos_i == -1){
            throw NoInexistente<N>(inicio);
        }
        else if(pos_f == -1){
            throw NoInexistente<N>(fim);
        }

        for(int j=0; j<nos.at(pos_i)->arestas.size();j++){
            if(nos.at(pos_f) == nos.at(pos_i)->arestas.at(j).destino){
                return nos.at(pos_i)->arestas.at(j).valor;
            }
        }

        throw ArestaInexistente<N>(inicio, fim);
    }

    int numArestas(void) const {
        int count = 0;
        for (int i=0; i<nos.size();i++){
            count+=nos.at(i)->arestas.size();
        }
        return count;
    }

    int numNos(void) const {
        return nos.size();
    }

    void imprimir(std::ostream &os) const{
        for(int i=0;i<nos.size();i++){
            os << "( " << nos.at(i)->info;
            for(int j=0;j<nos.at(i)->arestas.size();j++){
                os << "[ " << nos.at(i)->arestas.at(j).destino->info << " " << nos.at(i)->arestas.at(j).valor << "] ";
            }
            os << ") ";
        }
    }
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g){
    for(int i=0;i<g.nos.size();i++){
        out << "( " << g.nos.at(i)->info;
        for(int j=0;j<g.nos.at(i)->arestas.size();j++){
            out << "[ " << g.nos.at(i)->arestas.at(j).destino->info << " " << g.nos.at(i)->arestas.at(j).valor << "] ";
        }
        out << ") ";
    }

    return out;
}


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }


// excecao ArestaRepetida
template <class N>
class ArestaRepetida{
public:
    N inicio, fim;
    ArestaRepetida(N i, N f){
        inicio=i;
        fim=f;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar){
    out << "Aresta repetida: " << ar.inicio << " , " << ar.fim;
    return out;
}

//excecao ArestaInexistente
template <class N>
class ArestaInexistente{
public:
    N inicio, fim;
    ArestaInexistente(N i, N f){
        inicio = i;
        fim = f;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ai){
    out << "Aresta inexistente: " << ai.inicio << " , " << ai.fim;
    return out;
}