#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Employee.h"

using namespace std;

void writeCSV(const vector<Employee>& employees, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Employee Name,Department Name,Project ID\n";
        for (const auto& employee : employees) {
            for (const auto& project : employee.projects) {
                file << employee.name << "," << employee.department->name << "," << project->id << "\n";
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

void readAndPrintCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Read the header line
        std::cout << line << std::endl; // Print the header

        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}