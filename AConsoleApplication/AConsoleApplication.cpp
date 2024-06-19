// AConsoleApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <windows.h> // For SetConsoleOutputCP
#include "MyApp.h"
#include "MathLibrary.h"
#include <Login.h>
#include <EventLogger.h>


using namespace std;
using namespace string_demos;

typedef bool (*ValidateCredentialsFunc)(const char*, const char*);

int main()
{
    // Set the console output code page to UTF-8
	SetConsoleOutputCP(CP_UTF8);

	MyApp app;
	
	app.varDeclarations();
    WriteToEventLog("Var Declarations has been run");
	app.printTheFollowingStringLiterals();
    WriteToEventLog("String literals printing has been run");
	app.printWithLocale();
    WriteToEventLog("Printing with locale has been run");
	app.createRandomStrings();
    WriteToEventLog("Random strings printing has been run");

    // Initialize a Fibonacci relation sequence.
    fibonacci_init(1, 1);
    // Write out the sequence values until overflow.
    do {
        cout << fibonacci_index() << ": "
            << fibonacci_current() << endl;
    } while (fibonacci_next());
    // Report count of values written before overflow.
    cout << fibonacci_index() + 1 <<
        " Fibonacci sequence values fit in an " <<
        "unsigned 64-bit integer." << endl;
    WriteToEventLog("Fibonaccis has been run");

    // Validate credentials
    const char* username = "nikolaos";
    const char* password = "nikos1967";

    bool result = ValidateCredentials(username, password);
    if (result) {
        std::cout << "Login successful!" << std::endl;
    }
    else {
        std::cout << "Login failed." << std::endl;
    }
    WriteToEventLog("Login has been run");

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
