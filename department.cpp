#include "department.h"
#include <iostream>
#include <fstream>

using namespace std;

// Remove whitespace around a name
string trimDepartmentField(string text)
{

    // contains whitespace characters to be removed
    string spaces = " \t\r\n";

    // Find the first non-whitespace character
    size_t start = text.find_first_not_of(spaces);

    // If the string is all whitespace, return an empty string
    if (start == string::npos)
    {
        return ""; // String is all whitespace
    }

    // Find the last non-whitespace character
    size_t end = text.find_last_not_of(spaces);

    // extracts part of the string
    return text.substr(start, end - start + 1);
}
