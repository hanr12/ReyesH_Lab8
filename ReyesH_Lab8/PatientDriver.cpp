//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include <vector>
#include <random>     
#include <typeinfo>
#include "Patient.h"
#include "Visit.h"
#include "Service.h"
#include "Employee.h"
#include "Nurse.h"
#include "Aide.h"
#include "CaseManager.h"
#include "Equipment.h"
#include "Monitor.h"
#include "Mobility.h"
#include "StorageUnit.h"

using namespace std;

//constants for formatting and limits
const int SCREEN_WIDTH = 80;       //width of screen for formatting headers/footers
const string INDENT = "     ";     //indentation for user interface prompts
const size_t MAX_PATIENTS = 50;    //maximum number of patients allowed

//functions
int calculateOffset(const string& s);
int main();
void clearCin();
void wait();
void printHeader(ostream& out, const string& company, const string& title);
void printFooter(ostream& out);
void printMainMenu();
void printPatientMenu();
void printEmployeeMenu();
void printEquipmentMenu();
Patient editPatients();
bool inputPatient(Patient& p, const string& fileName, size_t currentPatientCount);
void deletePatient(vector<Patient>& patients);

//display patient list sorted by first name
void showPatientList(const vector<Patient>& patients);

int numEmployees(const string& fileName);

void loadEquipment(vector<Equipment*>& equipment, const string& filename);
void showEquipment(const vector<Equipment*>& equipment);
void equipmentMenu(vector<Equipment*>& equipment);

//prototypes for templates
template<typename T>
void loadEmployeeData(T**& arr, int& count, const string& filename);

template<typename T>
void showEmployees(T** arr, int count);

template<typename T>
void sortEmployees(T** arr, int count);

template<typename T>
int findEmployee(int id, T** arr, int count);

//unique patientid
int generateUniquePatientID(const std::vector<Patient>& patients, std::mt19937& gen, std::uniform_int_distribution<int>& dis);

//unique visitid
void validateUniqueVisitID(Patient& patient, int visitID);

//made a template for a more clean look
template <typename T>
void updateStorageUnit(StorageUnit<T>& unit);

//menu options enumeration for clarity
enum MenuOptions { ADD_MANUAL = 1, READ_FILE, DELETE_PATIENT, CREATE_VISIT, CASE_MANAGER, PRINT_SCREEN, SAVE_FILE, INCREASE_AGE, EXIT };

int main() {
    //random number generator for PatientID
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 1000);

    vector<Patient> patients;
    vector<Service> availableServices;
    vector<Equipment*> equipmentList; //new equipment vector

    //employee dynamic arrays
    Nurse** nurses = nullptr;
    Aide** aides = nullptr;
    CaseManager** caseManagers = nullptr;
    int nurseCount = 0, aideCount = 0, caseManagerCount = 0;

    //load services
    ifstream serviceFile("services.txt");
    if (!serviceFile) {
        cerr << "Error: could not open services.txt\n";
        wait();
        return 1;
    }

    while (true) {
        int id; string name;
        if (!(serviceFile >> id)) break;
        serviceFile.ignore();
        if (!getline(serviceFile, name)) break;
        availableServices.push_back(Service(id, name));
    }
    serviceFile.close();

    //load employees
    loadEmployeeData(nurses, nurseCount, "nurses.txt");
    loadEmployeeData(aides, aideCount, "aides.txt");
    loadEmployeeData(caseManagers, caseManagerCount, "caseManagers.txt");

    // warn user about missing employee files
if (nurseCount == 0) {
    cout << "ERROR: nurses.txt could not be opened or contains no data.\n";
    cout << "You will NOT be able to assign a nurse to a visit.\n";
    cout << "Please fix the file and restart the application if you need this functionality.\n\n";
    wait();
}

if (aideCount == 0) {
    cout << "ERROR: aides.txt could not be opened or contains no data.\n";
    cout << "You will NOT be able to assign an aide to a visit.\n";
    cout << "Please fix the file and restart the application if you need this functionality.\n\n";
    wait();
}

if (caseManagerCount == 0) {
    cout << "ERROR: caseManagers.txt could not be opened or contains no data.\n";
    cout << "You will NOT be able to assign a case manager.\n";
    cout << "Please fix the file and restart the application if you need this functionality.\n\n";
    wait();
}


    //load equipment
    loadEquipment(equipmentList, "equipment.txt");

    int mainChoice = 0;
    do {
        printMainMenu();
        cin >> mainChoice;
        while (cin.fail() || mainChoice < 1 || mainChoice > 4) {
            cout << "Error: invalid selection. Please choose again: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> mainChoice;
        }

        switch (mainChoice) {
        case 1: { // Patients
            int patientChoice = 0;
            do {
                printPatientMenu();
                cin >> patientChoice;
                while (cin.fail() || patientChoice < 1 || patientChoice > 9) {
                    cout << "Error: invalid selection. Please choose again: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cin >> patientChoice;
                }

                switch (patientChoice) {
                    //entire patient switched
                case ADD_MANUAL:
                    system("cls");
                    if (patients.size() >= MAX_PATIENTS) {
                        cout << "Error: Maximum number of patients reached.\n"; wait(); break;
                    }
                    {
                        Patient p = editPatients();
                        p.setPatientID(dis(gen));  // assign random ID
                        patients.push_back(p);
                    }
                    system("cls");
                    break;

                case READ_FILE:
                    system("cls");
                    if (patients.size() >= MAX_PATIENTS) { cout << "Error: Maximum patients reached.\n"; wait(); break; }
                    {
                        string fileName;
                        cout << "Enter file name: ";
                        clearCin();
                        getline(cin, fileName);
                        Patient p;
                        if (inputPatient(p, fileName, patients.size())) {
                            p.setPatientID(dis(gen));  // assign random ID
                            patients.push_back(p);
                        }
                        wait();
                    }
                    break;

                case DELETE_PATIENT:
                    system("cls");

                    if (patients.empty()) {
                        cout << "No patients available.\n";
                        wait();
                        break;
                    }
                    //patient list display added
                    cout << "\nCurrent Patient List:\n";
                    showPatientList(patients);
                    cout << endl;

                    deletePatient(patients);
                    wait();
                    break;

                case CREATE_VISIT:
                    system("cls");
                    if (patients.empty()) {
                        cout << "No patients available.\n";
                        wait();
                        break;
                    }

                    {
                        int patientID;
                        cout << "\nCurrent Patient List:\n";
                        showPatientList(patients);
                        cout << endl;

                        cout << "Enter patient ID for the visit: ";
                        while (!(cin >> patientID)) {
                            cout << "Invalid input. Please enter a number: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        auto it = find_if(patients.begin(), patients.end(), [&](Patient& p) {
                            return p.getPatientID() == patientID;
                            });

                        if (it == patients.end()) {
                            cout << "Patient not found.\n";
                            wait();
                            break;
                        }

                        //unique visit id
                        int visitID;
                        while (true) {
                            cout << "Enter Visit ID: ";
                            while (!(cin >> visitID)) {
                                cout << "Invalid input. Please enter a number: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            bool duplicate = false;
                            for (int i = 0; i < it->getNumVisits(); ++i) {
                                if (it->getVisit(i).getVisitID() == visitID) {
                                    duplicate = true;
                                    break;
                                }
                            }
                            if (duplicate) {
                                cout << "Duplicate Visit ID. Please enter a unique ID.\n";
                            }
                            else {
                                break; //valid ID
                            }
                        }

                        //create visit with one-argument constructor
                        Visit visit(visitID);

                        //visit date handling
                        bool validDate = false;
                        char date[20];
                        while (!validDate) {
                            cout << "Enter Visit Date (MM/DD/YYYY): ";
                            cin.getline(date, 20);

                            try {
                                visit.setVisitDate(date); //may throw InvalidDateException
                                validDate = true;
                            }
                            catch (const InvalidDateException& e) {
                                cout << "Invalid date: " << e.what() << endl;
                            }
                            catch (const std::exception& e) {
                                cout << "Error: " << e.what() << endl;
                            }
                        }

                        //nurse selection
                        if (nurseCount == 0) {
                            cout << "Error: No nurses loaded. Cannot assign nurse.\n";
                            wait();
                        }
                        else {
                            cout << "\nAvailable Nurses:\n";
                            showEmployees(nurses, nurseCount);

                            int nurseID, nIndex;
                            cout << "Enter Nurse ID (0 for none): ";
                            while (true) {
                                while (!(cin >> nurseID)) {
                                    cout << "Invalid input. Enter a number: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                if (nurseID == 0) break;
                                nIndex = findEmployee(nurseID, nurses, nurseCount);
                                if (nIndex != -1) { visit.setNurse(*nurses[nIndex]); break; }
                                cout << "Invalid Nurse ID. Try again (or 0 for none): ";
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        //aide selection
                        if (aideCount == 0) {
                            cout << "Error: No aides loaded. Cannot assign aide.\n";
                            wait();
                        }
                        else {
                            cout << "\nAvailable Aides:\n";
                            showEmployees(aides, aideCount);

                            int aideID, aIndex;
                            cout << "Enter Aide ID (0 for none): ";
                            while (true) {
                                while (!(cin >> aideID)) {
                                    cout << "Invalid input. Enter a number: ";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                if (aideID == 0) break;
                                aIndex = findEmployee(aideID, aides, aideCount);
                                if (aIndex != -1) { visit.setAide(*aides[aIndex]); break; }
                                cout << "Invalid Aide ID. Try again (or 0 for none): ";
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        //services selection
                        cout << "\nAvailable Services:\n";
                        for (size_t i = 0; i < availableServices.size(); ++i)
                            cout << i + 1 << "\t" << availableServices[i].getServiceName() << endl;

                        int serviceChoice;
                        cout << "Enter service numbers (0 to stop):\n";
                        while (true) {
                            cout << "Service #: ";
                            while (!(cin >> serviceChoice)) {
                                cout << "Invalid input. Enter a number.\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            if (serviceChoice == 0) break;
                            if (serviceChoice < 1 || serviceChoice >(int)availableServices.size()) {
                                cout << "Invalid choice.\n";
                                continue;
                            }
                            visit.addService(availableServices[serviceChoice - 1]);
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        //add visit to patient
                        it->addVisit(visit);
                        cout << "\nVisit created:\n";
                        visit.printVisit(cout);
                        wait();
                    }
                    break;


                case CASE_MANAGER:
                    system("cls");
                    if (patients.empty()) { cout << "No patients available.\n"; wait(); break; }
                    {
                        int patientID;

                        //patient list display added
                        cout << "\nCurrent Patient List:\n";
                        showPatientList(patients);
                        cout << endl;

                        cout << "Enter patient ID to assign Case Manager: ";
                        while (!(cin >> patientID)) {
                            cout << "Invalid input. Please enter a number: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        auto it = find_if(patients.begin(), patients.end(), [&](Patient& p) { return p.getPatientID() == patientID; });
                        if (it == patients.end()) { cout << "Patient not found.\n"; wait(); break; }

                        //error checking for Case Managers
                        if (caseManagerCount == 0) {
                            cout << "Error: No case managers are loaded. Cannot create a visit.\n";
                            wait();
                            break;
                        }

                        cout << "\nThe following Case Managers are currently employed by HCO:\n";
                        showEmployees(caseManagers, caseManagerCount);

                        int cmID, cmIndex;
                        do {
                            cout << "Enter Case Manager ID: ";
                            while (!(cin >> cmID)) {
                                cout << "Invalid input. Please enter a number: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cmIndex = findEmployee(cmID, caseManagers, caseManagerCount);
                            if (cmIndex == -1) cout << "Invalid Case Manager ID. Please try again.\n";
                        } while (cmIndex == -1);

                        it->setCaseManager(*caseManagers[cmIndex]);
                        cout << "Case Manager assigned successfully.\n";
                        wait();
                    }
                    break;

                case PRINT_SCREEN:
                    system("cls");
                    {
                        const string company = "Health Care Options, Inc.";
                        const string title = "Patient Report";
                        printHeader(cout, company, title);
                        for (auto& p : patients) cout << p; //overload << operator
                        printFooter(cout);
                    }
                    wait();
                    break;

                case SAVE_FILE:
                    system("cls");
                    {
                        string fileName;
                        cout << "Enter output filename: ";
                        clearCin();
                        getline(cin, fileName);
                        ofstream output(fileName);
                        if (!output.is_open()) {
                            cout << "Error: Could not open file " << fileName << endl;
                            wait();
                            break;
                        }

                        const string company = "Health Care Options, Inc.";
                        const string title = "Patient Report";
                        printHeader(output, company, title);

                        for (auto& p : patients)
                            output << p;

                        printFooter(output);
                        output.close();
                        cout << "Successfully exported to " << fileName << "\n\n";
                    }
                    wait();
                    break;

                case INCREASE_AGE:
                    system("cls");
                    if (patients.empty()) {
                        cout << "No patients available.\n"; wait(); break;
                    }
                    showPatientList(patients);
                    //patient list added
                    cout << "\nCurrent Patient List:\n";
                    showPatientList(patients);
                    cout << endl;

                    int patientID_inc;
                    cout << "\nEnter the ID of the patient (0 to return): ";
                    while (!(cin >> patientID_inc)) {
                        cout << "Invalid input. Enter a number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    if (patientID_inc == 0) break;

                    {
                        auto it = find_if(patients.begin(), patients.end(), [patientID_inc](Patient& p) { return p.getPatientID() == patientID_inc; });
                        if (it == patients.end()) {
                            cout << "Patient ID not found.\n";
                            wait(); break;
                        }

                        cout << "\nThis is the patient's current information\n\n";
                        cout << *it;

                        char confirm;
                        cout << "Are you sure you want to increase this patient's age? Confirm? (Y or N): ";
                        cin >> confirm;
                        if (confirm == 'Y' || confirm == 'y') {
                            ++(*it); // use overloaded ++ operator
                            cout << "\nPatient successfully updated.\n\n";
                            cout << "This is the patient's updated information:\n\n";
                            cout << *it;
                        }
                        else {
                            cout << "Operation cancelled.\n";
                        }
                        wait();
                    }
                    break;

                case 9: // Return to Main Menu
                    break;
                }

            } while (patientChoice != 9);
        } break;

        case 2: { //employees
            int empChoice = 0;
            do {
                printEmployeeMenu();
                cin >> empChoice;
                while (cin.fail() || empChoice < 1 || empChoice > 2) {
                    cout << "Error: invalid selection. Please choose again: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cin >> empChoice;
                }

                switch (empChoice) {
                case 1:
                    system("cls");
                    sortEmployees(nurses, nurseCount);
                    sortEmployees(aides, aideCount);
                    sortEmployees(caseManagers, caseManagerCount);

                    cout << "--------------------------------------------------------------------------------------------------\n";
                    cout << setw(60) << "Healthcare Options, Inc." << "\n";
                    cout << setw(54) << "Employee List" << "\n";
                    cout << "--------------------------------------------------------------------------------------------------\n";

                    cout << "Nurses:\n";
                    cout << "          "
                        << std::left << setw(10) << "ID"
                        << setw(30) << "Employee Name"
                        << setw(15) << "Hourly Wage"
                        << setw(20) << "Designation" << "\n";
                    cout << "--------------------------------------------------------------------------------------------------\n";
                    for (int i = 0; i < nurseCount; ++i) nurses[i]->printDetails(cout);
                    cout << "--------------------------------------------------------------------------------------------------\n";

                    cout << "\nAides:\n";
                    cout << "          "
                        << std::left << setw(10) << "ID"
                        << setw(30) << "Employee Name"
                        << setw(15) << "Hourly Wage"
                        << setw(20) << "Certification" << "\n";
                    cout << "--------------------------------------------------------------------------------------------------\n";
                    for (int i = 0; i < aideCount; ++i) aides[i]->printDetails(cout);
                    cout << "--------------------------------------------------------------------------------------------------\n";

                    cout << "\nCase Managers:\n";
                    cout << "          "
                        << std::left << setw(10) << "ID"
                        << setw(30) << "Employee Name"
                        << setw(15) << "Salary"
                        << setw(20) << "Degree" << "\n";
                    cout << "--------------------------------------------------------------------------------------------------\n";
                    for (int i = 0; i < caseManagerCount; ++i) caseManagers[i]->printDetails(cout);

                    cout << "--------------------------------------------------------------------------------------------------\n";
                    cout << setw(calculateOffset("End of Report") + 8) << right << "End of Report" << endl;
                    cout << "--------------------------------------------------------------------------------------------------\n";
                    wait();
                    break;

                case 2: //return to Main Menu
                    break;
                }
            } while (empChoice != 2);
        } break;

        case 3: { //equipment
            equipmentMenu(equipmentList);
        } break;

        case 4: //exit program
            cout << left << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
            cout << setw(43) << right << "Lab 1 Hospital, Inc." << endl;
            cout << setw(40) << right << "Thank You!" << endl;
            cout << left << setfill('-') << setw(70) << "-" << setfill(' ') << endl << endl;
            wait();
            system("cls");
            break;
        }
    } while (mainChoice != 4);

    //free dynamic memory
    if (nurses != nullptr) {
        for (int i = 0; i < nurseCount; i++) { delete nurses[i]; nurses[i] = nullptr; }
        delete[] nurses; nurses = nullptr;
    }

    if (aides != nullptr) {
        for (int i = 0; i < aideCount; i++) { delete aides[i]; aides[i] = nullptr; }
        delete[] aides; aides = nullptr;
    }

    if (caseManagers != nullptr) {
        for (int i = 0; i < caseManagerCount; i++) { delete caseManagers[i]; caseManagers[i] = nullptr; }
        delete[] caseManagers; caseManagers = nullptr;
    }

    if (!equipmentList.empty()) {
        for (auto& eq : equipmentList) { delete eq; eq = nullptr; }
        equipmentList.clear();
    }

    return 0;
}
//for generating unique patientid
int generateUniquePatientID(const std::vector<Patient>& patients, std::mt19937& gen, std::uniform_int_distribution<int>& dis) {
    int id;
    bool unique;
    do {
        id = dis(gen);
        unique = std::none_of(patients.begin(), patients.end(), [&](const Patient& p) { return p.getPatientID() == id; });
    } while (!unique);
    return id;
}

//for unique visitid
void validateUniqueVisitID(Patient& patient, int visitID) {
    for (int i = 0; i < patient.getNumVisits(); ++i) {
        if (patient.getVisit(i).getVisitID() == visitID)
            throw DuplicateIDException("Duplicate Visit ID. Please enter a unique ID.");
    }
}


//display main menu
void printMainMenu() {
    system("cls");
    const string company = "Health Care Options, Inc.";
    const string title = "Patient Management";

    printHeader(cout, company, title);

    cout << "\t\t1. Patients" << endl;
    cout << "\t\t2. Employees" << endl;
    cout << "\t\t3. Equipment" << endl;
    cout << "\t\t4. Exit\n\n";
    cout << "\t\tEnter choice: ";
}

//print patient sub menu
void printPatientMenu() {
    system("cls");
    const string company = "Health Care Options, Inc.";
    const string title = "Patient Management";

    printHeader(cout, company, title);

    cout << "\t\t1. Add new patient manually" << endl;
    cout << "\t\t2. Read patient data from file" << endl;
    cout << "\t\t3. Delete existing patient" << endl;
    cout << "\t\t4. Create visit for patient" << endl;
    cout << "\t\t5. Assign case manager to patient" << endl;
    cout << "\t\t6. Print patient report" << endl;
    cout << "\t\t7. Save patient report" << endl;
    cout << "\t\t8. Increase patient age" << endl;
    cout << "\t\t9. Return to Main Menu\n\n";
    cout << "\t\tEnter selection: ";
}

//print employee sub menu
void printEmployeeMenu() {
    system("cls");
    const string company = "Health Care Options, Inc.";
    const string title = "Employee Management";

    printHeader(cout, company, title);

    cout << "\t\t1. Print employee report" << endl;
    cout << "\t\t2. Return to Main Menu\n\n";
    cout << "\t\tEnter selection: ";
}

//print equipment sub menu
void printEquipmentMenu() {
    system("cls");
    const string company = "Health Care Options, Inc.";
    const string title = "Equipment Management";

    printHeader(cout, company, title);

    cout << "\t\t1. Print equipment list" << endl;
    cout << "\t\t2. Produce depreciation schedule" << endl;
    cout << "\t\t3. Update storage unit information" << endl;
    cout << "\t\t4. Add equipment to storage unit" << endl;
    cout << "\t\t5. View storage unit information" << endl;
    cout << "\t\t6. Exit\n\n";
    cout << "\t\tEnter selection: ";
}


//display patient list sorted by first name
void showPatientList(const vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients available.\n";
        return;
    }

    vector<Patient> sortedPatients = patients;
    sort(sortedPatients.begin(), sortedPatients.end(), [](const Patient& a, const Patient& b) {
        return a < b;  // overloaded < compares first names
        });

    cout << "ID\tPatient Name\n";
    cout << "--------------------------------------\n";
    for (const auto& p : sortedPatients) {
        cout << p.getPatientID() << "\t" << p.getFirstName() << " " << p.getLastName() << "\n";
    }
}

//helper function
int numEmployees(const string& fileName) {
    int employeeID;
    string firstName, lastName, string1;
    float value1;
    int numEmps = 0;

    ifstream inFile(fileName);
    if (!inFile) {
        cout << "The " + fileName + " file did not load correctly. Please fix the file and restart the program." << endl;
        return 0;
    }

    while (!inFile.eof()) {
        inFile >> employeeID;
        inFile.ignore();
        getline(inFile, firstName);
        getline(inFile, lastName);
        inFile >> value1;
        inFile.ignore();
        getline(inFile, string1);
        numEmps++;
    }

    inFile.close();
    return numEmps;
}

// Load Equipment from file
void loadEquipment(vector<Equipment*>& equipment, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    while (!inFile.eof()) {
        int id, life;
        string name, date, displayOp;
        double cost, salvage;

        if (!(inFile >> id)) break;
        inFile.ignore();
        getline(inFile, name);
        getline(inFile, date);
        inFile >> cost >> life >> salvage;
        inFile.ignore();
        getline(inFile, displayOp);

        Equipment* e;
        if (life <= 5)
            e = new Monitor(id, name, date, cost, life, salvage, displayOp);
        else
            e = new Mobility(id, name, date, cost, life, salvage, displayOp);

        equipment.push_back(e);
    }

    inFile.close();
}


//display equipment list
void showEquipment(const vector<Equipment*>& equipment) {
    if (equipment.empty()) {
        cout << "No equipment available.\n";
        return;
    }

    //sort equipment by ID
    vector<Equipment*> sortedEquipment = equipment;
    sort(sortedEquipment.begin(), sortedEquipment.end(), [](Equipment* a, Equipment* b) {
        return *a < *b;
        });

    //print table header
    cout << left
        << setw(5) << "ID"
        << setw(25) << "Name"
        << setw(12) << "Date"
        << right
        << setw(10) << "Cost"
        << setw(6) << "Life"
        << setw(10) << "Salvage"
        << "  Display/Operation" << endl;

    cout << string(80, '-') << endl;

    //print each equipment row
    for (auto e : sortedEquipment) {
        cout << left
            << setw(5) << e->getEquipmentID()
            << setw(25) << e->getEquipmentName()
            << setw(12) << e->getPurchaseDate()
            << right
            << setw(10) << fixed << setprecision(2) << e->getOriginalCost()
            << setw(6) << e->getUsefulLife()
            << setw(10) << e->getSalvageValue()
            << "  ";

        //display/operation field
        string displayOrOperation;
        if (Monitor* m = dynamic_cast<Monitor*>(e)) {
            displayOrOperation = m->getDisplayType();
        }
        else if (Mobility* m = dynamic_cast<Mobility*>(e)) {
            displayOrOperation = m->getOperationMode();
        }

        cout << left << displayOrOperation << endl;
    }
}


//equipment menu
void equipmentMenu(vector<Equipment*>& equipment) {
    StorageUnit<Mobility> mobilityUnit;
    StorageUnit<Monitor> monitorUnit;

    int choice;
    const string company = "Health Care Options, Inc.";
    const string title = "Equipment Management";

    do {
        system("cls");
        printHeader(cout, company, title);
        cout << "\t\t1. Print equipment list" << endl;
        cout << "\t\t2. Produce depreciation schedule" << endl;
        cout << "\t\t3. Update storage unit information" << endl;
        cout << "\t\t4. Add equipment to storage unit" << endl;
        cout << "\t\t5. View storage unit information" << endl;
        cout << "\t\t6. Exit\n\n";
        cout << "\t\tEnter selection: ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 6) {
            cout << "\t\tError: Invalid selection. Please choose again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }

        switch (choice) 
        {
        case 1:
            system("cls");
            printHeader(cout, company, "Equipment List");
            showEquipment(equipment);
            wait();
            break;
        case 2: {
            system("cls"); 
            if (equipment.empty()) {
                cout << "No equipment available.\n";
                wait();
                break;
            }

            printHeader(cout, company, "Equipment List");
            showEquipment(equipment);

            cout << "\nEnter Equipment ID for depreciation: ";
            int eqID;
            cin >> eqID;

            auto it = find_if(equipment.begin(), equipment.end(),
                [eqID](Equipment* e) { return e->getEquipmentID() == eqID; });

            if (it != equipment.end()) {
                Equipment* e = *it;

                system("cls"); //clear screen before showing depreciation schedule

                const int width = 80; // total width for formatting
                printHeader(cout, company, "Equipment List");

                //header
                cout << string(width, '-') << endl;
                cout << setw((width + company.length()) / 2) << company << endl;
                cout << setw((width + title.length()) / 2) << title << endl;
                cout << string(width, '-') << endl << endl;

                //dynamic depreciation title
                string depType;
                if (dynamic_cast<Monitor*>(e))
                    depType = "Straight-line Depreciation";
                else if (dynamic_cast<Mobility*>(e))
                    depType = "Double-Declining Balance Depreciation";

                cout << setw((width + depType.length()) / 2) << depType << "\n\n";

                if (e != nullptr) {
                    cout << setw((width - 40) / 2) << "" << setw(30) << left << "Equipment ID:" << e->getEquipmentID() << endl;
                    cout << setw((width - 40) / 2) << "" << setw(30) << left << "Equipment name:" << e->getEquipmentName() << endl;
                    cout << setw((width - 40) / 2) << "" << setw(30) << left << "Original cost:" << "$" << fixed << setprecision(2) << e->getOriginalCost() << endl;
                    cout << setw((width - 40) / 2) << "" << setw(30) << left << "Salvage value:" << "$" << fixed << setprecision(2) << e->getSalvageValue() << endl;
                    cout << setw((width - 40) / 2) << "" << setw(30) << left << "Useful life (in years):" << e->getUsefulLife() << endl << endl;
                }
                else {
                    cout << "\t\tEquipment not found.\n";
                }

                std::cout << std::setw(10) << ""               // smaller initial padding
                    << std::setw(15) << std::left << "Period"   
                    << std::setw(20) << std::right << "Depreciation Expense ($)"
                    << std::setw(20) << std::right << "Book Value ($)" << std::endl << std::endl;


                
                //depreciation table (handled by virtual function)
                if (e != nullptr) {
                    e->depreciate(cout);
                }
                else {
                    cout << "\t\tError: Equipment pointer is null. Cannot calculate depreciation.\n";
                }
                printFooter(cout);
            }
            else {
                cout << "\t\tEquipment not found.\n";
            }
            wait();
            break;
        }

        case 3: {
            system("cls");
            printHeader(cout, company, "Update Storage Unit Information");

            int unitChoice;
            while (true) {
                cout << "Enter 1 for Mobility Unit, 2 for Monitoring Unit, 0 to exit: ";
                if (cin >> unitChoice) {
                    if (unitChoice >= 0 && unitChoice <= 2) break;  // valid choice
                    else cout << "Invalid choice. Please enter 0, 1, or 2.\n";
                }
                else {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear(); // clear the fail state
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            }
            cin.ignore(); // clear newline after number


            if (unitChoice == 1)
                updateStorageUnit(mobilityUnit);
            else if (unitChoice == 2)
                updateStorageUnit(monitorUnit);
            // 0 just exits
            break;
        }

        case 4: {
            system("cls");
            printHeader(cout, company, "Add Equipment to Storage Unit");

            if (equipment.empty()) {
                cout << "No equipment available.\n";
                wait();
                break;
            }

            // 1. Show equipment list
            showEquipment(equipment);

            int eqID;
            Equipment* selected = nullptr;

            // 2. Prompt user for valid Equipment ID
            while (true) {
                cout << "\nEnter Equipment ID to add: ";
                cin >> eqID;

                auto it = find_if(equipment.begin(), equipment.end(),
                    [eqID](Equipment* e) { return e->getEquipmentID() == eqID; });

                if (it != equipment.end()) {
                    selected = *it;
                    break;
                }
                else {
                    cout << "The ID you entered is not in the system. Please try again.\n";
                }
            }

            // 3. Determine the type of equipment
            string typeName = typeid(*selected).name();

            if (string(typeName) == "class Mobility") {
                if (mobilityUnit.contains(*dynamic_cast<Mobility*>(selected))) {
                    cout << "This item has already been added to a storage unit. Operation cancelled.\n";
                }
                else {
                    mobilityUnit.addEquipment(*dynamic_cast<Mobility*>(selected));

                    // Print Mobility inventory
                    cout << "\nMobility Inventory\n";
                    cout << string(70, '*') << "\n";
                    cout << left
                        << setw(6) << "ID"
                        << setw(25) << "Name"
                        << setw(12) << "Date"
                        << setw(8) << "Cost"
                        << setw(6) << "Life"
                        << setw(8) << "Salvage"
                        << setw(20) << "Display/Operation" << "\n";

                    for (int i = 0; i < mobilityUnit.getInventoryCount(); ++i) {
                        Mobility item = mobilityUnit.getEquipment(i);
                        cout << left
                            << setw(6) << item.getEquipmentID()
                            << setw(25) << item.getEquipmentName()
                            << setw(12) << item.getPurchaseDate()
                            << setw(8) << fixed << setprecision(2) << item.getOriginalCost()
                            << setw(6) << item.getUsefulLife()
                            << setw(8) << item.getSalvageValue()
                            << setw(20) << item.getOperationMode() << "\n";
                    }

                    cout << string(70, '*') << "\n\n";
                    cout << "Equipment successfully added to Mobility storage unit.\n\n";
                }
            }
            else if (string(typeName) == "class Monitor") {
                if (monitorUnit.contains(*dynamic_cast<Monitor*>(selected))) {
                    cout << "This item has already been added to a storage unit. Operation cancelled.\n";
                }
                else {
                    monitorUnit.addEquipment(*dynamic_cast<Monitor*>(selected));

                    // Print Monitor inventory
                    cout << "\nMonitor Inventory\n";
                    cout << string(70, '*') << "\n";
                    cout << left
                        << setw(6) << "ID"
                        << setw(25) << "Name"
                        << setw(12) << "Date"
                        << setw(8) << "Cost"
                        << setw(6) << "Life"
                        << setw(8) << "Salvage"
                        << setw(20) << "Display/Operation" << "\n";

                    for (int i = 0; i < monitorUnit.getInventoryCount(); ++i) {
                        Monitor item = monitorUnit.getEquipment(i);
                        cout << left
                            << setw(6) << item.getEquipmentID()
                            << setw(25) << item.getEquipmentName()
                            << setw(12) << item.getPurchaseDate()
                            << setw(8) << fixed << setprecision(2) << item.getOriginalCost()
                            << setw(6) << item.getUsefulLife()
                            << setw(8) << item.getSalvageValue()
                            << setw(20) << item.getDisplayType() << "\n";
                    }

                    cout << string(70, '*') << "\n\n";
                    cout << "Equipment successfully added to Monitor storage unit.\n\n";
                }
            }
            else {
                cout << "Unknown equipment type. Operation cancelled.\n";
            }

            wait();  // Pause before returning to submenu
            break;
        }

       case 5: {
           system("cls");
           printHeader(cout, company, "View Storage Unit Information");

           int unitChoice;
           while (true) {
               cout << "Enter 1 for Mobility Unit, 2 for Monitoring Unit, 0 to exit: ";
               if (cin >> unitChoice) {
                   if (unitChoice >= 0 && unitChoice <= 2) break;  // valid choice
                   else cout << "Invalid choice. Please enter 0, 1, or 2.\n";
               }
               else {
                   cout << "Invalid input. Please enter a number.\n";
                   cin.clear(); // clear the fail state
               }
               cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
           }
           cin.ignore(); // clear newline after number


           if (unitChoice == 0) break;

           if (unitChoice == 1) {
               system("cls");
               printHeader(cout, company, "Storage Unit Information");
               mobilityUnit.printUnitInformation();
               mobilityUnit.sortInventory();   // Sort inventory before displaying
               mobilityUnit.printInventory();
           }
           else if (unitChoice == 2) {
               system("cls");
               printHeader(cout, company, "Storage Unit Information");
               monitorUnit.printUnitInformation();
               monitorUnit.sortInventory();    // Sort inventory before displaying
               monitorUnit.printInventory();
           }
           else {
               cout << "\t\tInvalid selection. Returning to menu...\n";
           }

           cout << "\n\t\tPress the Enter key to continue ...";
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
           cin.get();
           break;
       }



        case 6:
            break; //return to main menu
        }
    } while (choice != 6);
}


//employee functions for dynamic arrays
template<typename T>
void loadEmployeeData(T**& arr, int& count, const string& filename) {
    count = numEmployees(filename);   //first pass count rows

    if (count == 0) {
        arr = nullptr;
        return;
    }

    arr = new T * [count];              //allocate array of pointers

    ifstream inFile(filename);        //second pass actually read data
    int id;
    string first, last, extra;
    float value;

    for (int i = 0; i < count; i++) {
        inFile >> id;
        inFile.ignore();
        getline(inFile, first);
        getline(inFile, last);
        inFile >> value;
        inFile.ignore();
        getline(inFile, extra);

        arr[i] = new T(id, first, last, value, extra);
    }

    inFile.close();
}

template<typename T>
void showEmployees(T** arr, int count) {
    cout << left << setw(25) << "Name" << setw(10) << "ID" << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < count; ++i) {
        cout << setw(25) << (arr[i]->getEmpFirstName() + " " + arr[i]->getEmpLastName())
            << setw(10) << arr[i]->getEmployeeID() << endl;
    }
}

template<typename T>
void sortEmployees(T** arr, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (arr[i]->getEmpLastName() > arr[j]->getEmpLastName()) {
                T* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

template<typename T>
int findEmployee(int id, T** arr, int count) {
    for (int i = 0; i < count; ++i) {
        if (arr[i]->getEmployeeID() == id) return i;
    }
    return -1;
}

//template function to update any StorageUnit
template <typename T>
void updateStorageUnit(StorageUnit<T>& unit) {
    system("cls");

    int id, length, width, height;
    double cost;
    std::string desc, dateStr;
    char autoRenew, humidity;

    // ID input
    while (true) {
        std::cout << "Enter the ID of the Storage Unit: ";
        if (std::cin >> id) {
            try { unit.setID(id); break; }
            catch (NegativeNumberException& e) { std::cout << e.what() << " Try again.\n"; }
        }
        else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cin.ignore();

    // Description
    std::cout << "Enter the description for the Storage Unit: ";
    std::getline(std::cin, desc);
    unit.setDescription(desc);

    // Length input
    while (true) {
        std::cout << "Enter the length of the unit (in feet): ";
        if (std::cin >> length) {
            try { unit.setLength(length); break; }
            catch (NegativeNumberException& e) { std::cout << e.what() << " Try again.\n"; }
        }
        else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Width input
    while (true) {
        std::cout << "Enter the width of the unit (in feet): ";
        if (std::cin >> width) {
            try { unit.setWidth(width); break; }
            catch (NegativeNumberException& e) { std::cout << e.what() << " Try again.\n"; }
        }
        else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Height input
    while (true) {
        std::cout << "Enter the height of the unit (in feet): ";
        if (std::cin >> height) {
            try { unit.setHeight(height); break; }
            catch (NegativeNumberException& e) { std::cout << e.what() << " Try again.\n"; }
        }
        else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Cost input
    while (true) {
        std::cout << "Enter the cost per month to rent the unit: ";
        if (std::cin >> cost) {
            try { unit.setCostPerMonth(cost); break; }
            catch (NegativeNumberException& e) { std::cout << e.what() << " Try again.\n"; }
        }
        else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cin.ignore();

    // Date rented input with loop for validation
    Date d;
    bool validDate = false;
    while (!validDate) {
        std::cout << "Enter the date rented (MM/DD/YYYY): ";
        std::getline(std::cin, dateStr);

        try {
            int m, day, y;
            Visit::tokenizeDate(const_cast<char*>(dateStr.c_str()), m, day, y);

            // Range validation
            if (m < 1 || m > 12) throw std::invalid_argument("Month must be 1-12.");
            if (day < 1 || day > 31) throw std::invalid_argument("Day must be 1-31.");
            if (y < 1000 || y > 9999) throw std::invalid_argument("Year must be 4 digits.");

            d.setDate(m, day, y);
            unit.setDateRented(d);
            validDate = true;
        }
        catch (const std::exception& e) {
            std::cout << "Invalid date entered: " << e.what() << "\nPlease re-enter.\n";
        }
    }

    // Auto-renew
    std::cout << "Does the contract auto-renew? (Y/N): ";
    std::cin >> autoRenew;
    unit.setAutoRenew(tolower(autoRenew) == 'y');

    // Humidity-controlled
    std::cout << "Is the unit humidity-controlled? (Y/N): ";
    std::cin >> humidity;
    unit.setHumidityControlled(tolower(humidity) == 'y');

    // Clear screen and display updated info
    system("cls");
    std::cout << "Storage Unit updated successfully.\n\n";
    std::cout << "Storage Unit Information\n\n";
    std::cout << std::left;
    std::cout << std::setw(25) << "Unit ID:" << unit.getID() << "\n";
    std::cout << std::setw(25) << "Description:" << unit.getDescription() << "\n";
    std::cout << "Dimensions\n";
    std::cout << std::setw(25) << "Length:" << unit.getLength() << " feet\n";
    std::cout << std::setw(25) << "Width:" << unit.getWidth() << " feet\n";
    std::cout << std::setw(25) << "Height:" << unit.getHeight() << " feet\n\n";
    std::cout << "**Unit is " << (unit.isHumidityControlled() ? "" : "not ") << "humidity controlled.\n\n";
    std::cout << "Rental Contract\n";
    std::cout << std::setw(25) << "Cost Per Month: $" << unit.getCostPerMonth() << "\n";
    std::cout << std::setw(25) << "Date Signed: " << unit.getDateRented() << "\n\n";
    std::cout << "**Contract " << (unit.isAutoRenew() ? "does" : "does not") << " auto-renew.\n\n";

    std::cout << "Press the Enter key to continue ...";
    std::cin.ignore();
    std::cin.get();
}


//clears the input buffer
void clearCin() {
    if (cin.rdbuf()->in_avail() > 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

//pauses program until Enter
void wait() {
    clearCin();
    char ch;
    cout << endl << INDENT << "Press the Enter key to continue ... ";
    cin.get(ch);
}

//prints report header
void printHeader(ostream& out, const string& company, const string& title) {
    out << string(SCREEN_WIDTH, '-') << endl << endl;
    out << setw(calculateOffset(company)) << right << company << endl;
    out << setw(calculateOffset(title)) << right << title << endl << endl;
    out << string(SCREEN_WIDTH, '-') << endl << endl;
}

//prints report footer
void printFooter(ostream& out) {
    out << string(SCREEN_WIDTH, '-') << endl << endl;
    out << setw(calculateOffset("End of Report")) << right << "End of Report" << endl << endl;
    out << string(SCREEN_WIDTH, '-') << endl << endl;
}


//inputs patient info
Patient editPatients() {
    Patient p;
    string firstName, lastName, streetAddress;
    int age, numBpm;
    float height, weight;
    char gender, ambInput;
    bool ambulatory;

    cout << left << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
    cout << setw(40) << right << "Patient Information" << endl;
    cout << left << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    clearCin();
    cout << "\t\tFirst name:  ";
    getline(cin, firstName);
    p.setFirstName(firstName);

    cout << "\t\tLast name:  ";
    getline(cin, lastName);
    p.setLastName(lastName);

    cout << "\t\tStreet address:  ";
    getline(cin, streetAddress);
    p.setStreetAddress(streetAddress);

    while (true) {
        cout << "\t\tAge:  ";
        cin >> age;
        if (cin.fail() || !p.setAge(age)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Enter a valid number between 1 and 120.\n";
        }
        else break;
    }

    while (true) {
        cout << "\t\tHeight (in inches):  ";
        cin >> height;
        if (cin.fail() || !p.setHeight(height)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Enter a positive number for height.\n";
        }
        else break;
    }

    while (true) {
        cout << "\t\tWeight (in pounds):  ";
        cin >> weight;
        if (cin.fail() || !p.setWeight(weight)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Enter a positive number for weight.\n";
        }
        else break;
    }

    while (true) {
        cout << "\t\tGender (M or F):  ";
        cin >> gender;
        gender = toupper(gender);
        if (!p.setGender(gender)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Enter 'M' or 'F'.\n";
        }
        else break;
    }

    while (true) {
        cout << "\t\tIs the patient ambulatory (Y or N):  ";
        cin >> ambInput;
        if (ambInput == 'Y' || ambInput == 'y') ambulatory = true;
        else if (ambInput == 'N' || ambInput == 'n') ambulatory = false;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Enter 'Y' or 'N'.\n";
            continue;
        }
        p.setIsAmbulatory(ambulatory);
        break;
    }

    p.setPatientID(rand() % 100 + 1);

    while (true) {
        cout << "\t\tHow many heart rate (bpm) readings will be entered? ";
        cin >> numBpm;
        if (cin.fail() || numBpm < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Enter a positive integer.\n";
        }
        else break;
    }

    for (int i = 0; i < numBpm; ++i) {
        int value;
        while (true) {
            cout << "\t\tBPM Reading #" << i + 1 << ":  ";
            cin >> value;
            if (cin.fail() || value <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error: Enter a positive number for BPM.\n";
            }
            else {
                p.addBpmReading(value);
                break;
            }
        }
    }

    return p;
}

//read patient from file
bool inputPatient(Patient& p, const string& fileName, size_t currentPatientCount) {
    if (currentPatientCount >= MAX_PATIENTS) {
        cout << "Error: Cannot add more patients. Maximum of " << MAX_PATIENTS << " reached.\n";
        return false;
    }

    ifstream input(fileName);
    if (!input) {
        cout << "File could not be opened. Please fix the problem and try again.\n\n";
        return false;
    }

    string firstName, lastName, street;
    int age;
    float height, weight;
    char gender, ambInput;
    bool ambulatory;

    if (!getline(input, firstName)) { input.close(); return false; }
    if (!getline(input, lastName)) { input.close(); return false; }
    if (!getline(input, street)) { input.close(); return false; }
    if (!(input >> age)) { input.close(); return false; }
    if (!(input >> height)) { input.close(); return false; }
    if (!(input >> weight)) { input.close(); return false; }
    input >> gender; gender = toupper(gender);
    if (!p.setGender(gender)) { input.close(); return false; }
    input >> ambInput;
    if (ambInput == 'Y' || ambInput == 'y') ambulatory = true;
    else if (ambInput == 'N' || ambInput == 'n') ambulatory = false;
    else { cout << "Error: Invalid ambulatory status in file.\n"; input.close(); return false; }

    p.setFirstName(firstName);
    p.setLastName(lastName);
    p.setStreetAddress(street);
    if (!p.setAge(age)) { input.close(); return false; }
    if (!p.setHeight(height)) { input.close(); return false; }
    if (!p.setWeight(weight)) { input.close(); return false; }
    p.setIsAmbulatory(ambulatory);
    p.setPatientID(rand() % 100 + 1);

    int bpm;
    while (input >> bpm) {
        if (bpm > 0) p.addBpmReading(bpm);
    }

    if (p.getBpmCount() == 0) {
        cout << "Error: No BPM readings found in file.\n";
        input.close();
        return false;
    }

    cout << "File successfully opened and patient imported.\n\n";
    input.close();
    return true;
}

//delete patient by ID
void deletePatient(vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients to delete.\n";
        return;
    }

    int id;
    cout << "Enter the ID of the patient to remove:  ";
    cin >> id;

    auto it = find_if(patients.begin(), patients.end(), [id](const Patient& p) {
        return p.getPatientID() == id;
        });

    if (it == patients.end()) {
        cout << "Patient ID not found.\n";
        return;
    }

    //overload changes (before: it->printPatientDetails(cout);
    cout << *it;

    char confirm;
    cout << "\t\tThis patient was selected for removal. Confirm? (Y or N): ";
    cin >> confirm;
    if (confirm == 'Y' || confirm == 'y') {
        patients.erase(it);
        cout << "\t\tPatient successfully removed\n";
    }
    else {
        cout << "\t\tOperation cancelled\n";
    }
}

//calculate center offset for formatting
int calculateOffset(const string& s) {
    return SCREEN_WIDTH / 2 + s.size() / 2;
}
