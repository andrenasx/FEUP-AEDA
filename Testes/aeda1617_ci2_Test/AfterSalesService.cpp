/*
 * AfterSalesService.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include <algorithm>
#include <stdexcept>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {
}

vector<Article*> AfterSalesService::getPresentsTable() const {
	return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
	return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
	return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
	for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
		presents[i]->setPresentNumber(i+1);
		presents[i]->setArrivalNumber(++tableOrdinal);
		presentsTable.push_back(presents[i]);
	}
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {
    vector<Article*> clientPresents;
    for(auto it=presentsTable.begin();it!=presentsTable.end();it++){
        if((*it)->getClient()==client){
            clientPresents.push_back(*it);
            it = presentsTable.erase(it);
            it--;
        }
    }
	return clientPresents;
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */

bool compareArticlesForTake(Article* a1, Article* a2) {
    if (a1->getPresentNumber() + 2 < a2->getPresentNumber())
        return true;
    return a1->getArrivalNumber() < a2->getArrivalNumber();
}

void AfterSalesService::sortArticles() {
    vector<Article*> toAlter = {presentsTable.begin(), presentsTable.begin() + 10};
    vector<Article*> deliverHomeVector;

    for (auto it = toAlter.begin(); it != toAlter.end(); it++) {
        if ((*it)->getDeliverHome()) {
            deliverHomeVector.push_back(*it);
            it = -- toAlter.erase(it);
        }
    }

    sort(toAlter.begin(), toAlter.end(), compareArticlesForTake);
    toAlter.insert(toAlter.end(), deliverHomeVector.begin(), deliverHomeVector.end());

    for (int i = 0; i < 10; i++)
        presentsTable[i] = toAlter[i];
}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */
void AfterSalesService::enqueueArticles() {
    int size = toWrapQueueSize - toWrap.size();
    if(presentsTable.size()<size)
        size = presentsTable.size();
    for(int i=0;i<size;i++){
        toWrap.push(presentsTable.at(0));
		presentsTable.erase(presentsTable.begin());
    }
    /*for(int i=0; i<size;i++){
        try{
            toWrap.push(presentsTable.at(0));
            presentsTable.erase(presentsTable.begin());
        }
        catch(out_of_range){
            return;
        }
    }*/
}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {
    if(toWrap.empty())
        return NULL;
    else if(toWrap.front()->getDeliverHome()){
        toDeliver.push(toWrap.front());
        toWrap.pop();
        return NULL;
    }
    Article *a = toWrap.front();
    toWrap.pop();
    return a;
}

