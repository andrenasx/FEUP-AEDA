/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) const{
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
    BSTItrIn<Expertize> it(expertizes);
    while(!it.isAtEnd()){
        if(it.retrieve().getName() ==expertizeAvailable && it.retrieve().getCost() == cost){
            it.retrieve().addConsultant(student);
            return;
        }
        it.advance();
    }
    Expertize exp1(expertizeAvailable,cost);
    exp1.addConsultant(student);
    expertizes.insert(exp1);
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	
    Expertize exp1 = getExpertize(project->getExpertize(),project->getCost());
	if(exp1.getName()!="") {
        vector<Student *> s = exp1.getConsultants();
        for (auto c = s.begin(); c != s.end(); c++) {
            if ((*c)->getCurrentProject().empty())
                temp.push_back(*c);
        }
    }

	return temp;
}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
    if(project->getConsultant()!= nullptr || !student->getCurrentProject().empty())
        return false;
    vector<Student*> available = getCandidateStudents(project);
    for(auto it=available.begin();it!=available.end();it++){
        if((*it)->getName() == student->getName() && (*it)->getEMail() == student->getEMail()){
            project->setConsultant(student);
            student->addProject(project->getTitle());
            return true;
        }
    }
    return false;
}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
    students.insert(student);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
    student->setEMail(newEMail);
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
    for(auto it=candidates.begin();it!=candidates.end();it++){
        if((*it).getPastProjects().size()>=min){
            activeStudents.push(*it);
        }
    }
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
    int count = activeStudents.size();
    if(count==0){
        return 0;
    }
    else if(count == 1){
        studentMaximus = activeStudents.top();
        return 1;
    }
    priority_queue<Student> aux = activeStudents;
    Student st1 = aux.top();
    aux.pop();
    Student st2 = aux.top();
    if(st1.getPastProjects().size() == st2.getPastProjects().size())
        return 0;

    studentMaximus = st1;
    return count;
}





















