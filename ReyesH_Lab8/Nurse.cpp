//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#include <iostream>
#include <iomanip>
#include "Nurse.h"


//parameterized constructor
Nurse::Nurse(int ei, std::string efn, std::string eln, float hw, std::string des)
    : Employee(ei, efn, eln), hourlyWage(hw), designation(des) {
}


// Destructor
Nurse::~Nurse() {}

// Setters
bool Nurse::setHourlyWage(float hw) {
    if (hw < 0) return false;
    hourlyWage = hw;
    return true;
}

void Nurse::setDesignation(const std::string& des) { designation = des; }

// Getters
float Nurse::getHourlyWage() const { return hourlyWage; }
std::string Nurse::getDesignation() const { return designation; }

// Print formatted details
void Nurse::printDetails(std::ostream& out) const {
    out << "          "  // 10-space indent to match headers
        << std::left << std::setw(10) << getEmployeeID()
        << std::setw(30) << (getEmpFirstName() + " " + getEmpLastName())
        << std::setw(15) << std::fixed << std::setprecision(2) << hourlyWage
        << std::setw(20) << designation << "\n";
}


