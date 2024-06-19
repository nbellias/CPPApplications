#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "IEmployee.h"
#include "IDepartment.h"

using namespace std;

class Employee : public IEmployee {
private:
    string m_id;
    string m_name;
    string m_dateOfBirth;
    double m_salary;
    IDepartment* m_department;

public:
    Employee();
    Employee(const string id, const string name, const string dateOfBirth, double salary, IDepartment* department);
    ~Employee(void);
    // Implementing the interface methods
    void storeEmployee(const string& filename);
    void retrieveEmployeeById(const string& id, const string& filename);
    void retrieveEmployeeByName(const string& name, const string& filename);
    void printEmployee() const;

    // Getter and Setter methods
    void setId(const string& id);
    string getId() const;

    void setName(const string& name);
    string getName() const;

    void setDateOfBirth(const string& dateOfBirth);
    string getDateOfBirth() const;

    void setSalary(double salary);
    double getSalary() const;

    void setDepartment(IDepartment* department);
    IDepartment* getDepartment() const;
};

#endif // EMPLOYEE_H
