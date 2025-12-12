//Hannah Reyes
//CSCN 112 - Dynamic Allocation of Memory
// 11/1/2025
#pragma once
#include <iostream>
#include <string>

class Employee
{
private:
    int* employeeID;
    std::string* empFirstName;
    std::string* empLastName;

public:
    // constructors
    Employee(int ei = 0, const std::string& efn = "", const std::string& eln = "");

    // copy constructor
    Employee(const Employee& other);

    // assignment operator
    Employee& operator=(const Employee& other);

    // destructor
    ~Employee();

    // setters
    bool setEmployeeID(int ei);
    void setEmpFirstName(const std::string& efn);
    void setEmpLastName(const std::string& eln);

    // getters
    int getEmployeeID() const;
    std::string getEmpFirstName() const;
    std::string getEmpLastName() const;

    // print function
    void printEmployee(std::ostream& out) const;
};
