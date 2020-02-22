/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
		numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// TODO

bool Cinema::operator<(const Cinema & cr) const
{
    if(this->distance==cr.distance)
        return this->services<cr.services;
    return this->distance<cr.distance;
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	BST<FilmTime> tempTable = timetable;

	while(!tempTable.isEmpty()){
	    FilmTime it = tempTable.findMax();
	    if(it.getHour()==h1){
	        return it.getFilm();
	    }
	    else if(it.getHour()<h1){
            h1=it.getHour();
	        return it.getFilm();
	    }
	    tempTable.remove(it);
	}
	return NULL;
}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
    BSTItrIn<FilmTime> it(timetable);

    while(!it.isAtEnd()){
        if(it.retrieve().getRoomID()==room1){
            if(it.retrieve().getHour()==h2){
                return false;
            }
        }
        it.advance();
    }

    BSTItrIn<FilmTime> it2(timetable);
    while(!it2.isAtEnd()){
        FilmTime temp = it.retrieve();
        if(temp.getRoomID()==room1){
            if(temp.getHour()==h1){
                timetable.remove(temp);
                temp.setHour(h2);
                timetable.insert(temp);
                return true;
            }
        }
        it2.advance();
    }

    return false;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned roomToUse = 0;

	// TODO

	return roomToUse;
}






