//Hannah Reyes
//CSCN 112 - Polymorphism and Operator Overloading
// 11/15/2025
#pragma once
#include "Equipment.h"

class Mobility : public Equipment {
private:
    std::string operationMode;

    //private helper function for recursion (double-declining balance)
    void produceSchedule(std::ostream& out, const std::string& assetName, int year,
        double bookValue, double salvageValue, int usefulLife, double totalDep) const;

public:
    //constructors
    Mobility();
    Mobility(int id, std::string name, std::string date, double cost, int life, double salvage, std::string mode);

    //destructor
    ~Mobility();

    //accessors/Mutators
    std::string getOperationMode() const;
    void setOperationMode(const std::string& mode);

    //override depreciate
    void depreciate(std::ostream& out) const override;

    //override printDetails
    void printDetails(std::ostream& out) const override;
};
