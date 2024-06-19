#pragma once
#ifndef IEMPLOYEE_H
#define IEMPLOYEE_H

#include <string>
#include "IDepartment.h"

using namespace std;

class IEmployee {
public:
    // Methods to be implemented by the concrete class
    virtual void storeEmployee(const string& filename) = 0;
    virtual void retrieveEmployeeById(const string& id, const string& filename) = 0;
    virtual void retrieveEmployeeByName(const string& name, const string& filename) = 0;
    virtual void printEmployee() const = 0;

    // Getter and Setter methods for the employee data
    virtual void setId(const string& id) = 0;
    virtual string getId() const = 0;

    virtual void setName(const string& name) = 0;
    virtual string getName() const = 0;

    virtual void setDateOfBirth(const string& dateOfBirth) = 0;
    virtual string getDateOfBirth() const = 0;

    virtual void setSalary(double salary) = 0;
    virtual double getSalary() const = 0;

    virtual void setDepartment(IDepartment* department) = 0;
    virtual IDepartment* getDepartment() const = 0;
};

#endif // IEMPLOYEE_H
