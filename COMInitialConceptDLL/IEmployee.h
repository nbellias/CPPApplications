#pragma once
#ifdef COMINITIALCONCEPTDLL_EXPORTS
#define COMINITIALCONCEPTDLL_API __declspec(dllexport)
#else
#define COMINITIALCONCEPTDLL_API __declspec(dllimport)
#endif

#include <string>
#include "IDepartment.h"

using namespace std;

class COMINITIALCONCEPTDLL_API IEmployee {
public:
    // Methods to be implemented by the concrete class
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
