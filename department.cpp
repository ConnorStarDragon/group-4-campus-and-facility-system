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

// Compare dpeartment names without Capitalization
bool sameDepartmentName(string a, string b)
{

    if (a.length() != b.length())
    {
        return false;
    }

    for (size_t i = 0; i < a.length(); i++)
    {
        char letterA = a[i];
        char letterB = b[i];

        if (letterA >= 'A' && letterA <= 'Z')
        {
            letterA = letterA + ('a' - 'A'); // Convert to lowercase
        }
        if (letterB >= 'A' && letterB <= 'Z')
        {
            letterB = letterB + ('a' - 'A'); // Convert to lowercase
        }
        if (letterA != letterB)
        {
            return false;
        }
    }
    return true;
}

// Create an empty department tree
DepartmentTree::DepartmentTree()
{
    root = nullptr;
}

// Delete the tree when finished
DepartmentTree::~DepartmentTree()
{
    deleteNodes(root);
}

// Delete each department and its children
void DepartmentTree::deleteNodes(DepartmentNode *current)
{
    if (current == nullptr)
    {
        return;
    }

    // Recursively delete children
    for (DepartmentNode *child : current->children)
    {
        deleteNodes(child);
    }

    // Delete the current node
    delete current;
}

// Check whether the tree is empty
bool DepartmentTree::isEmpty()
{

    return root == nullptr;
}

// Searches for a department by name
DepartmentNode *DepartmentTree::findNode(DepartmentNode *current, string name)
{
    if (current == nullptr)
    {
        return nullptr;
    }

    // Check if the current node matches the name
    if (sameDepartmentName(current->name, name))
    {
        return current;
    }

    // Recursively search in children
    for (DepartmentNode *child : current->children)
    {
        DepartmentNode *result = findNode(child, name);
        if (result != nullptr)
        {
            return result;
        }
    }

    return nullptr; // Not found
}

// Add a new department to the tree
bool DepartmentTree::addDepartment(string name, string parentName, string &error)
{
    // Trim whitespace from the department name
    name = trimDepartmentField(name);
    parentName = trimDepartmentField(parentName);

    error = "";

    // Reject empty department names
    if (name.empty())
    {
        error = "Department name cannot be empty.";
        return false;
    }

    if (parentName.empty())
    {
        error = "Parent name cannot be empty.";
        return false;
    }

    // Reject if the department already exists
    if (findNode(root, name) != nullptr)
    {
        error = "Department already exists: " + name;
        return false;
    }

    // If the tree is empty, create the root node
    if (root == nullptr)
    {
        if (!sameDepartmentName(parentName, "NONE"))
        {
            error = "The first department must have NONE as its parent.";
            return false;
        }

        root = new DepartmentNode(name, nullptr);
        return true;
    }

    // Only the root can have ParentName as NONE
    if (sameDepartmentName(parentName, "NONE"))
    {
        error = "Only the root department can have NONE as its parent.";
        return false;
    }

    // Find the parent department node
    DepartmentNode *parentNode = findNode(root, parentName);
    if (parentNode == nullptr)
    {
        error = "Unknown parent: " + parentName;
        return false;
    }

    // Create a new department node
    DepartmentNode *newNode = new DepartmentNode(name, parentNode);

    // Add the new node to the parent's children
    parentNode->children.push_back(newNode);

    return true;
}

// Load departments from departments.txt
void DepartmentTree::loadFromFile(string filePath)
{
    ifstream file(filePath);

    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    // Check whether the file opened
    if (!file.is_open())
    {
        cout << "Error: Cannot open file: " << filePath << endl;
        cout << "departments.txt file: 0 accepted, 0 rejected" << endl;
        return;
    }

    string line;

    // Read the file one line at a time
    while (getline(file, line))
    {
        lineNumber++;

        line = trimDepartmentField(line);

        // Skip empty lines
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        // Find the separator between department name and parent name
        size_t separator = line.find('|');

        // Make sure there are exactly two fields
        if (separator == string::npos || line.find('|', separator + 1) != string::npos)
        {
            rejected++;

            cout << "Warning: departments.txt line " << lineNumber << ": Incorrect number of fields " << line << endl;
            continue;
        }

        // Seperate the name and parent
        string name = line.substr(0, separator);
        string parent = line.substr(separator + 1);

        string error;

        // Try to add the department to the tree
        if (addDepartment(name, parent, error))
        {
            accepted++;
        }
        else
        {
            rejected++;

            cout << "Warning: departments.txt line " << lineNumber << ": " << error << endl;
        }
    }

    file.close();

    // Display the results of loading the file
    cout << "departments.txt: " << accepted << " accepted, " << rejected << " rejected" << endl;
}

// Search for a department and display its information
void DepartmentTree::searchDepartment(string name)
{
    name = trimDepartmentField(name);

    if (name.empty())
    {
        cout << "Error: Department name cannot be empty." << endl;
        return;
    }

    DepartmentNode *found = findNode(root, name);

    if (found == nullptr)
    {
        cout << "Department not found: " << name << endl;
        return;
    }

    // Calculate the department depth
    int depth = 0;
    DepartmentNode *current = found;

    while (current->parent != nullptr)
    {
        depth++;
        current = current->parent;
    }

    // Display the department information
    cout << "Name: " << found->name << endl;

    if (found->parent == nullptr)
    {
        cout << "Parent: None" << endl;
    }
    else
    {
        cout << "Parent: " << found->parent->name << endl;
    }

    cout << "Direct children: " << found->children.size() << endl;

    cout << "Depth: " << depth << endl;
}

// Print departments with indentation
void DepartmentTree::printHierarchy(DepartmentNode *current, int depth)
{
    if (current == nullptr)
    {
        return;
    }

    // Print four spaces per depth level
    cout << string(depth * 4, ' ') << current->name << endl;

    // visit each child department
    for (DepartmentNode *child : current->children)
    {
        printHierarchy(child, depth + 1);
    }
}

// Display the entire department hierarchy
void DepartmentTree::displayHierarchy()
{
    if (root == nullptr)
    {
        cout << "No departments are loaded" << endl;
        return;
    }
    printHierarchy(root, 0);
}

// Recursively visits departments in preorder
void DepartmentTree::printPreorder(DepartmentNode *current, bool &first)
{
    if (current == nullptr)
    {
        return;
    }

    // Print the department name with a comma separator
    if (!first)
    {
        cout << ", ";
    }
    cout << current->name;
    first = false;

    // Visit each child department
    for (DepartmentNode *child : current->children)
    {
        printPreorder(child, first);
    }
}

// States the preorder traversal at root
void DepartmentTree::preorderTraversal()
{
    if (root == nullptr)
    {
        cout << "No departments are loaded" << endl;
        return;
    }

    bool first = true;
    printPreorder(root, first);
    cout << endl;
}
