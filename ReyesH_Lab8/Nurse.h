//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#pragma once
#include <iostream>
#include <string>
#include "Employee.h"

class Nurse : public Employee
{
private:
    float hourlyWage;
    std::string designation; // RN, LPN, Nurse Practitioner

public:
    //constructor with defaults
    Nurse(int ei = 0, std::string efn = "", std::string eln = "", float wage = 0.0f, std::string desig = "");

    //destructor
    ~Nurse();

    //setters
    bool setHourlyWage(float wage);
    void setDesignation(const std::string& desig);

    //getters
    float getHourlyWage() const;
    std::string getDesignation() const;

    //print function (overrides Employee)
    void printDetails(std::ostream& out) const;
};
#pragma once
