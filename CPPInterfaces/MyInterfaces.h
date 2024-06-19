#pragma once

#include <string>
#include <iostream>

using namespace std;

class IShape {
public:
    virtual ~IShape() = default; // Virtual destructor for proper cleanup
    virtual double area() const = 0; // Pure virtual function
    virtual string name() const = 0; // Pure virtual function
};
