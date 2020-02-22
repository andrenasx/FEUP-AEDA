#include "maquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


// a alterar    DONE
unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
    unsigned counter=0;
	for(auto it = objs.begin();it!=objs.end();it++){
	    if((*it).getPeso()<=capacidadeCaixas){
            counter++;
            objetos.push(*it);
            it = objs.erase(it);
            it--;
	    }
	}
	return counter;
}

// a alterar    DONE
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	Caixa cx;
    HEAP_CAIXAS aux;
    bool found=false;

    while(!found){
        if(caixas.empty()){
            break;
        }
        else{
            if(caixas.top().getCargaLivre()>=obj.getPeso()){
                cx=caixas.top();
                caixas.pop();
                found = true;
            }
            else{
                aux.push(caixas.top());
                caixas.pop();
            }
        }
    }
    while(!aux.empty()) {
        caixas.push(aux.top());
        aux.pop();
    }
    return cx;
}

// a alterar    DONE
unsigned MaquinaEmpacotar::empacotaObjetos() {
    unsigned counter = 0;
    while(!objetos.empty()){
        Objeto obj = objetos.top();
        objetos.pop();
        Caixa cx = procuraCaixa(obj);
        if(cx.getSize()==0){
            counter++;
        }
        cx.addObjeto(obj);
        caixas.push(cx);
    }
    return counter;
}

// a alterar    DONE
string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
    if(objetos.empty()){
        return  "Nao ha objetos!\n";
    }
    stringstream out;
    HEAP_OBJS objs=objetos;
    while(!objs.empty()) {
        out << objs.top() << endl;
        objs.pop();
    }
    return out.str();
}

// a alterar
Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	if(caixas.empty()){
	    throw MaquinaSemCaixas();
	}
    HEAP_CAIXAS aux=caixas;
    Caixa cx = aux.top();
	while(!aux.empty()){
	    if(aux.top().getCargaLivre()<cx.getCargaLivre())
	        cx  = aux.top();
	    aux.pop();
	}

	return cx;
}



