/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar DONE c)
double Bank::getWithdraw(string cod1) const{
    double total=0;
    for(int i=0;i<accounts.size();i++){
        if(cod1==accounts.at(i)->getCodH())
            total+=accounts.at(i)->getWithdraw();
    }
    return total;
}


// a alterar DONE d)
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res={};

	for(int i=0;i<bankOfficers.size();i++){
	    if(name==bankOfficers.at(i).getName()) {
	        res=bankOfficers.at(i).getAccounts();
            bankOfficers.erase(bankOfficers.begin()+i);
            break;
        }
	}
	return res;
}


// a alterar DONE g)
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    //BankOfficer *bo= new BankOfficer();

    for(auto it=bankOfficers.begin();it!=bankOfficers.end();it++){
        if(it->getName()==name){
            it->addAccount(ac);
            return *it;
        }
    }
    throw NoBankOfficerException(name);

    //return *bo;
}

bool CmpAcc(Account *ac1, Account *ac2) {
    if(ac1->getBalance()==ac2->getBalance())
        return ac1->getCodIBAN()<ac2->getCodIBAN();
    return ac1->getBalance()<ac2->getBalance();
}

// a alterar DONE h)
void Bank::sortAccounts() {
    sort(accounts.begin(),accounts.end(),CmpAcc);
}

