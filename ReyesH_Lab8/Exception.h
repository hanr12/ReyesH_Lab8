//Hannah Reyes
//CSCN 112 - Templates and Exceptions Instructions
// 11/29/2025
#pragma once
#include <stdexcept>
#include <string>

//thrown when a negative number is passed where it isn't allowed
class NegativeNumberException : public std::runtime_error {
public:
    NegativeNumberException(const std::string& msg = "Only positive numbers are allowed.")
        : std::runtime_error(msg) {}
};

//thrown when a duplicate ID is detected
class DuplicateIDException : public std::runtime_error {
public:
    DuplicateIDException(const std::string& msg = "This ID already exists.")
        : std::runtime_error(msg) {}
};

//thrown when an invalid date format is encountered
class InvalidDateException : public std::runtime_error {
public:
    InvalidDateException(const std::string& msg = "Invalid date format.")
        : std::runtime_error(msg) {}
};
