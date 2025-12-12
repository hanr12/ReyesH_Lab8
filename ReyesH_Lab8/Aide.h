//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#pragma once
#include <iostream>
#include <string>
#include "Employee.h"

class Aide : public Employee
{
private:
    float hourlyWage;
    std::string certification;

public:
    //constructor with defaults
    Aide(int ei = 0, std::string efn = "", std::string eln = "", float wage = 0.0f, std::string desig = "");

    //destructor
    ~Aide();

    //setters
    bool setHourlyWage(float wage);
    void setCertification(const std::string& cert);

    //getters
    float getHourlyWage() const;
    std::string getCertification() const;

    //print function (overrides Employee)
    void printDetails(std::ostream& out) const;
};
