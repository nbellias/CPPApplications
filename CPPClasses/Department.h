#pragma once
#include <string>



class Department
{
public:
    int id;
    std::string name;

    Department(int id, std::string name) : id(id), name(name) {}
};

