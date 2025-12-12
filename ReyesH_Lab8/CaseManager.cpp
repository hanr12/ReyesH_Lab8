//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#include <iostream>
#include <iomanip>
#include "CaseManager.h"

//parameterized constructor
CaseManager::CaseManager(int ei, std::string efn, std::string eln, double sal, std::string deg)
    : Employee(ei, efn, eln), salary(sal), degree(deg) {
}

//destructor
CaseManager::~CaseManager() {}

//setters
bool CaseManager::setSalary(double sal) {
    if (sal < 0) return false;
    salary = sal;
    return true;
}
void CaseManager::setDegree(const std::string& deg) { degree = deg; }

//getters
double CaseManager::getSalary() const { return salary; }
std::string CaseManager::getDegree() const { return degree; }

//formatted printDetails function
void CaseManager::printDetails(std::ostream& out) const {
    out << "          "  // 10-space indent to match headers
        << std::left << std::setw(10) << getEmployeeID()
        << std::setw(30) << (getEmpFirstName() + " " + getEmpLastName())
        << std::setw(15) << std::fixed << std::setprecision(2) << salary
        << std::setw(20) << degree << "\n";
}

