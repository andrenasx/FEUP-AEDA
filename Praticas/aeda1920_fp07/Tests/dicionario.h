#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() const { return palavra; }
       string getSignificado() const { return significado; }
       void setSignificado(string sig) { significado=sig; }
       bool operator < (const PalavraSignificado &ps1) const;
       bool operator == (const PalavraSignificado &ps1) const;
};

class Dicionario
{
      BST<PalavraSignificado> palavras;
public:
      Dicionario(): palavras(PalavraSignificado("","")){};
      BST<PalavraSignificado> getPalavras() const;
      void lerDicionario(ifstream &fich);
      string consulta(string palavra) const;
      bool corrige(string palavra, string significado);
      void imprime() const;
};

// a alterar    DONE
class PalavraNaoExiste
{
    string palavraantes, significadoantes, palavraapos, significadoapos;
public:
    PalavraNaoExiste(string pAntes, string sAntes, string pApos, string sApos):palavraantes(pAntes), significadoantes(sAntes), palavraapos(pApos), significadoapos(sApos) {}
	string getPalavraAntes() const { return palavraantes; }
	string getSignificadoAntes() const { return significadoantes; }
	string getPalavraApos() const { return palavraapos; }
	string getSignificadoApos() const { return significadoantes; }
};


#endif
