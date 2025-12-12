//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Patient.h"

//constructor, initializes members
Patient::Patient() {
    patientID = 0;
    firstName = " ";
    lastName = " ";
    streetAddress = " ";
    age = 0;
    height = 0;
    weight = 0;
    gender = ' ';
    isAmbulatory = false;
    bpmReadings.clear();
}

//multi-argument constructor
Patient::Patient(int pi, std::string fn, std::string ln, std::string sa, int a, float h, float w, char g, bool ia) {
    setPatientID(pi);
    setFirstName(fn);
    setLastName(ln);
    setStreetAddress(sa);
    setAge(a);
    setHeight(h);
    setWeight(w);
    setGender(g);
    setIsAmbulatory(ia);
    bpmReadings.clear();
}

//destructor
Patient::~Patient() {}

//setters
bool Patient::setPatientID(int pi) {
    if (pi < 1 || pi > 100) return false; // enforce 1-100
    patientID = pi;
    return true;
}

void Patient::setFirstName(const std::string& fn) { firstName = fn; }
void Patient::setLastName(const std::string& ln) { lastName = ln; }
void Patient::setStreetAddress(const std::string& sa) { streetAddress = sa; }

bool Patient::setAge(int a) {
    if (a < 1 || a > 120) return false;
    age = a;
    return true;
}

bool Patient::setHeight(float h) {
    if (h <= 0 || h > 106.0f) return false;
    height = h;
    return true;
}

bool Patient::setWeight(float w) {
    if (w <= 0 || w > 1000.0f) return false;
    weight = w;
    return true;
}

bool Patient::setGender(char g) {
    g = toupper(g);
    if (g != 'M' && g != 'F') return false;
    gender = g;
    return true;
}

void Patient::setIsAmbulatory(bool ambulatory) { isAmbulatory = ambulatory; }

//casemanager access
void Patient::setCaseManager(const CaseManager& cm) {
    caseManager = cm;
}

CaseManager Patient::getCaseManager() const {
    return caseManager;
}

//BPM access
int Patient::getBpmCount() const { return bpmReadings.size(); }

int Patient::getReading(size_t index) const {
    if (index >= bpmReadings.size()) return -1;
    return bpmReadings[index];
}

void Patient::setReading(size_t index, int value) {
    if (index < bpmReadings.size()) bpmReadings[index] = value;
}

//function to add a single BPM reading
void Patient::addBpmReading(int bpm) {
    if (bpm > 0) bpmReadings.push_back(bpm);
    else std::cout << "Error: BPM must be positive.\n";
}

//BPM stats
double Patient::getBpmAverage() const {
    if (bpmReadings.empty()) return 0.0;
    int sum = std::accumulate(bpmReadings.begin(), bpmReadings.end(), 0);
    return static_cast<double>(sum) / bpmReadings.size();
}

int Patient::getBpmMin() const {
    if (bpmReadings.empty()) return 0;
    int minVal = bpmReadings[0];
    for (size_t i = 1; i < bpmReadings.size(); ++i) {
        if (bpmReadings[i] < minVal) minVal = bpmReadings[i];
    }
    return minVal;
}

int Patient::getBpmMax() const {
    if (bpmReadings.empty()) return 0;
    int maxVal = bpmReadings[0];
    for (size_t i = 1; i < bpmReadings.size(); ++i) {
        if (bpmReadings[i] > maxVal) maxVal = bpmReadings[i];
    }
    return maxVal;
}

//visits
void Patient::addVisit(const Visit& v) { visits.push_back(v); }

//return one visit object by index
Visit Patient::getVisit(int index) const {
    if (index < 0 || index >= (int)visits.size()) {
        //handle errors
        return Visit(); //return empty visit object
    }
    return visits[index];
}

//return number of visits
int Patient::getNumVisits() const {
    return visits.size();
}


//getters
int Patient::getPatientID() const { return patientID; }
std::string Patient::getFirstName() const { return firstName; }
std::string Patient::getLastName() const { return lastName; }
std::string Patient::getStreetAddress() const { return streetAddress; }
int Patient::getAge() const { return age; }
float Patient::getHeight() const { return height; }
float Patient::getWeight() const { return weight; }
char Patient::getGender() const { return gender; }
bool Patient::getIsAmbulatory() const { return isAmbulatory; }


void Patient::printPatientDetails(std::ostream& out) const {
    const int SCREEN_WIDTH = 80;
    const int LABEL_WIDTH = 30;
    int leftPad = 10;

    auto printLine = [&](const std::string& label, const std::string& value) {
        out << std::string(leftPad, ' ')
            << std::setw(LABEL_WIDTH) << std::left << label
            << value << std::endl;
        };

    out << std::string(SCREEN_WIDTH, '-') << std::endl << std::endl;

    printLine("Patient ID:", std::to_string(getPatientID()));
    printLine("Patient Name:", getFirstName() + " " + getLastName());
    printLine("Address:", getStreetAddress());
    printLine("Age:", std::to_string(getAge()));

    out << std::string(leftPad, ' ')
        << std::setw(LABEL_WIDTH) << std::left << "Height:"
        << std::fixed << std::setprecision(1) << getHeight() << " inches" << std::endl;

    out << std::string(leftPad, ' ')
        << std::setw(LABEL_WIDTH) << std::left << "Weight:"
        << std::fixed << std::setprecision(1) << getWeight() << " pounds" << std::endl;

    printLine("Gender:", (getGender() == 'M' ? "Male" : "Female"));
    out << std::endl;

    out << std::string(leftPad, ' ')
        << (getIsAmbulatory() ? "*** Patient is ambulatory ***" : "*** Patient is not ambulatory ***")
        << std::endl << std::endl;

    //print BPM readings
    if (!bpmReadings.empty()) {
        std::vector<int> sortedBpm = bpmReadings;
        std::sort(sortedBpm.begin(), sortedBpm.end());

        out << std::string(leftPad, ' ') << "Heart rate (bpm) readings (sorted):" << std::endl
            << std::string(leftPad, ' ');
        for (int bpm : sortedBpm)
            out << bpm << "  ";
        out << std::endl << std::endl;

        out << std::string(leftPad, ' ') << "Patient statistics" << std::endl << std::endl;
        printLine("Number of bpm readings:", std::to_string(getBpmCount()));
        out << std::string(leftPad, ' ')
            << std::setw(LABEL_WIDTH) << std::left << "Average heart rate (bpm):"
            << std::fixed << std::setprecision(1) << getBpmAverage() << std::endl;
        printLine("Minimum heart rate (bpm):", std::to_string(getBpmMin()));
        printLine("Maximum heart rate (bpm):", std::to_string(getBpmMax()));
        out << std::endl;
    }

    //print assigned casemanager
    out << std::string(leftPad, ' ') << "Assigned Case Manager: ";
    if (caseManager.getEmployeeID() != 0) {
        out << caseManager.getEmpFirstName() << " " << caseManager.getEmpLastName() << std::endl;
    }
    else {
        out << "None" << std::endl;
    }


    //print visits (with nurse and aide)
    if (!visits.empty()) {
        out << std::string(leftPad, ' ') << "Visits:" << std::endl << std::endl;
        for (const auto& v : visits) {
            v.printVisit(out);
        }
    }

    out << std::string(SCREEN_WIDTH, '-') << std::endl << std::endl;
}

//insertion operator overload
std::ostream& operator<<(std::ostream& out, const Patient& p) {
    p.printPatientDetails(out);  //reuse existing function
    return out;
}

//prefix ++ (increments age by 1)
Patient& Patient::operator++() {
    age++;   //directly increment age
    return *this;
}

//postfix ++ (increments age by 1)
Patient Patient::operator++(int) {
    Patient temp = *this;
    age++;
    return temp;
}

//less-than operator (compare firstName)
bool Patient::operator<(const Patient& other) const {
    return firstName < other.firstName;
}

