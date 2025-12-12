//Hannah Reyes
//CSCN 112 - Polymorphism and Operator Overloading
// 11/15/2025
#pragma once
#include "Equipment.h"

class Monitor : public Equipment {
private:
    std::string displayType;

    //private helper function for recursion
    void produceSchedule(std::ostream& out, const std::string& assetName, int year,
        double originalCost, double salvageValue, int usefulLife, double annualDep) const;

public:
    //constructors
    Monitor();
    Monitor(int id, std::string name, std::string date, double cost, int life, double salvage, std::string display);

    //destructor
    ~Monitor();

    //accessors/Mutators
    std::string getDisplayType() const;
    void setDisplayType(const std::string& type);

    //override depreciate
    void depreciate(std::ostream& out) const override;

    //override printDetails
    void printDetails(std::ostream& out) const override;
};
