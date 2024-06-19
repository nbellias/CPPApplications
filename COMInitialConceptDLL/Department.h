#pragma once
#ifdef COMINITIALCONCEPTDLL_EXPORTS
#define COMINITIALCONCEPTDLL_API __declspec(dllexport)
#else
#define COMINITIALCONCEPTDLL_API __declspec(dllimport)
#endif

#include "IDepartment.h"
#include "IPersistence.h"
#include <string>

using namespace std;

class COMINITIALCONCEPTDLL_API Department : public IDepartment, public IPersistence {
private:
    string m_id;
    string m_name;
    string m_address;

public:
    Department();
    Department(const string id, const string name, const string address);
    ~Department(void);
    // Implementing the IDepartment interface methods
    void printDepartment() const;
    // Implementing the IPersistence interface methods
    void store(const string& filename);
    void retrieveById(const string& id, const string& filename);
    void retrieveByName(const string& name, const string& filename);
    

    // Getter and Setter methods
    void setId(const string& id);
    string getId() const;

    void setName(const string& name);
    string getName() const;

    void setAddress(const string& address);
    string getAddress() const;
};

