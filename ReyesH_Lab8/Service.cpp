//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025

#include <iostream>
#include <string>
#include "Service.h"

// single constructor with defaults
Service::Service(int id, const std::string& name) : serviceID(id), serviceName(name) {}

//destructor
Service::~Service() {}

//setters
void Service::setServiceID(int id) { serviceID = id; }
void Service::setServiceName(const std::string& name) { serviceName = name; }

// getters
int Service::getServiceID() const { return serviceID; }
std::string Service::getServiceName() const { return serviceName; }

//print function
void Service::printServiceDetails(std::ostream& out) const {
    out << "Service ID: " << serviceID << "\n"
        << "Service Name: " << serviceName << "\n";
}
