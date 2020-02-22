/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name) {
    vector<Mail *>res;

    for(auto it=postmen.begin();it!=postmen.end();it++){
        if((*it).getName()==name){
            res=(*it).getMail();
            postmen.erase(it);
            break;
        }
    }
    return res;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
    balance=0;
    vector<Mail *>res;

    for(auto it=mailToSend.begin();it!=mailToSend.end();it++){
        balance+=(*it)->getPrice();

        if((*it)->getZipCode()>=firstZipCode && (*it)->getZipCode()<=lastZipCode){
            addMailToDeliver((*it));
        }
        else
            res.push_back((*it));

    }

    mailToSend.clear();
    return res;
}

Postman PostOffice::addMailToPostman(Mail *m, string name) {
    for(auto it=postmen.begin();it!=postmen.end();it++){
        if((*it).getName()==name){
            (*it).addMail(m);
            return *it;
        }
    }
    throw NoPostmanException(name);
}


