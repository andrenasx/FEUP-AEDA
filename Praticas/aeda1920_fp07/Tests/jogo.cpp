#include "jogo.h"
#include <sstream>


//a alterar DONE
ostream &operator << (ostream &os, Circulo &c1)
{
    string estado;
    if(c1.estado)
        estado = "true";
    else
        estado = "false";
    os << c1.pontuacao << "-" << estado << "-" << c1.nVisitas << endl;
    return os;
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int> &pontos, vector<bool> &estados)
{
    Circulo c1(pontos[pos],estados[pos]);
    if (niv==0) return BinaryTree<Circulo>(c1);
    BinaryTree<Circulo> filhoEsq=iniciaJogo(2 * pos + 1, niv - 1, pontos, estados);
    BinaryTree<Circulo> filhoDir=iniciaJogo(2 * pos + 2, niv - 1, pontos, estados);
    return BinaryTree<Circulo>(c1, filhoEsq, filhoDir);
}

//a alterar DONE
Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
    jogo=iniciaJogo(0,niv,pontos,estados);
}

//a alterar DONE
string Jogo::escreveJogo()
{
    BTItrLevel<Circulo> it(jogo);
    stringstream out("");
    while(!it.isAtEnd()){
        out << it.retrieve();
        it.advance();
    }
    return out.str();
}

//a alterar
int Jogo::jogada()
{
    int pos=1, pontos=0;
    BTItrLevel<Circulo> it(jogo);
    if(it.isAtEnd()) return pontos;
    while(true){
        Circulo &c=it.retrieve();
        bool estado = c.getEstado();
        int n;
        if(estado == false)
            n=pos;
        else
            n=pos+1;
        c.mudaEstado();
        c.incNVisitas();
        pontos=c.getPontuacao();
        int i=0;
        while(i<n && !it.isAtEnd()){
            it.advance();
            i++;
        }
        if(!it.isAtEnd())
            pos+=n;
        else
            break;
    }
    return pontos;
}


//a alterar
int Jogo::maisVisitado()
{
    BTItrLevel<Circulo> it(jogo);
    if(it.isAtEnd()) return -1;
    int maisV=-1;
    it.advance();
    while(!it.isAtEnd()){
        Circulo c = it.retrieve();
        if(c.getNVisitas()>maisV)
            maisV=c.getNVisitas();
        it.advance();
    }
    return maisV;
}

