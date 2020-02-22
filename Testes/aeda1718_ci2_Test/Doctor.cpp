/*
 * Doctor.cpp
 */

#include "Doctor.h"


Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
	return medicalSpecialty;
}

unsigned Patient::getCode() const {
	return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
	return codeM;
}

string Doctor::getMedicalSpecialty() const {
	return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
	return patients;
}

void Doctor::addPatient(const Patient &p1) {
	patients.push(p1);
}

Patient Doctor::removeNextPatient() {
	if (!patients.empty()) {
		Patient p1 = patients.front();
		patients.pop();
		return p1;
	}
	else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {
    queue<Patient> aux = patients;
    vector<Patient> auxVec;

    for(int i=0; i<patients.size(); i++){
        auxVec.push_back(aux.front());
        aux.pop();
    }

    for (int i = 0; i < auxVec.size() ; i++) {
        if(auxVec.at(i).getCode() == codP1)
            aux.push(auxVec.at(i));
    }
    for(int i=0; i<auxVec.size(); i++){
        if(auxVec.at(i).getCode() != codP1)
            aux.push(auxVec.at(i));
    }

    patients=aux;
}

