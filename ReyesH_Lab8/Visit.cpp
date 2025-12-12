//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include "Visit.h"

// constructor: only VisitID
Visit::Visit(int vi) : visitID(vi) {}

// destructor
Visit::~Visit() {}

// setters
bool Visit::setVisitID(int vi) {
    if (vi < 0) return false;
    visitID = vi;
    return true;
}

void Visit::setNurse(const Nurse& n) { nurse = n; }
void Visit::setAide(const Aide& a) { aide = a; }

// tokenizeDate with InvalidDateException
void Visit::tokenizeDate(char* c, int& month, int& day, int& year)
{
    char seps[] = "/";
    char* token = nullptr;
    char* next_token = nullptr;

    // month
    token = strtok_s(c, seps, &next_token);
    if (!token) throw InvalidDateException("Missing month.");
    month = atoi(token);

    // day
    token = strtok_s(nullptr, seps, &next_token);
    if (!token) throw InvalidDateException("Missing day.");
    day = atoi(token);

    // year
    token = strtok_s(nullptr, seps, &next_token);
    if (!token) throw InvalidDateException("Missing year.");
    year = atoi(token);
}

// setVisitDate with InvalidDateException
void Visit::setVisitDate(const char* vd) {
    int m, d, y;
    char temp[20];
    strncpy_s(temp, vd, 19);
    temp[19] = '\0';

    // tokenize
    tokenizeDate(temp, m, d, y);

    // validation
    if (m < 1 || m > 12)
        throw InvalidDateException("Month must be 1-12.");

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    // leap year
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
        daysInMonth[1] = 29;

    if (d < 1 || d > daysInMonth[m - 1])
        throw InvalidDateException("Day is out of range for month.");

    if (y < 1000 || y > 9999)
        throw InvalidDateException("Year must be 4 digits.");

    visitDate.setDate(m, d, y);
}

// add service
void Visit::addService(const Service& s) {
    services.push_back(s);
}

// getters
int Visit::getVisitID() const { return visitID; }
Nurse Visit::getNurse() const { return nurse; }
Aide Visit::getAide() const { return aide; }
Date Visit::getVisitDate() const { return visitDate; }
std::vector<Service> Visit::getServices() const { return services; }

// print visit
void Visit::printVisit(std::ostream& out) const {
    const int leftPad = 10;
    const int servicePad = 25;

    out << std::string(leftPad, ' ') << "Visit ID: " << visitID
        << std::setw(40) << std::right << "Visit Date: " << visitDate << "\n";

    out << std::string(leftPad, ' ') << "Nurse: ";
    if (nurse.getEmployeeID() != 0)
        out << nurse.getEmpFirstName() << " " << nurse.getEmpLastName() << "\n";
    else
        out << "None\n";

    out << std::string(leftPad, ' ') << "Aide: ";
    if (aide.getEmployeeID() != 0)
        out << aide.getEmpFirstName() << " " << aide.getEmpLastName() << "\n";
    else
        out << "None\n";

    if (!services.empty()) {
        out << std::string(leftPad, ' ') << "Services:\n";
        for (const auto& s : services)
            out << std::string(leftPad + servicePad, ' ') << s.getServiceName() << "\n";
    }
    out << "\n";
}
