#include <string>
#include "Utils.h"

using namespace std;

string generateRandomString(int length) {
    const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    const size_t maxIndex = sizeof(charset) - 1;
    string randomString;

    for (int i = 0; i < length; ++i) {
        randomString += charset[rand() % maxIndex];
    }

    return randomString;
}
