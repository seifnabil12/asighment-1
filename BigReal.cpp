#include <iostream>
#include <string>
#include <algorithm>
#include "BigReal.h"

BigReal::BigReal(double realNumber) {
    setNum(std::to_string(realNumber));
}

BigReal::BigReal(const std::string& realNumber) {
    setNum(realNumber);
}

BigReal::BigReal(const BigReal& other) {
    integerPart = other.integerPart;
    fractionPart = other.fractionPart;
    negative = other.negative;
    decimalPlace = other.decimalPlace;
}

BigReal& BigReal::operator=(const BigReal& other) {
    if (this != &other) {
        integerPart = other.integerPart;
        fractionPart = other.fractionPart;
        negative = other.negative;
        decimalPlace = other.decimalPlace;
    }
    return *this;
}

void BigReal::setNum(const std::string& realNumber) {
    if (realNumber.empty()) {
        std::cout << "Invalid input: Empty string\n";
        return;
    }

    std::string trimmedStr = realNumber;
    trimmedStr.erase(std::remove(trimmedStr.begin(), trimmedStr.end(), ' '), trimmedStr.end());

    if (trimmedStr[0] == '-') {
        negative = true;
        trimmedStr = trimmedStr.substr(1);
    }

    size_t decimalPos = trimmedStr.find('.');
    if (decimalPos == std::string::npos) {
        integerPart = removeLeadingZeros(trimmedStr);
        fractionPart = "0";
        decimalPlace = 0;
    }
    else {
        integerPart = removeLeadingZeros(trimmedStr.substr(0, decimalPos));
        fractionPart = removeLeadingZeros(trimmedStr.substr(decimalPos + 1));
        decimalPlace = fractionPart.length();
    }
}

int BigReal::size() const {
    return integerPart.length() + fractionPart.length();
}

int BigReal::sign() const {
    if (integerPart == "0" && fractionPart == "0") {
        return 0; // Zero
    }
    else if (negative) {
        return -1; // Negative
    }
    else {
        return 1; // Positive
    }
}
BigReal BigReal::operator+(const BigReal& other) const {
    BigReal result;
    result.alignDecimalPlaces(const_cast<BigReal&>(*this));
    result.alignDecimalPlaces(const_cast<BigReal&>(other));

    bool negative;
    if (negative == other.negative) {
        result.negative = negative;

        // Perform addition of integer parts
        int carry = 0;
        int i = integerPart.length() - 1;
        int j = other.integerPart.length() - 1;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;

            if (i >= 0) {
                sum += integerPart[i] - '0';
                i--;
            }

            if (j >= 0) {
                sum += other.integerPart[j] - '0';
                j--;
            }

            carry = sum / 10;
            sum %= 10;

            result.integerPart = std::to_string(sum) + result.integerPart;
        }

        // Perform addition of fraction parts
        int decimalPos = result.integerPart.length() - result.decimalPlace;
        int k = decimalPos + result.decimalPlace - 1;
        int l = decimalPos + other.decimalPlace - 1;
        carry = 0;

        while (k >= decimalPos || l >= decimalPos || carry > 0) {
            int sum = carry;

            if (k >= decimalPos) {
                sum += result.fractionPart[k - decimalPos] - '0';
                k--;
            }

            if (l >= decimalPos) {
                sum += other.fractionPart[l - decimalPos] - '0';
                l--;
            }

            carry = sum / 10;
            sum %= 10;

            result.fractionPart = std::to_string(sum) + result.fractionPart;
        }
    }
    else {
        // Subtract the smaller number from the larger number
        const BigReal* larger;
        const BigReal* smaller;

        if (*this > other) {
            larger = this;
            smaller = &other;
        }
        else {
            larger = &other;
            smaller = this;
        }

        result.negative = larger->negative;

        // Perform subtraction of integer parts
        int borrow = 0;
        int i = larger->integerPart.length() - 1;
        int j = smaller->integerPart.length() - 1;

        while (i >= 0 || j >= 0 || borrow > 0) {
            int diff = borrow;

            if (i >= 0) {
                diff += larger->integerPart[i] - '0';
                i--;
            }

            if (j >= 0) {
                diff -= smaller->integerPart[j] - '0';
                j--;
            }

            borrow = 0;

            if (diff < 0) {
                diff += 10;
                borrow = -1;
            }

            result.integerPart = std::to_string(diff) + result.integerPart;
        }

        // Perform subtraction of fraction parts
        int decimalPos = result.integerPart.length() - result.decimalPlace;
        int k = decimalPos + result.decimalPlace - 1;
        int l = decimalPos + smaller->decimalPlace - 1;
        borrow = 0;

        while (k >= decimalPos || l >= decimalPos || borrow > 0) {
            int diff = borrow;

            if (k >= decimalPos) {
                diff += result.fractionPart[k - decimalPos] - '0';
                k--;
            }

            if (l >= decimalPos) {
                diff -= smaller->fractionPart[l - decimalPos] - '0';
                l--;
            }

            borrow = 0;

            if (diff < 0) {
                diff += 10;
                borrow = -1;
            }

            result.fractionPart = std::to_string(diff) + result.fractionPart;
        }
    }

    // Remove leading zeros from the result
    result.integerPart = result.removeLeadingZeros(result.integerPart);
    result.fractionPart = result.removeLeadingZeros(result.fractionPart);

    return result;
}

BigReal BigReal::operator-(const BigReal& other) const {
    BigReal negOther = other;
    negOther.negative = !negOther.negative;
    return *this + negOther;
}

bool BigReal::operator<(const BigReal& other) const {
    if (negative && !other.negative) {
        return true;
    }
    else if (!negative && other.negative) {
        return false;
    }
    else if (negative && other.negative) {
        if (integerPart.length() > other.integerPart.length()) {
            return true;
        }
        else if (integerPart.length() < other.integerPart.length()) {
            return false;
        }
        else {
            return integerPart < other.integerPart;
        }
    }
    else {
        if (integerPart.length() < other.integerPart.length()) {
            return true;
        }
        else if (integerPart.length() > other.integerPart.length()) {
            return false;
        }
        else {
            return integerPart < other.integerPart;
        }
    }
}

bool BigReal::operator>(const BigReal& other) const {
    return !(*this < other || *this == other);
}

bool BigReal::operator==(const BigReal& other) const {
    return (negative == other.negative) && (integerPart == other.integerPart) && (fractionPart == other.fractionPart);
}

std::ostream& operator<<(std::ostream& os, const BigReal& bigReal) {
    if (bigReal.negative) {
        os << "-";
    }

    os << bigReal.integerPart;

    if (!bigReal.fractionPart.empty()) {
        os << "." << bigReal.fractionPart;
    }

    return os;
}
