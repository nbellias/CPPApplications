#pragma once
#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "IDepartment.h"
#include <string>

using namespace std;

class Department : public IDepartment {
private:
    string m_id;
    string m_name;
    string m_address;

public:
    Department();
    Department(const string id, const string name, const string address);
    ~Department(void);
    // Implementing the interface methods
    void storeDepartment(const string& filename);
    void retrieveDepartmentById(const string& id, const string& filename);
    void retrieveDepartmentByName(const string& name, const string& filename);
    void printDepartment() const;

    // Getter and Setter methods
    void setId(const string& id);
    string getId() const;

    void setName(const string& name);
    string getName() const;

    void setAddress(const string& address);
    string getAddress() const;
};

#endif // DEPARTMENT_H
