// COMwithATLclient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\COMwithATL\COMwithATL_i.h"
#include "..\COMwithATL\COMwithATL_i.c"

using namespace std;

int main()
{
    cout << "COM Demo!\n";

    CoInitialize(nullptr);

    IATLSimpleObject1* pATLSimpleObject = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_ATLSimpleObject1, nullptr, CLSCTX_ALL, IID_IATLSimpleObject1, (void**)&pATLSimpleObject);
    if (SUCCEEDED(hr) && pATLSimpleObject)
    {
        // Call the method PrintHelloWorld
        pATLSimpleObject->PrintHelloWorld();

        // Call the method CalculateCircleArea
        DOUBLE radius = 5.0;
        DOUBLE area = 0.0;
        hr = pATLSimpleObject->CalculateCircleArea(radius, &area);
        if (SUCCEEDED(hr))
		{
			cout << "Area of circle with radius " << radius << " is " << area << endl;
		}
        else
        {
            cout << "Failed to calculate area of circle with radius " << radius << endl;
		}


        pATLSimpleObject->Release();
    }

    CoUninitialize();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
