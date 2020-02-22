/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) const {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
    vector<Book*> temp = books;
    for(auto it=temp.begin();it!=temp.end();it++){
        addCatalogItem(*it);
    }
    books=temp;
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;

	BookCatalogItem b = getCatalogItem(book->getTitle(),book->getAuthor());
	vector<Book*> books = b.getItems();

	for(auto it=books.begin();it!=books.end();it++){
	    if((*it)->getReader()== nullptr)
	        temp.push_back(*it);
	}

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
    vector<Book*> books = getAvailableItems(book);
    if(books.size()==0)
        return false;
    reader->addReading(books.at(0)->getTitle(),books.at(0)->getAuthor());
    book->setReader(reader);
    return true;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
    userRecords.insert(user);
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
    user->setEMail(newEMail);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
    for (auto it=candidates.begin();it!=candidates.end();it++){
        int count=0;
        if(!(*it).getReading().first.empty())
            count++;
        count+=(*it).getReadings().size();
        if(count>=min)
            readerCandidates.push(*it);
    }
}

int ReadingClub::awardReaderChampion(User& champion) {
    if(readerCandidates.empty())
        return 0;
    priority_queue<User> aux = readerCandidates;
    User c1 = aux.top();
    aux.pop();
    User c2 = aux.top();
    int count1=0;
    if(c1.getReading().first.empty())
        count1++;
    count1+=c1.getReadings().size();
    int count2=0;
    if(c2.getReading().first.empty())
        count2++;
    count2+=c2.getReadings().size();
    if(count1>count2){
        champion = c1;
        return readerCandidates.size();
    }
    return 0;
}
























