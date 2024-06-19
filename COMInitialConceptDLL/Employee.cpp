#include "pch.h"
#include "Employee.h"
#include "Department.h"
#include <iostream>
#include <fstream>

using namespace std;

// Implementing the interface methods

Employee::Employee()
{
	this->m_id = "";
	this->m_name = "";
	this->m_dateOfBirth = "";
	this->m_salary = 0.0;
	this->m_department = nullptr;
}

Employee::Employee(const string id, const string name, const string dateOfBirth, double salary, IDepartment* department)
{
    this->m_id = id;
	this->m_name = name;
	this->m_dateOfBirth = dateOfBirth;
	this->m_salary = salary;
	this->m_department = department;
}

Employee::~Employee(void)
{
}

void Employee::store(const string& filename) {
    ofstream file(filename, ios::binary | ios::app);
    if (file.is_open()) {
        size_t idSize = m_id.size();
        size_t nameSize = m_name.size();
        size_t dobSize = m_dateOfBirth.size();
        size_t departmentIdSize = m_department->getId().size();
        size_t departmentNameSize = m_department->getName().size();
        size_t departmentAddressSize = m_department->getAddress().size();

        file.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
        file.write(m_id.c_str(), idSize);

        file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        file.write(m_name.c_str(), nameSize);

        file.write(reinterpret_cast<const char*>(&dobSize), sizeof(dobSize));
        file.write(m_dateOfBirth.c_str(), dobSize);

        file.write(reinterpret_cast<const char*>(&m_salary), sizeof(m_salary));

        file.write(reinterpret_cast<const char*>(&departmentIdSize), sizeof(departmentIdSize));
        file.write(m_department->getId().c_str(), departmentIdSize);

        file.write(reinterpret_cast<const char*>(&departmentNameSize), sizeof(departmentNameSize));
        file.write(m_department->getName().c_str(), departmentNameSize);

        file.write(reinterpret_cast<const char*>(&departmentAddressSize), sizeof(departmentAddressSize));
        file.write(m_department->getAddress().c_str(), departmentAddressSize);

        file.close();
    }
}

void Employee::retrieveById(const string& searchId, const string& filename) {
    ifstream file(filename, ios::binary);
    if (file.is_open()) {
        size_t idSize;
        size_t nameSize;
        size_t dobSize;
        size_t departmentIdSize;
        size_t departmentNameSize;
        size_t departmentAddressSize;

        while (file.read(reinterpret_cast<char*>(&idSize), sizeof(idSize))) {
            m_id.resize(idSize);
            file.read(&m_id[0], idSize);

            file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
            m_name.resize(nameSize);
            file.read(&m_name[0], nameSize);

            file.read(reinterpret_cast<char*>(&dobSize), sizeof(dobSize));
            m_dateOfBirth.resize(dobSize);
            file.read(&m_dateOfBirth[0], dobSize);

            file.read(reinterpret_cast<char*>(&m_salary), sizeof(m_salary));

            file.read(reinterpret_cast<char*>(&departmentIdSize), sizeof(departmentIdSize));
            string departmentId(departmentIdSize, ' ');
            file.read(&departmentId[0], departmentIdSize);

            file.read(reinterpret_cast<char*>(&departmentNameSize), sizeof(departmentNameSize));
            string departmentName(departmentNameSize, ' ');
            file.read(&departmentName[0], departmentNameSize);

            file.read(reinterpret_cast<char*>(&departmentAddressSize), sizeof(departmentAddressSize));
            string departmentAddress(departmentAddressSize, ' ');
            file.read(&departmentAddress[0], departmentAddressSize);

            if (m_id == searchId) {
                m_department = new Department(departmentId, departmentName, departmentAddress);
                break;
            }
        }

        file.close();
    }
}

void Employee::retrieveByName(const string& searchName, const string& filename) {
    ifstream file(filename, ios::binary);
    if (file.is_open()) {
        size_t idSize;
        size_t nameSize;
        size_t dobSize;
        size_t departmentIdSize;
        size_t departmentNameSize;
        size_t departmentAddressSize;

        while (file.read(reinterpret_cast<char*>(&idSize), sizeof(idSize))) {
            m_id.resize(idSize);
            file.read(&m_id[0], idSize);

            file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
            m_name.resize(nameSize);
            file.read(&m_name[0], nameSize);

            file.read(reinterpret_cast<char*>(&dobSize), sizeof(dobSize));
            m_dateOfBirth.resize(dobSize);
            file.read(&m_dateOfBirth[0], dobSize);

            file.read(reinterpret_cast<char*>(&m_salary), sizeof(m_salary));

            file.read(reinterpret_cast<char*>(&departmentIdSize), sizeof(departmentIdSize));
            string departmentId(departmentIdSize, ' ');
            file.read(&departmentId[0], departmentIdSize);

            file.read(reinterpret_cast<char*>(&departmentNameSize), sizeof(departmentNameSize));
            string departmentName(departmentNameSize, ' ');
            file.read(&departmentName[0], departmentNameSize);

            file.read(reinterpret_cast<char*>(&departmentAddressSize), sizeof(departmentAddressSize));
            string departmentAddress(departmentAddressSize, ' ');
            file.read(&departmentAddress[0], departmentAddressSize);

            if (m_name == searchName) {
                m_department = new Department(departmentId, departmentName, departmentAddress);
                break;
            }
        }

        file.close();
    }
}

void Employee::printEmployee() const {
    cout << "ID: " << m_id << endl;
    cout << "Name: " << m_name << endl;
    cout << "Date of Birth: " << m_dateOfBirth << endl;
    cout << "Salary: " << m_salary << endl;
    cout << "Department ID: " << m_department->getId() << endl;
    cout << "Department Name: " << m_department->getName() << endl;
    cout << "Department Address: " << m_department->getAddress() << endl;
}

// Implementing the getter and setter methods

void Employee::setId(const string& id) {
    this->m_id = id;
}

string Employee::getId() const {
    return m_id;
}

void Employee::setName(const string& name) {
    this->m_name = name;
}

string Employee::getName() const {
    return m_name;
}

void Employee::setDateOfBirth(const string& dateOfBirth) {
    this->m_dateOfBirth = dateOfBirth;
}

string Employee::getDateOfBirth() const {
    return m_dateOfBirth;
}

void Employee::setSalary(double salary) {
    this->m_salary = salary;
}

double Employee::getSalary() const {
    return m_salary;
}

void Employee::setDepartment(IDepartment* department) {
    this->m_department = department;
}

IDepartment* Employee::getDepartment() const {
    return m_department;
}
