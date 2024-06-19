#include "pch.h"
#include "Department.h"
#include <iostream>
#include <fstream>

using namespace std;

// Implementing the interface methods

Department::Department()
{
	this->m_id = "";
	this->m_name = "";
	this->m_address = "";
}

Department::Department(const string id, const string name, const string address)
{
    this->m_id = id;
    this->m_name = name;
    this->m_address = address;
}

Department::~Department(void)
{
}

void Department::store(const string& filename) {
    ofstream file(filename, ios::binary | ios::app);
    if (file.is_open()) {
        size_t idSize = m_id.size();
        size_t nameSize = m_name.size();
        size_t addressSize = m_address.size();

        file.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
        file.write(m_id.c_str(), idSize);

        file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        file.write(m_name.c_str(), nameSize);

        file.write(reinterpret_cast<const char*>(&addressSize), sizeof(addressSize));
        file.write(m_address.c_str(), addressSize);

        file.close();
    }
}

void Department::retrieveById(const string& searchId, const string& filename) {
    ifstream file(filename, ios::binary);
    if (file.is_open()) {
        size_t idSize;
        size_t nameSize;
        size_t addressSize;

        while (file.read(reinterpret_cast<char*>(&idSize), sizeof(idSize))) {
            m_id.resize(idSize);
            file.read(&m_id[0], idSize);

            file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
            m_name.resize(nameSize);
            file.read(&m_name[0], nameSize);

            file.read(reinterpret_cast<char*>(&addressSize), sizeof(addressSize));
            m_address.resize(addressSize);
            file.read(&m_address[0], addressSize);

            if (m_id == searchId) {
                break;
            }
        }

        file.close();
    }
}

void Department::retrieveByName(const string& searchName, const string& filename) {
    ifstream file(filename, ios::binary);
    if (file.is_open()) {
        size_t idSize;
        size_t nameSize;
        size_t addressSize;

        while (file.read(reinterpret_cast<char*>(&idSize), sizeof(idSize))) {
            m_id.resize(idSize);
            file.read(&m_id[0], idSize);

            file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
            m_name.resize(nameSize);
            file.read(&m_name[0], nameSize);

            file.read(reinterpret_cast<char*>(&addressSize), sizeof(addressSize));
            m_address.resize(addressSize);
            file.read(&m_address[0], addressSize);

            if (m_name == searchName) {
                break;
            }
        }

        file.close();
    }
}

void Department::printDepartment() const {
    cout << "ID: " << m_id << endl;
    cout << "Name: " << m_name << endl;
    cout << "Address: " << m_address << endl;
}

// Implementing the getter and setter methods

void Department::setId(const string& id) {
    this->m_id = id;
}

string Department::getId() const {
    return m_id;
}

void Department::setName(const string& name) {
    this->m_name = name;
}

string Department::getName() const {
    return m_name;
}

void Department::setAddress(const string& address) {
    this->m_address = address;
}

string Department::getAddress() const {
    return m_address;
}
