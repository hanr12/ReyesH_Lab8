//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#include <iostream>
#include <iomanip>
#include <string>
#include "Employee.h"

// parameterized constructor
Employee::Employee(int ei, const std::string& efn, const std::string& eln) {
    employeeID = new int(ei);
    empFirstName = new std::string(efn);
    empLastName = new std::string(eln);
}

// copy constructor
Employee::Employee(const Employee& other) {
    employeeID = new int(*other.employeeID);
    empFirstName = new std::string(*other.empFirstName);
    empLastName = new std::string(*other.empLastName);
}

// assignment operator
Employee& Employee::operator=(const Employee& other) {
    if (this == &other) return *this; // self-assignment check

    // free old memory
    delete employeeID;
    delete empFirstName;
    delete empLastName;

    // allocate new memory and copy
    employeeID = new int(*other.employeeID);
    empFirstName = new std::string(*other.empFirstName);
    empLastName = new std::string(*other.empLastName);

    return *this;
}

// destructor
Employee::~Employee() {
    delete employeeID;
    delete empFirstName;
    delete empLastName;
}

// setters
bool Employee::setEmployeeID(int ei) {
    *employeeID = ei;
    return true;
}

void Employee::setEmpFirstName(const std::string& efn) {
    *empFirstName = efn;
}

void Employee::setEmpLastName(const std::string& eln) {
    *empLastName = eln;
}

// getters
int Employee::getEmployeeID() const {
    return *employeeID;
}

std::string Employee::getEmpFirstName() const {
    return *empFirstName;
}

std::string Employee::getEmpLastName() const {
    return *empLastName;
}

// print function
void Employee::printEmployee(std::ostream& out) const {
    out << "Employee ID: " << *employeeID << "\n"
        << "First Name: " << *empFirstName << "\n"
        << "Last Name: " << *empLastName << std::endl;
}
