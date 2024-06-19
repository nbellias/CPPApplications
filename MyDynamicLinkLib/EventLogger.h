#pragma once

#include <string>

using namespace std;

extern "C" __declspec(dllexport) void WriteToEventLog(string message);

