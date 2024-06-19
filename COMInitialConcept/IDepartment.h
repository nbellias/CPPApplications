#pragma once
#ifndef IDEPARTMENT_H
#define IDEPARTMENT_H

#include <string>

using namespace std;

class IDepartment {

public:
    // Methods to be implemented by the concrete class
    virtual void storeDepartment(const string& filename) = 0;
    virtual void retrieveDepartmentById(const string& id, const string& filename) = 0;
    virtual void retrieveDepartmentByName(const string& name, const string& filename) = 0;
    virtual void printDepartment() const = 0;

    // Getter and Setter methods for the department data
    virtual void setId(const string& id) = 0;
    virtual string getId() const = 0;

    virtual void setName(const string& name) = 0;
    virtual string getName() const = 0;

    virtual void setAddress(const string& address) = 0;
    virtual string getAddress() const = 0;
};

#endif // IDEPARTMENT_H
