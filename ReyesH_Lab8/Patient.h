//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include "Visit.h"
#include "CaseManager.h"

class Patient
{
private:
    int patientID;
    std::string firstName;
    std::string lastName;
    std::string streetAddress;
    int age;
    float height;
    float weight;
    char gender;
    bool isAmbulatory;

    std::vector<int> bpmReadings;
    std::vector<Visit> visits;
    CaseManager caseManager; // new data member

public:
    //constructors
    Patient();
    Patient(int pi, std::string fn, std::string ln, std::string sa, int a, float h, float w, char g, bool ia);

    //destructor
    ~Patient();

    //setters
    bool setPatientID(int pi);
    void setFirstName(const std::string& fn);
    void setLastName(const std::string& ln);
    void setStreetAddress(const std::string& sa);
    bool setAge(int a);
    bool setHeight(float h);
    bool setWeight(float w);
    bool setGender(char g);
    void setIsAmbulatory(bool isAmbulatory);

    //casemanager access
    void setCaseManager(const CaseManager& cm);
    CaseManager getCaseManager() const;

    //BPM access
    int getBpmCount() const;
    int getReading(size_t index) const;
    void setReading(size_t index, int value);
    void addBpmReading(int bpm);

    double getBpmAverage() const;
    int getBpmMin() const;
    int getBpmMax() const;

    //visits
    //visits
    void addVisit(const Visit& v);

    //new required functions
    Visit getVisit(int index) const;   //return one visit
    int getNumVisits() const;          //return number of visits


    //getters
    int getPatientID() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getStreetAddress() const;
    int getAge() const;
    float getHeight() const;
    float getWeight() const;
    char getGender() const;
    bool getIsAmbulatory() const;

    //print details
    void printPatientDetails(std::ostream& out) const;

    //operator overloads
    friend std::ostream& operator<<(std::ostream& out, const Patient& p); //insertion operator
    Patient& operator++();        //prefix ++
    Patient operator++(int);      //postfix ++
    bool operator<(const Patient& other) const; // less-than operator (compare by firstName)

};
