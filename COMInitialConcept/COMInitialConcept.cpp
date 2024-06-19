#include "Employee.h"
#include "IEmployee.h"
#include "Department.h"
#include "IDepartment.h"
#include <iostream>
#include <vector>
#include <memory> // For std::unique_ptr
#include <map>


int main() {
    std::string deptFilename = "departments.dat";
    std::string empFilename = "employees.dat";

    // Create departments
    std::vector<std::unique_ptr<IDepartment>> departments;

    auto dept1 = std::make_unique<Department>();
    dept1->setId("123e4567-e89b-12d3-a456-426614174000");
    dept1->setName("Engineering");
    dept1->setAddress("123 Tech Lane");
    departments.push_back(std::move(dept1));

    auto dept2 = std::make_unique<Department>();
    dept2->setId("789e4567-e89b-12d3-a456-426614174000");
    dept2->setName("HR");
    dept2->setAddress("456 Human Resource Blvd");
    departments.push_back(std::move(dept2));

    // Create employees
    std::vector<std::unique_ptr<IEmployee>> employees;

    auto emp1 = std::make_unique<Employee>();
    emp1->setId("456e7890-e12b-34c5-a678-901234567890");
    emp1->setName("Nikolaos Bellias");
    emp1->setDateOfBirth("1990-01-01");
    emp1->setSalary(50000);
    emp1->setDepartment(departments[0].get());
    employees.push_back(std::move(emp1));

    auto emp2 = std::make_unique<Employee>();
    emp2->setId("123e7890-e12b-34c5-a678-901234567891");
    emp2->setName("Margarita Papastamou");
    emp2->setDateOfBirth("1985-05-15");
    emp2->setSalary(60000);
    emp2->setDepartment(departments[1].get());
    employees.push_back(std::move(emp2));

    auto emp3 = std::make_unique<Employee>();
    emp3->setId("789e7890-e12b-34c5-a678-901234567892");
    emp3->setName("Eleni Fasoula");
    emp3->setDateOfBirth("1975-12-22");
    emp3->setSalary(70000);
    emp3->setDepartment(departments[1].get());
    employees.push_back(std::move(emp3));

    for (const auto& dept : departments) {
        dept->storeDepartment(deptFilename);
    }
    std::cout << "Departments stored successfully." << std::endl;

    for (const auto& emp : employees) {
        emp->storeEmployee(empFilename);
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
