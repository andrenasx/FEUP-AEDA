/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>
#include <string>

template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

class NoSuchBrandException {
    std::string brand;
public:
    NoSuchBrandException(std::string marca){brand=marca;}
    std::string getBrand(){return brand;}
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle) {
    if(vehicles.size()>=capacity)
        return false;
    for(auto it=vehicles.begin();it!=vehicles.end();it++){
        if(*(*it)==*vehicle)
            return false;
    }
    vehicles.push_back(vehicle);
    return true;
}

template<class Vehicle>
bool cmpVehicles(const Vehicle *v1, const Vehicle *v2){
    if(v1->getBrand() == v2->getBrand())
        return v1->getPrice()>v2->getPrice();
    return v1->getBrand()<v2->getBrand();
}

template<class Vehicle>
void Garage<Vehicle>::sortVehicles() {
    sort(vehicles.begin(),vehicles.end(),cmpVehicles<Vehicle>);
}

template<class Vehicle>
Vehicle *Garage<Vehicle>::removeVehicle(std::string brand, std::string model) {
    Vehicle *v;

    for(auto it=vehicles.begin();it!=vehicles.end();it++){
        if((*it)->getBrand()==brand && (*it)->getModel()==model){
            v=(*it);
            vehicles.erase(it);
            return v;
        }
    }
    throw NoSuchVehicleException();
}

template<class Vehicle>
float Garage<Vehicle>::avgPrice(std::string brand) const {
    float total=0;
    unsigned int num=0;

    for(auto it=vehicles.begin();it!=vehicles.end();it++){
        if((*it)->getBrand()==brand){
            total+=(*it)->getPrice();
            num++;
        }
    }
    if(num==0)
        throw NoSuchBrandException(brand);
    return total/(float)num;
}

#endif /* SRC_GARAGE_H_ */
