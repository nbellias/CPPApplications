#pragma once

#include <math.h>

#include "MyInterfaces.h"


// Circle class implementing the IShape interface
class Circle : public IShape {
public:
    Circle(double radius) : radius_(radius) {}

    double area() const override {
        const double PI = atan(1.0) * 4;
        return PI * radius_ * radius_;
    }

    std::string name() const override {
        return "Circle";
    }

private:
    double radius_;
};

// Rectangle class implementing the IShape interface
class Rectangle : public IShape {
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}

    double area() const override {
        return width_ * height_;
    }

    std::string name() const override {
        return "Rectangle";
    }

private:
    double width_;
    double height_;
};
