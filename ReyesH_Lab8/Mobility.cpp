//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025
#include "Mobility.h"
#include <iostream>
#include <iomanip>
#include <string>

//constructors
Mobility::Mobility() : Equipment(), operationMode("") {}
Mobility::Mobility(int id, std::string name, std::string date, double cost, int life, double salvage, std::string mode)
    : Equipment(id, name, date, cost, life, salvage), operationMode(mode) {
}

//destructor
Mobility::~Mobility() {}

//accessors
std::string Mobility::getOperationMode() const { return operationMode; }
void Mobility::setOperationMode(const std::string& mode) { operationMode = mode; }

//print details
void Mobility::printDetails(std::ostream& out) const {
    Equipment::printDetails(out);
    out << "Operation Mode: " << operationMode << "\n";
}

//depreciate public function
void Mobility::depreciate(std::ostream& out) const {
    // Print starting book value (required in instructions)
    const int periodWidth = 15;
    const int depWidth = 25;
    const int bookWidth = 20;

    out << std::setw(periodWidth / 2 + 1) << ""
        << std::setw(periodWidth / 2) << "Start"
        << std::setw(depWidth / 2 + 1) << ""
        << std::setw(depWidth / 2) << "----"
        << std::setw(bookWidth / 2 + 3) << ""
        << std::setw(bookWidth / 2) << std::fixed << std::setprecision(2) << originalCost
        << "\n";

    produceSchedule(out, equipmentName, 1, originalCost, salvageValue, usefulLife, 0);
}


//recursive helper function for double-declining balance depreciation
void Mobility::produceSchedule(std::ostream& out, const std::string& assetName, int year,
    double bookValue, double salvage, int usefulLife, double totalDep) const {

    const int periodWidth = 15;
    const int depWidth = 25;
    const int bookWidth = 20;

    if (year > usefulLife || bookValue <= salvage) {
        out << "\n"
            << std::setw(5) << ""
            << std::setw(periodWidth + depWidth - 5) << std::left << "Total Depreciation:"
            << std::setw(bookWidth) << std::right << std::fixed << std::setprecision(2) << totalDep
            << "\n";
        return;
    }

    double rate = 2.0 / usefulLife;
    double dep = bookValue * rate;

    // FIX: adjust final year depreciation so ending BV = salvage
    if ((bookValue - dep) < salvage) {
        dep = bookValue - salvage;
    }

    double endBookValue = bookValue - dep;

    out << std::setw(periodWidth / 2 + 1) << ""
        << std::setw(periodWidth / 2) << year
        << std::setw(depWidth / 2 + 1) << ""
        << std::setw(depWidth / 2) << std::fixed << std::setprecision(2) << dep
        << std::setw(bookWidth / 2 + 3) << ""
        << std::setw(bookWidth / 2) << std::fixed << std::setprecision(2) << endBookValue
        << "\n";

    produceSchedule(out, assetName, year + 1, endBookValue, salvage, usefulLife, totalDep + dep);
}
