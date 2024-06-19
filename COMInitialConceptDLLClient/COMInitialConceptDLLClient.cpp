// COMInitialConceptDLLClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "IPersistence.h"
#include "IDepartment.h"
#include "Department.h"
#include "IEmployee.h"
#include "Employee.h"
#include <vector>
#include <memory>
#include <map>

using namespace std;

int main()
{
    string deptFilename = "departments.dat";
    string empFilename = "employees.dat";

    // Create departments
    vector<unique_ptr<Department>> departments;

    auto dept1 = make_unique<Department>();
    dept1->setId("123e4567-e89b-12d3-a456-426614174000");
    dept1->setName("Engineering");
    dept1->setAddress("123 Tech Lane");
    departments.push_back(move(dept1));

    auto dept2 = make_unique<Department>();
    dept2->setId("789e4567-e89b-12d3-a456-426614174000");
    dept2->setName("HR");
    dept2->setAddress("456 Human Resource Blvd");
    departments.push_back(move(dept2));

    // Create employees
    vector<unique_ptr<Employee>> employees;

    auto emp1 = make_unique<Employee>();
    emp1->setId("456e7890-e12b-34c5-a678-901234567890");
    emp1->setName("Nikolaos Bellias");
    emp1->setDateOfBirth("1990-01-01");
    emp1->setSalary(50000);
    emp1->setDepartment(departments[0].get());
    employees.push_back(move(emp1));

    auto emp2 = make_unique<Employee>();
    emp2->setId("123e7890-e12b-34c5-a678-901234567891");
    emp2->setName("Margarita Papastamou");
    emp2->setDateOfBirth("1985-05-15");
    emp2->setSalary(60000);
    emp2->setDepartment(departments[1].get());
    employees.push_back(move(emp2));

    auto emp3 = make_unique<Employee>();
    emp3->setId("789e7890-e12b-34c5-a678-901234567892");
    emp3->setName("Eleni Fasoula");
    emp3->setDateOfBirth("1975-12-22");
    emp3->setSalary(70000);
    emp3->setDepartment(departments[1].get());
    employees.push_back(move(emp3));

    for (const auto& dept : departments) {
        dept->store(deptFilename);
    }
    cout << "Departments stored successfully." << endl;

    for (const auto& emp : employees) {
        emp->store(empFilename);
    }
    cout << "Employees stored successfully." << endl;

    // Retrieve and print departments
    vector<unique_ptr<IDepartment>> retrievedDepartments;

    for (const auto& dept : departments) {
        auto retrievedDept = make_unique<Department>();
        retrievedDept->retrieveById(dept->getId(), deptFilename);
        retrievedDepartments.push_back(move(retrievedDept));
    }

    cout << "\nRetrieved Departments:" << endl;
    for (const auto& dept : retrievedDepartments) {
        dept->printDepartment();
    }

    // Retrieve and print employees
    vector<unique_ptr<IEmployee>> retrievedEmployees;

    for (const auto& emp : employees) {
        auto retrievedEmp = make_unique<Employee>();
        retrievedEmp->retrieveById(emp->getId(), empFilename);
        retrievedEmployees.push_back(move(retrievedEmp));
    }

    cout << "\nRetrieved Employees:" << endl;
    for (const auto& emp : retrievedEmployees) {
        emp->printEmployee();
    }

    // Count employees in each department
    cout << "\nEmployee count per department:" << endl;
    map<string, int> departmentEmployeeCount;

    for (const auto& emp : retrievedEmployees) {
        string deptId = emp->getDepartment()->getId();
        departmentEmployeeCount[deptId]++;
    }

    for (const auto& dept : retrievedDepartments) {
        string deptId = dept->getId();
        cout << "Department " << dept->getName() << " has " << departmentEmployeeCount[deptId] << " employee(s)." << endl;
    }
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
