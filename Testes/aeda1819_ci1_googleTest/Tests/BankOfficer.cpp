/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"


BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

unsigned int i=0;
unsigned int getIDcounter(){
    i++;
    return i;
}

// a alterar DONE e)
BankOfficer::BankOfficer(string name){
    this->name=name;
    this->myAccounts={};
    this->id=getIDcounter();
}

//DONE f)
bool BankOfficer::operator>(const BankOfficer b){
    if(this->myAccounts.size()>b.myAccounts.size())
        return true;
    else if(this->myAccounts.size()==b.myAccounts.size() && this->name>b.name)
        return true;
    return false;
}
