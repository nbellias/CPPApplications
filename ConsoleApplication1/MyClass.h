#pragma once
#include <string>

using namespace std;

class MyClass
{
public:
	bool isSomething;
	long id;
	string name;

	MyClass();
	MyClass(bool isSomething, long id, string name);
	~MyClass();
	void print();
};

