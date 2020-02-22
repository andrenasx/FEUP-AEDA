/*
 * Account.cpp
 */
#include <iostream>
#include "Account.h"
using namespace std;

Account::Account(string hold, string codeH, string codeA, double bal): holder(hold), codeHolder(codeH), codeIBAN(codeA), balance(bal) {}

Account::~Account(){ }

string Account::getCodH() const {
	return codeHolder;
}

string Account::getCodIBAN() const {
	return codeIBAN;
}

double Account::getBalance() const {
	return balance;
}

SavingsAccount::SavingsAccount (string hold, string codeH, string codeA, double bal, double pct):
		Account(hold, codeH, codeA, bal), rate(pct/100)
{ }


CheckingAccount::CheckingAccount(string hold, string codeH, string codeA, double bal,double lim):
			Account(hold, codeH, codeA, bal) {
	limit = lim;
}


TimeAccount::TimeAccount(string hold, string codeH, string codeA, double bal, double pct):
			SavingsAccount(hold, codeH, codeA, bal, pct) {
	funds_avail = balance*rate;
}

//b)
double CheckingAccount::getCharge() const {
    if(limit<=500)
        return 0.50;
    else if(limit>500 && limit<=1000)
        return 0.25;
    return 0;
}

double SavingsAccount::getCharge() const {
    if(rate*100 > 2.0)
        return 0.80;
    return 0;
}


//c)
double Account::getWithdraw() const {
    return balance;
}

Account::Account(const Account &a2) {
    this->holder=a2.holder;
    this->codeHolder=a2.codeHolder;
    this->balance=a2.balance;
    this->codeIBAN=a2.codeIBAN;
}

double CheckingAccount::getWithdraw() const {
    return Account::getWithdraw();
}

double SavingsAccount::getWithdraw() const {
    return Account::getWithdraw();
}

double TimeAccount::getWithdraw() const {
    return funds_avail;
}

