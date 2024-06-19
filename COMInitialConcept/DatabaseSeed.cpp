#include "Employee.h"
#include "IEmployee.h"
#include "Department.h"
#include "IDepartment.h"
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <random>
#include <sstream>
#include <map>

// Function to generate a random UUID string
std::string generateUUID() {
    std::stringstream ss;
    ss << std::hex;
    for (int i = 0; i < 8; ++i) ss << ((rand() % 16));
    ss << "-";
    for (int i = 0; i < 4; ++i) ss << ((rand() % 16));
    ss << "-4";
    for (int i = 0; i < 3; ++i) ss << ((rand() % 16));
    ss << "-";
    ss << ((rand() % 4) + 8);
    for (int i = 0; i < 3; ++i) ss << ((rand() % 16));
    ss << "-";
    for (int i = 0; i < 12; ++i) ss << ((rand() % 16));
    return ss.str();
}

// Function to generate a random name
std::string generateName() {
    static const char* firstNames[] = { "Nikos", "Jane", "Margarita", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Dimitris" };
    static const char* lastNames[] = { "Smith", "Doe", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Martinez" };
    std::stringstream ss;
    ss << firstNames[rand() % 10] << " " << lastNames[rand() % 10];
    return ss.str();
}

int databaseSeed() {
    srand(time(nullptr)); // Seed the random number generator

    // Create departments
    std::vector<std::unique_ptr<IDepartment>> departments;
    for (int i = 0; i < 10; ++i) {
        auto dept = std::make_unique<Department>();
        dept->setId(generateUUID());
        dept->setName("Department " + std::to_string(i + 1));
        dept->setAddress(std::to_string(i + 1) + " Main St");
        departments.push_back(std::move(dept));
    }

    // Create employees
    std::vector<std::unique_ptr<IEmployee>> employees;
    for (int i = 0; i < 10000; ++i) {
        auto emp = std::make_unique<Employee>();
        emp->setId(generateUUID());
        emp->setName(generateName());
        emp->setDateOfBirth("1990-01-01"); // Simplified for demonstration
        emp->setSalary(30000 + (rand() % 50000));
        emp->setDepartment(departments[rand() % 10].get());
        employees.push_back(std::move(emp));
    }

    // Store departments and employees
    std::string deptFilename = "departments.dat";
    std::string empFilename = "employees.dat";

    // Store departments
    std::ofstream deptFile(deptFilename, std::ios::binary);
    if (deptFile.is_open()) {
        for (const auto& dept : departments) {
            dept->storeDepartment(deptFilename);
        }
        deptFile.close();
    }
    std::cout << "Departments stored successfully." << std::endl;

    // Store employees
    std::ofstream empFile(empFilename, std::ios::binary);
    if (empFile.is_open()) {
        for (const auto& emp : employees) {
            emp->storeEmployee(empFilename);
        }
        empFile.close();
    }
    std::cout << "Employees stored successfully." << std::endl;

    // Retrieve and print departments
    std::vector<std::unique_ptr<IDepartment>> retrievedDepartments;

    for (const auto& dept : departments) {
        auto retrievedDept = std::make_unique<Department>();
        retrievedDept->retrieveDepartmentById(dept->getId(), deptFilename);
        retrievedDepartments.push_back(std::move(retrievedDept));
    }

    std::cout << "\nRetrieved Departments:" << std::endl;
    for (const auto& dept : retrievedDepartments) {
        dept->printDepartment();
    }

    // Retrieve and print employees
    std::vector<std::unique_ptr<IEmployee>> retrievedEmployees;

    for (const auto& emp : employees) {
        auto retrievedEmp = std::make_unique<Employee>();
        retrievedEmp->retrieveEmployeeById(emp->getId(), empFilename);
        retrievedEmployees.push_back(std::move(retrievedEmp));
    }

    std::cout << "\nRetrieved Employees:" << std::endl;
    for (const auto& emp : retrievedEmployees) {
        emp->printEmployee();
    }

    // Count employees in each department
    std::cout << "\nEmployee count per department:" << std::endl;
    std::map<std::string, int> departmentEmployeeCount;

    for (const auto& emp : retrievedEmployees) {
        std::string deptId = emp->getDepartment()->getId();
        departmentEmployeeCount[deptId]++;
    }

    for (const auto& dept : retrievedDepartments) {
        std::string deptId = dept->getId();
        std::cout << "Department " << dept->getName() << " has " << departmentEmployeeCount[deptId] << " employee(s)." << std::endl;
    }

    return 0;
}
