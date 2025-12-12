//Hannah Reyes
//CSCN 112 - Polymorphism and Operator Overloading
// 11/15/2025
#pragma once
#include <iostream>
#include <string>

class Equipment {
protected:
    int equipmentID;
    std::string equipmentName;
    std::string purchaseDate; // You could later use a Date class
    double originalCost;
    int usefulLife;
    double salvageValue;

public:
    // Constructors
    Equipment();
    Equipment(int id, std::string name, std::string date, double cost, int life, double salvage);

    // Destructor
    virtual ~Equipment();

    // Accessors
    int getEquipmentID() const;
    std::string getEquipmentName() const;
    std::string getPurchaseDate() const;
    double getOriginalCost() const;
    int getUsefulLife() const;
    double getSalvageValue() const;

    // Mutators
    void setEquipmentID(int id);
    void setEquipmentName(const std::string& name);
    void setPurchaseDate(const std::string& date);
    void setOriginalCost(double cost);
    void setUsefulLife(int life);
    void setSalvageValue(double salvage);

    // Pure virtual function
    virtual void depreciate(std::ostream& out) const = 0;

    // Print details
    virtual void printDetails(std::ostream& out) const;


    // Overloaded operator for sorting
    bool operator<(const Equipment& other) const;
};
