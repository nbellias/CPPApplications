#include "MyApp.h"
#include <iostream>
#include <vector>
#include <locale>
#include <string>
#include "Utils.h"
using namespace string_demos;
using namespace std;
using namespace string_literals; // enables s-suffix for string literals

void MyApp::varDeclarations()
{
	// VARIABLES
	int answer = 42;      // integer literal
	double d = sin(108.87);     // floating point literal passed to sin function
	bool b = true;              // boolean literal
	int* ip = &answer;      // pointer literal
	int i = 157;        // Decimal literal
	//int j = 0198;       // Not a decimal number; erroneous octal literal, 9 is not an octal digit
	int k = 0365;       // Leading zero specifies octal literal, not decimal
	int m = 36'000'000;  // digit separators make large values more readable
	int ih = 0x3fff;   // Hexadecimal literal
	int j = 0X3FFF;   // Equal to ih
	long long ill = 24'847'458'121;
	unsigned val_1 = 328u;                  // Unsigned value
	long val_2 = 0x7FFFFFL;                 // Long value specified as hex literal
	unsigned long val_3 = 0776745ul;        // Unsigned long value
	auto val_4 = 108LL;                           // signed long long
	auto val_5 = 0x8000000000000000ULL << 16;     // unsigned long long
	auto x = 42;           // int
	auto y = 3.14;         // double
	auto s = "hello";      // const char*
	auto ptr = &x;         // int*
	vector<int> vec = { 1, 2, 3, 4, 5 };
	auto it = vec.begin(); // vector<int>::iterator

	cout << "Hello World! Γειά σας\n";
	cout << answer << endl;
	cout << d << endl;
	cout << b << endl;
	cout << ip << endl;
	cout << *ip << endl;
	cout << i << endl;
	//cout << j << endl;
	cout << k << endl;
	cout << m << endl;
	cout << ih << endl;
	cout << j << endl;
	cout << ill << endl;
	cout << val_1 << endl;
	cout << val_2 << endl;
	cout << val_3 << endl;
	cout << val_4 << endl;
	cout << val_5 << endl;
	cout << x << endl;
	cout << y << endl;;
	cout << s << endl;;
	cout << ptr << endl;
	cout << *ptr << endl;
	// Iterate through vec and print each element
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << endl;
	}
}

void MyApp::printWithLocale()
{
	// Set the global locale to the user's native environment
	locale::global(locale("el_EL"));

	// Imbue the wcout stream with the current global locale
	wcout.imbue(locale());

	// Output a wide string
	wcout << L"Hello, Καλημέρα" << endl;

	// Another example with special wide characters
	wcout << L"Characters: \u03B1 \u03B2 \u03B3" << endl; // Greek letters alpha, beta, gamma
}

void MyApp::printTheFollowingStringLiterals()
{
	// Character literals
	auto c0 = 'A'; // char
	auto c1 = u8'A'; // char
	auto c2 = L'A'; // wchar_t
	auto c3 = u'A'; // char16_t
	auto c4 = U'A'; // char32_t

	// Multicharacter literals
	auto m0 = 'abcd'; // int, value 0x61626364

	// String literals
	auto s0 = "hello"; // const char*
	auto s1 = u8"hello"; // const char* before C++20, encoded as UTF-8,
	// const char8_t* in C++20
	auto s2 = L"hello"; // const wchar_t*
	auto s3 = u"hello"; // const char16_t*, encoded as UTF-16
	auto s4 = U"hello"; // const char32_t*, encoded as UTF-32

	// Raw string literals containing unescaped \ and "
	auto R0 = R"("Hello \ world")"; // const char*
	auto R1 = u8R"("Hello \ world")"; // const char* before C++20, encoded as UTF-8,
	// const char8_t* in C++20
	auto R2 = LR"("Hello \ world")"; // const wchar_t*
	auto R3 = uR"("Hello \ world")"; // const char16_t*, encoded as UTF-16
	auto R4 = UR"("Hello \ world")"; // const char32_t*, encoded as UTF-32

	// Combining string literals with standard s-suffix
	auto S0 = "hello"s; // string
	auto S1 = u8"hello"s; // string before C++20, u8string in C++20
	auto S2 = L"hello"s; // wstring
	auto S3 = u"hello"s; // u16string
	auto S4 = U"hello"s; // u32string

	// Combining raw string literals with standard s-suffix
	auto S5 = R"("Hello \ world")"s; // string from a raw const char*
	auto S6 = u8R"("Hello \ world Καλημέρα")"s; // string from a raw const char* before C++20, encoded as UTF-8,
	// u8string in C++20
	auto S7 = LR"("Hello \ world")"s; // wstring from a raw const wchar_t*
	auto S8 = uR"("Hello \ world")"s; // u16string from a raw const char16_t*, encoded as UTF-16
	auto S9 = UR"("Καλημέρα")"s; // u32string from a raw const char32_t*, encoded as UTF-32

	// Print the values
	cout << c0 << endl;
	cout << c1 << endl;
	wcout << c2 << endl;
	wcout << c3 << endl;
	wcout << c4 << endl;
	cout << m0 << endl;
	cout << s0 << endl;
	cout << s1 << endl;
	wcout << s2 << endl;
	wcout << s3 << endl;
	wcout << s4 << endl;
	cout << R0 << endl;
	cout << R1 << endl;
	wcout << R2 << endl;
	wcout << R3 << endl;
	wcout << R4 << endl;
	cout << S0 << endl;
	cout << S1 << endl;
	wcout << S2 << endl;
	/*wcout << S3 << endl;
	wcout << S4 << endl;*/
	cout << S5 << endl;
	cout << S6 << endl;
	wcout << S7 << endl;
	//wcout << S8 << endl;
	//wcout << S9 << endl;
}

void MyApp::createRandomStrings()
{
	// Initialize the random number generator with the current time
	srand(static_cast<unsigned>(std::time(0)));

	// Generate 10 random strings
	for (int i = 0; i < 10; ++i)
	{
		// Generate a random length between 10 and 20
		int randomLength = 10 + (std::rand() % 11);

		// Generate a random string
		string randomString = generateRandomString(randomLength);

		// Output the random string
		cout << "Random String: " << randomString << endl;
	}
}
