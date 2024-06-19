// CPPSimpleConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CPPSimpleConsole.h"
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

int main()
{
    PrintHelloWorld();
    cout << "Date in ISO format: " << PrintDateInISOFormat() << endl;
    FindSubstringInString("world", "Hello world!");
    cout << "Sum of 2 numbers: " << CalculateSumOfTwoNumbers(5.34, 10.49) << endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

void PrintHelloWorld()
{
    cout << "Hello World!\n";
}

string PrintDateInISOFormat()
{
    // Get current time
    time_t now = time(nullptr);

    // Convert to tm struct
    struct tm timeinfo;
    errno_t err = localtime_s(&timeinfo, &now);

    if (err) {
        // Handle error (if any)
        return "";
    }

    // Create stringstream to format the date
    ostringstream oss;
    oss << put_time(&timeinfo, "%Y-%m-%dT%H:%M:%S");

    // Append 'Z' to denote UTC time
    oss << "Z";

    return oss.str();
}

void FindSubstringInString(string subString, string stringToSearch)
{
    if (stringToSearch.find(subString) != string::npos)
    {
        cout << "Substring '" << subString << "' found in the given string\n";
    }
    else
    {
        cout << "Substring not found in string\n";
    }
}

double CalculateSumOfTwoNumbers(double firstNumber, double secondNumber)
{
    return firstNumber + secondNumber;
}
