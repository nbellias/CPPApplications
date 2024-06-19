#pragma once
#ifdef COMINITIALCONCEPTDLL_EXPORTS
#define COMINITIALCONCEPTDLL_API __declspec(dllexport)
#else
#define COMINITIALCONCEPTDLL_API __declspec(dllimport)
#endif

#include "IEmployee.h"
#include "IDepartment.h"
#include "IPersistence.h"

using namespace std;

class  COMINITIALCONCEPTDLL_API Employee : public IEmployee, public IPersistence {
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
    // Implementing the IEmployee interface methods
    void printEmployee() const;
    // Implementing the IPersistence interface methods
    void store(const string& filename);
    void retrieveById(const string& id, const string& filename);
    void retrieveByName(const string& name, const string& filename);
    
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
