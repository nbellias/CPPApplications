#pragma once
#ifdef COMINITIALCONCEPTDLL_EXPORTS
#define COMINITIALCONCEPTDLL_API __declspec(dllexport)
#else
#define COMINITIALCONCEPTDLL_API __declspec(dllimport)
#endif

#include <string>

using namespace std;

class COMINITIALCONCEPTDLL_API IPersistence {
	public:
	// Methods to be implemented by the concrete class
	virtual void store(const string& filename) = 0;
	virtual void retrieveById(const string& id, const string& filename) = 0;
	virtual void retrieveByName(const string& name, const string& filename) = 0;
};