#ifndef BIGREAL_H
#define BIGREAL_H

#include <string>
#include <iostream>

class BigReal {
private:
    std::string integerPart;  // Stores the integer part of the real number
    std::string fractionPart; // Stores the fraction part of the real number
    bool negative;            // Stores the sign of the real number
    int decimalPlace;         // Stores the position of the decimal point

    // Helper function to remove leading zeros from a string
    std::string removeLeadingZeros(const std::string& str) {
        std::string result = str;
        result.erase(0, result.find_first_not_of('0'));
        return result;
    }

    // Helper function to align decimal places of two BigReal objects
    void alignDecimalPlaces(BigReal& other) {
        if (decimalPlace < other.decimalPlace) {
            std::string zeros(other.decimalPlace - decimalPlace, '0');
            fractionPart = zeros + fractionPart;
            decimalPlace = other.decimalPlace;
        }
        else if (decimalPlace > other.decimalPlace) {
            std::string zeros(decimalPlace - other.decimalPlace, '0');
            other.fractionPart = zeros + other.fractionPart;
            other.decimalPlace = decimalPlace;
        }
    }

public:
    BigReal(double realNumber = 0.0); // Default constructor
    BigReal(const std::string& realNumber); // Initialize from string
    BigReal(const BigReal& other); // Copy constructor
    BigReal& operator=(const BigReal& other); // Assignment operator

    void setNum(const std::string& realNumber); // Set the value of the BigReal object

    int size() const; // Returns the total number of digits in the BigReal object
    int sign() const; // Returns -1 for negative, 0 for zero, and 1 for positive

    BigReal operator+(const BigReal& other) const; // Addition operator
    BigReal operator-(const BigReal& other) const; // Subtraction operator
    bool operator<(const BigReal& anotherReal) const; // Less than operator
    bool operator>(const BigReal& anotherReal) const; // Greater than operator
    bool operator==(const BigReal& anotherReal) const; // Equality operator

    friend std::ostream& operator<<(std::ostream& out, const BigReal& num); // Output stream operator
};

#endif // BIGREAL_H