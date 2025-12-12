//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "Date.h"
#include "Equipment.h"
#include "Exception.h"   // centralized exceptions

//storageUnit template class
template <typename T>
class StorageUnit {
private:
    int ID;
    std::string description;
    int length;
    int width;
    int height;
    double costPerMonth;
    Date dateRented;
    bool humidityControlled;
    bool autoRenew;
    std::vector<T> inventory;  //vector of derived class equipment objects

public:
    //constructors
    StorageUnit()
        : ID(0), description(""), length(0), width(0), height(0),
        costPerMonth(0.0), humidityControlled(false), autoRenew(false) {
    }

    StorageUnit(int id, const std::string& desc, int l, int w, int h, double cost,
        const Date& date, bool humidity, bool autoR) {
        setID(id);
        setDescription(desc);
        setLength(l);
        setWidth(w);
        setHeight(h);
        setCostPerMonth(cost);
        setDateRented(date);
        setHumidityControlled(humidity);
        setAutoRenew(autoR);
    }

    //destructor
    ~StorageUnit() = default;

    //accessors
    int getID() const { return ID; }
    std::string getDescription() const { return description; }
    int getLength() const { return length; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    double getCostPerMonth() const { return costPerMonth; }
    Date getDateRented() const { return dateRented; }
    bool isHumidityControlled() const { return humidityControlled; }
    bool isAutoRenew() const { return autoRenew; }
    int getInventoryCount() const { return inventory.size(); }
    T getEquipment(int index) const {
        if (index < 0 || index >= inventory.size())
            throw std::out_of_range("Equipment index out of range.");
        return inventory[index];
    }

    //mutators
    void setID(int id) {
        if (id < 0) throw NegativeNumberException();
        ID = id;
    }
    void setDescription(const std::string& desc) { description = desc; }
    void setLength(int l) {
        if (l < 0) throw NegativeNumberException();
        length = l;
    }
    void setWidth(int w) {
        if (w < 0) throw NegativeNumberException();
        width = w;
    }
    void setHeight(int h) {
        if (h < 0) throw NegativeNumberException();
        height = h;
    }
    void setCostPerMonth(double cost) {
        if (cost < 0) throw NegativeNumberException();
        costPerMonth = cost;
    }
    void setDateRented(const Date& date) { dateRented = date; }
    void setHumidityControlled(bool humidity) { humidityControlled = humidity; }
    void setAutoRenew(bool autoR) { autoRenew = autoR; }

    //inventory functions
    void addEquipment(const T& item) {
        for (const auto& eq : inventory) {
            if (eq.getEquipmentID() == item.getEquipmentID())
                throw DuplicateIDException();
        }
        inventory.push_back(item);
    }

    bool contains(const T& item) const {
        for (const auto& eq : inventory) {
            if (eq.getEquipmentID() == item.getEquipmentID())
                return true;
        }
        return false;
    }

    void sortInventory() {
        std::sort(inventory.begin(), inventory.end());  //uses overloaded < operator in equipment
    }

    void printUnitInformation() const {
        std::cout << "\nStorage Unit Information:\n\n";
        std::cout << "    Unit ID:            " << ID << "\n";
        std::cout << "    Description:        " << description << "\n";
        std::cout << "    Dimensions\n";
        std::cout << "        Length:         " << length << " feet\n";
        std::cout << "        Width:          " << width << " feet\n";
        std::cout << "        Height:         " << height << " feet\n\n";

        std::cout << "    **Unit is " << (humidityControlled ? "" : "not ")
            << "humidity controlled.\n\n";

        std::cout << "    Rental Contract\n";
        std::cout << "        Cost Per Month:     $" << costPerMonth << "\n";
        std::cout << "        Date Signed:        " << dateRented << "\n\n";

        std::cout << "    **Contract does " << (autoRenew ? "" : "not ")
            << "auto-renew.\n\n";
    }

    void printInventory() const {
        std::cout << "                        " << description << " Inventory\n";
        std::cout << "*********************************************************************\n";

        if (inventory.empty()) {
            std::cout << "Inventory is empty.\n";
        }
        else {
            //print header
            std::cout << "ID    Name                     Date        Cost    Life   Salvage    Display/Operation\n";
            for (const auto& eq : inventory) {
                eq.printDetails(std::cout);  //make sure printDetails prints in the same table format
            }
        }

        std::cout << "*********************************************************************\n\n";
    }

};
