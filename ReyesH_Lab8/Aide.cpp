//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#include <iostream>
#include <iomanip>
#include "Aide.h"


//parameterized constructor
Aide::Aide(int ei, std::string efn, std::string eln, float hw, std::string cert)
    : Employee(ei, efn, eln), hourlyWage(hw), certification(cert) {
}


//destructor
Aide::~Aide() {}

//setters
bool Aide::setHourlyWage(float hw) {
    if (hw < 0) return false;
    hourlyWage = hw;
    return true;
}
void Aide::setCertification(const std::string& cert) { certification = cert; }

//getters
float Aide::getHourlyWage() const { return hourlyWage; }
std::string Aide::getCertification() const { return certification; }

//print formatted details
void Aide::printDetails(std::ostream& out) const {
    out << "          "  // 10-space indent to match headers
        << std::left << std::setw(10) << getEmployeeID()
        << std::setw(30) << (getEmpFirstName() + " " + getEmpLastName())
        << std::setw(15) << std::fixed << std::setprecision(2) << hourlyWage
        << std::setw(20) << certification << "\n";
}
