//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Service.h"
#include "Nurse.h"
#include "Aide.h"
#include "Date.h"
#include "Exception.h"   // include your exceptions

class Visit {
public:
    // constructor (only VisitID now)
    Visit(int vi = 0);

    // destructor
    ~Visit();

    // setters
    bool setVisitID(int vi);
    void setNurse(const Nurse& n);
    void setAide(const Aide& a);
    void setVisitDate(const char* vd);  //accepts char array and throws InvalidDateException
    void addService(const Service& s);

    // getters
    int getVisitID() const;
    Nurse getNurse() const;
    Aide getAide() const;
    Date getVisitDate() const;
    std::vector<Service> getServices() const;

    // print
    void printVisit(std::ostream& out) const;

    // helper for parsing
    static void tokenizeDate(char* c, int& month, int& day, int& year); //throws InvalidDateException

private:
    int visitID;
    Nurse nurse;
    Aide aide;
    Date visitDate;
    std::vector<Service> services;
};
