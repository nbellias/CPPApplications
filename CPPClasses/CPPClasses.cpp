// CPPClasses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Department.h"
#include "Project.h"
#include <vector>
#include "Employee.h"
#include "CPPClasses.h"

using namespace std;

int main()
{
    // Create Departments
    Department dept1(1, "HR");
    Department dept2(2, "Engineering");

    // Create Projects
    Project proj1(101, "Project Alpha");
    Project proj2(102, "Project Beta");

    // Create Employees
    Employee emp1(1, "Alice", &dept1);
    Employee emp2(2, "Bob", &dept2);
    Employee emp3(3, "Charlie", &dept2);

    // Assign Projects to Employees
    emp1.addProject(&proj1);
    emp2.addProject(&proj1);
    emp2.addProject(&proj2);
    emp3.addProject(&proj2);

    // Create Vectors
    vector<Department> departments = { dept1, dept2 };
    vector<Project> projects = { proj1, proj2 };
    vector<Employee> employees = { emp1, emp2, emp3 };

    string filename = "employee_projects.csv";
    writeCSV(employees, filename);

    cout << "CSV file created successfully." << endl;

    std::cout << "\nContents of the CSV file:\n";
    readAndPrintCSV(filename);

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
