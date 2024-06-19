#pragma once

#ifdef LOGINDLL_EXPORTS
#define LOGINDLL_API __declspec(dllexport)
#else
#define LOGINDLL_API __declspec(dllimport)
#endif

extern "C" LOGINDLL_API bool ValidateCredentials(const char* username, const char* password);

