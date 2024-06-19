#pragma once

#include <string>
#include <set>
#include "Department.h"
#include "Project.h"

using namespace std;

class Employee
{
public:
    int id;
    string name;
    Department* department;
    set<Project*> projects;

    Employee(int id, string name, Department* department)
        : id(id), name(name), department(department) {}

    void addProject(Project* project) {
        projects.insert(project);
    }
};

