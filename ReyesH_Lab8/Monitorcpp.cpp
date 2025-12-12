//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025
#include "Monitor.h"
#include <iostream>
#include <iomanip>
#include <string>

//constructors
Monitor::Monitor() : Equipment(), displayType("") {}
Monitor::Monitor(int id, std::string name, std::string date, double cost, int life, double salvage, std::string display)
    : Equipment(id, name, date, cost, life, salvage), displayType(display) {
}

//destructor
Monitor::~Monitor() {}

//accessors/Mutators
std::string Monitor::getDisplayType() const { return displayType; }
void Monitor::setDisplayType(const std::string& type) { displayType = type; }

//print details
void Monitor::printDetails(std::ostream& out) const {
    Equipment::printDetails(out);
    out << "Display Type: " << displayType << "\n";
}

//depreciate public function
void Monitor::depreciate(std::ostream& out) const {
    const int periodWidth = 15;
    const int depWidth = 25;
    const int bookWidth = 20;

    // FIX: print starting book value
    out << std::setw(periodWidth / 2 + 1) << ""
        << std::setw(periodWidth / 2) << "Start"
        << std::setw(depWidth / 2 + 1) << ""
        << std::setw(depWidth / 2) << "----"
        << std::setw(bookWidth / 2 + 3) << ""
        << std::setw(bookWidth / 2) << std::fixed << std::setprecision(2) << originalCost
        << "\n";

    double annualDep = (originalCost - salvageValue) / usefulLife;
    produceSchedule(out, equipmentName, 1, originalCost, salvageValue, usefulLife, annualDep);
}


//recursive helper function for straight-line depreciation
void Monitor::produceSchedule(std::ostream& out, const std::string& assetName, int year,
    double bookValue, double salvage, int usefulLife, double annualDep) const {

    const int periodWidth = 15;
    const int depWidth = 25;
    const int bookWidth = 20;

    if (year > usefulLife) {
        double totalDep = annualDep * usefulLife;
        out << "\n"
            << std::setw(5) << ""                         //smaller initial padding
            << std::setw(periodWidth + depWidth - 5) << std::left << "Total Depreciation:"
            << std::setw(bookWidth) << std::right << std::fixed << std::setprecision(2) << totalDep
            << "\n";
        return;
    }


    double endBookValue = bookValue - annualDep;
    if (endBookValue < salvage) endBookValue = salvage;

    //centered formatting
    out << std::setw(periodWidth / 2 + 1) << ""          
        << std::setw(periodWidth / 2) << year           
        << std::setw(depWidth / 2 + 1) << ""            
        << std::setw(depWidth / 2) << std::fixed << std::setprecision(2) << annualDep 
        << std::setw(bookWidth / 2 + 3) << ""           
        << std::setw(bookWidth / 2) << std::fixed << std::setprecision(2) << endBookValue 
        << "\n";


    produceSchedule(out, assetName, year + 1, endBookValue, salvage, usefulLife, annualDep);
}
