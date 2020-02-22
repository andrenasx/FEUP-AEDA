/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include <string>
#include <vector>

class Postman {
	unsigned int id;
	static unsigned int nextid;
	string name;
	vector<Mail *> myMail;
public:
	Postman();
	Postman(string name);
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;
	bool operator<(const Postman &p2);
};

template <class T>
unsigned int numberDifferent(const vector<T> &vi){
    int count=0;
    bool unique;

    for(auto i=vi.begin(); i!=vi.end(); i++){
        unique = true;
        for(auto j=vi.begin();j!=i;j++){
            if((*i)==(*j)){
                unique = false;
                break;
            }
        }
        if(unique)
            count++;
    }

    return count;
}


#endif /* SRC_POSTMAN_H_ */
