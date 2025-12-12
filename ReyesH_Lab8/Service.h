//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025

#pragma once
#include <iostream>
#include <string>

class Service {
private:
    int serviceID;
    std::string serviceName;

public:
    //constructor with default parameters (serves as default and multi-arg)
    Service(int id = 0, const std::string& name = "");

    //destructor
    ~Service();

    //setters
    void setServiceID(int id);
    void setServiceName(const std::string& name);

    //getters
    int getServiceID() const;
    std::string getServiceName() const;

    //print function
    void printServiceDetails(std::ostream& out) const;
};
