/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    unsigned int count=0;
    for(auto it=doctors.begin();it!=doctors.end();it++){
        if((*it).getMedicalSpecialty()==medicalSpecialty) {
            count+=(*it).getPatients().size();
        }
    }
    return count;
}

bool cmpDoctors(const Doctor &d1, const Doctor &d2){
    if(d1.getMedicalSpecialty() == d2.getMedicalSpecialty() && d1.getPatients().size() == d2.getPatients().size())
        return d1.getCode() < d2.getCode();
    else if (d1.getPatients().size() == d2.getPatients().size())
        return d1.getMedicalSpecialty() < d2.getMedicalSpecialty();
    return d1.getPatients().size() < d2.getPatients().size();
}

void Hospital::sortDoctors() {
    doctors.sort(cmpDoctors);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
    unsigned int count=0;
    for(auto it=doctors.begin();it!=doctors.end();it++){
        if((*it).getMedicalSpecialty() == medicalSpecialty1)
            count++;
    }
    if(count>=3)
        return false;
    doctors.push_back(Doctor(codM1,medicalSpecialty1));
    return true;
}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> p1;

    for(auto it= doctors.begin(); it!=doctors.end();it++){
        if((*it).getCode() == codM1){
            p1 = (*it).getPatients();
            doctors.erase(it);
            return p1;
        }
    }
    throw DoctorInexistent();
}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
    vector<Doctor> d;
    int menor=0;
    for(auto it=doctors.begin();it!=doctors.end();it++){
        if((*it).getMedicalSpecialty() == medicalSpecialty1)
            d.push_back(*it);
    }
    if(d.empty())
        return false;

    for(int i=1; i<d.size();i ++){
        if(d.at(i).getPatients().size()<d.at(menor).getPatients().size())
            menor = i;
    }

    for(auto it=doctors.begin();it!=doctors.end();it++){
        if((*it).getCode() == d.at(menor).getCode())
            (*it).addPatient(Patient(cod1, medicalSpecialty1));
    }
    return true;
}



void Hospital::processPatient(unsigned codM1) {
    for(auto it=doctors.begin();it!=doctors.end();it++){
        if((*it).getCode() == codM1 && (*it).getPatients().size()!=0){
            Patient p = (*it).getPatients().front();
            (*it).removeNextPatient();
            for(auto it2=letterTray.begin();it2!=letterTray.end();it2++){
                if((*it2).size() < trayCapacity) {
                    (*it2).push(p);
                    return;
                }
            }
            stack<Patient> stackP;
            stackP.push(p);
            letterTray.push_back(stackP);
            return;
        }
    }
}


unsigned Hospital::removePatients(unsigned codP1) {
    unsigned int count=0;
    for(auto it = letterTray.begin(); it!=letterTray.end(); it++){
        if((*it).top().getCode() == codP1){
            (*it).pop();
            count ++;
        }
        if((*it).empty()){
            it = letterTray.erase(it);
            it--;
        }
    }
    return count;
}
