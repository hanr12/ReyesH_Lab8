//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#pragma once
#include <iostream>
#include <string>
#include "Employee.h"

class CaseManager : public Employee
{
private:
    double salary;
    std::string degree;

public:
    //constructor with defaults
    CaseManager(int ei = 0, std::string efn = "", std::string eln = "", double sal = 0.0, std::string deg = "");

    //destructor
    ~CaseManager();

    //setters
    bool setSalary(double sal);
    void setDegree(const std::string& deg);

    //getters
    double getSalary() const;
    std::string getDegree() const;

    //print function (overrides employee)
    void printDetails(std::ostream& out) const;
};
