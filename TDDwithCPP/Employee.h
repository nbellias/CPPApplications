#pragma once
#include <string>

using namespace std;

class Employee
{
public:
	Employee();
	~Employee();
	Employee(string id, string name, string dateOfBirth, string dateOfHiring) : id(id), name(name), dateOfBirth(dateOfBirth), dateOfHiring(dateOfHiring) {}
	string getId();
	string getName();
	string getDateOfBirth();
	string getDateOfHiring();
	void setId(string id);
	void setName(string name);
	void setDateOfBirth(string dateOfBirth);
	void setDateOfHiring(string dateOfHiring);
	void printEmployee();

private:
	string id;
	string name;
	string dateOfBirth;
	string dateOfHiring;
};
