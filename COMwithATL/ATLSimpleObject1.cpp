// ATLSimpleObject1.cpp : Implementation of CATLSimpleObject1

#include <math.h>
#include "pch.h"
#include "ATLSimpleObject1.h"
#include <iostream>

using namespace std;

// CATLSimpleObject1 method definitions

STDMETHODIMP CATLSimpleObject1::PrintHelloWorld()
{
    cout << "Hello World...from COM" << endl;
    return S_OK;
}

STDMETHODIMP CATLSimpleObject1::CalculateCircleArea(DOUBLE radius, DOUBLE* area)
{
    if (radius < 0)
    {
        return E_INVALIDARG;
    }
    *area = M_PI * radius * radius;
    return S_OK;
}