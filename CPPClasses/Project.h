#pragma once

#include <string>

class Project
{
public:
    int id;
    std::string name;

    Project(int id, std::string name) : id(id), name(name) {}
};

