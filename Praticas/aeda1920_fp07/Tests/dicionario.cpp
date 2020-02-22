#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//a alterar DONE
bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
     return palavra<ps1.getPalavra();
}

bool PalavraSignificado::operator==(const PalavraSignificado &ps1) const {
    return palavra==ps1.getPalavra();
}

//a alterar DONE
void Dicionario::lerDicionario(ifstream &fich)
{
    string palavra, significado;
    while(!fich.eof()){
        getline(fich,palavra);
        getline(fich, significado);
        PalavraSignificado p(palavra, significado);
        palavras.insert(p);
    }
}

//a alterar DONE
string Dicionario::consulta(string palavra) const
{
    PalavraSignificado ps(palavra,"");
    PalavraSignificado find = palavras.find(ps);
    PalavraSignificado notfound("","");
    if(find == notfound){
        BSTItrIn<PalavraSignificado> it(palavras);
        string palAntes="",signifAntes="";
        while (!it.isAtEnd() && it.retrieve()<ps)
        {
            palAntes=it.retrieve().getPalavra();
            signifAntes=it.retrieve().getSignificado();
            it.advance();
        }
        string palApos="",signifApos="";
        if (!it.isAtEnd())
        {
            palApos=it.retrieve().getPalavra();
            signifApos=it.retrieve().getSignificado();
        }
        throw PalavraNaoExiste(palAntes,signifAntes,palApos,signifApos);
    }
    return find.getSignificado();
}

//a alterar DONE
bool Dicionario::corrige(string palavra, string significado)
{
    PalavraSignificado p(palavra, "");
    PalavraSignificado find = palavras.find(p);
    PalavraSignificado notfound("","");
    if(find == notfound){
        palavras.insert(p);
        return false;
    }
    palavras.remove(p);
    find.setSignificado(significado);
    palavras.insert(find);
    return true;
}

//a alterar DONE
void Dicionario::imprime() const
{
    BSTItrIn<PalavraSignificado> it(palavras);
    while(!it.isAtEnd()){
        cout<<it.retrieve().getPalavra()<<endl;
        cout<<it.retrieve().getSignificado()<<endl;
        it.advance();
    }
//Outra maneira:
//    iteratorBST<PalavraSignificado> it2 = palavras.begin();
//    while (it2!=palavras.end()) {
//        cout << (*it2).getPalavra() << endl << (*it2).getSignificado() << endl;
//        it2++;
//    }
}

