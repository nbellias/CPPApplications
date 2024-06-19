#pragma once
#ifdef COMINITIALCONCEPTDLL_EXPORTS
#define COMINITIALCONCEPTDLL_API __declspec(dllexport)
#else
#define COMINITIALCONCEPTDLL_API __declspec(dllimport)
#endif

#include <string>

using namespace std;

class COMINITIALCONCEPTDLL_API IDepartment {

public:
    // Methods to be implemented by the concrete class
    virtual void printDepartment() const = 0;

    // Getter and Setter methods for the department data
    virtual void setId(const string& id) = 0;
    virtual string getId() const = 0;

    virtual void setName(const string& name) = 0;
    virtual string getName() const = 0;

    virtual void setAddress(const string& address) = 0;
    virtual string getAddress() const = 0;
};
