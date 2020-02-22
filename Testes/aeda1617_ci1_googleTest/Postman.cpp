/*
 * Postman.cpp
 */
#include "Postman.h"


Postman::Postman(): id(0) {}

unsigned int Postman::nextid = 1;

Postman::Postman(string name): id(nextid++), name(name) {}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator<(const Postman &p2) {
    vector<string> zipCode1, zipCode2;

    for(auto it=myMail.begin();it!=myMail.end();it++){
        zipCode1.push_back((*it)->getZipCode());
    }
    for(auto it=p2.myMail.begin();it!=p2.myMail.end();it++){
        zipCode2.push_back((*it)->getZipCode());
    }

    return numberDifferent(zipCode1)<numberDifferent(zipCode2);
}
