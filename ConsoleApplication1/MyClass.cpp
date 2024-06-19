#include "MyClass.h"
#include <iostream>

MyClass::MyClass()
{
	isSomething = false;
	id = 0;
	name = "";
}

MyClass::MyClass(bool isSomething, long id, string name)
{
	this->isSomething = isSomething;
	this->id = id;
	this->name = name;
}

MyClass::~MyClass()
{
	delete this;
}

void MyClass::print()
{
	cout << "isSomething: " << isSomething << endl;
	cout << "id: " << id << endl;
	cout << "name: " << name << endl;
}
