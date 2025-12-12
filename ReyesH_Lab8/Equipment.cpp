//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025
#include "Equipment.h"
#include <iostream>
#include <iomanip>

//constructors
Equipment::Equipment() : equipmentID(0), equipmentName(""), purchaseDate(""),
originalCost(0), usefulLife(0), salvageValue(0) {
}

Equipment::Equipment(int id, std::string name, std::string date, double cost, int life, double salvage)
    : equipmentID(id), equipmentName(name), purchaseDate(date),
    originalCost(cost), usefulLife(life), salvageValue(salvage) {
}

//destructor
Equipment::~Equipment() {}

//accessors
int Equipment::getEquipmentID() const { return equipmentID; }
std::string Equipment::getEquipmentName() const { return equipmentName; }
std::string Equipment::getPurchaseDate() const { return purchaseDate; }
double Equipment::getOriginalCost() const { return originalCost; }
int Equipment::getUsefulLife() const { return usefulLife; }
double Equipment::getSalvageValue() const { return salvageValue; }

//mutators
void Equipment::setEquipmentID(int id) { equipmentID = id; }
void Equipment::setEquipmentName(const std::string& name) { equipmentName = name; }
void Equipment::setPurchaseDate(const std::string& date) { purchaseDate = date; }

//with error checking
void Equipment::setOriginalCost(double cost) {
    if (cost < 0) {
        std::cerr << "Error: originalCost cannot be negative. Value set to 0.\n";
        originalCost = 0;
    }
    else {
        originalCost = cost;
    }
}

void Equipment::setUsefulLife(int life) {
    if (life < 0) {
        std::cerr << "Error: usefulLife cannot be negative. Value set to 0.\n";
        usefulLife = 0;
    }
    else {
        usefulLife = life;
    }
}

void Equipment::setSalvageValue(double salvage) {
    if (salvage < 0) {
        std::cerr << "Error: salvageValue cannot be negative. Value set to 0.\n";
        salvageValue = 0;
    }
    else {
        salvageValue = salvage;
    }
}

//print details
void Equipment::printDetails(std::ostream& out) const {
    out << std::left
        << std::setw(5) << equipmentID
        << std::setw(25) << equipmentName
        << std::setw(12) << purchaseDate
        << std::setw(10) << originalCost
        << std::setw(8) << usefulLife
        << std::setw(10) << salvageValue
        << "\n";
}

//overloaded < operator
bool Equipment::operator<(const Equipment& other) const {
    return equipmentID < other.equipmentID;
}
