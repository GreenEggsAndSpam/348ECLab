/*
Name: Vrishank Kulkarni 
ID: 3115417
Class: EECS 348 EC Lab
Lab time: Wednesday 1-2:50

Objectives: This program is a C++ program that reads a string from the user and extracts a valid double-precision 
floating-point number from it without using library functions like std::stod. The program should handle potential 
errors in the input and provide clear feedback to the user.
 */


#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

double extractNumeric(const string& str) {
    bool hasDecimal = false; //track if a decimal point is there
    bool hasSign = false;    //track +/-
    bool isValid = true;     //track if the input is valid
    int digitCount = 0;      
    double result = 0.0;     
    double decimalMultiplier = 0.1; //multiplier for digits after the decimal
    bool isNegative = false; 

    size_t i = 0;

    //check for the sign at the beginning
    if (str[i] == '+' || str[i] == '-') {
        hasSign = true;
        if (str[i] == '-') {
            isNegative = true;
        }
        i++;
    }

    while (i < str.length()) {
        char ch = str[i];

        if (isdigit(ch)) {
            digitCount++;
            if (!hasDecimal) {
                //building the integer part
                result = result * 10 + (ch - '0');
            } else {
                //building the fractional part
                result += (ch - '0') * decimalMultiplier;
                decimalMultiplier /= 10;
            }
        } else if (ch == '.') {
            //only one decimal point allowed
            if (hasDecimal) {
                isValid = false;
                break;
            }
            hasDecimal = true;
        } else {
            //invalid character
            isValid = false;
            break;
        }
        i++;
    }

    //if input invalid return this number
    if (!isValid || digitCount == 0) {
        return -999999.99;
    }

    if (isNegative) {
        result = -result;
    }
    return result;
}


int main() {
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric(input);

        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}
