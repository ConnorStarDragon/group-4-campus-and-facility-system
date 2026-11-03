#ifndef Department_H
#define Department_H

#include <string>
#include <vector>
using namespace std;

// one department
struct DepartmentNode
{
    string name;
    DepartmentNode *next;
    vector<DepartmentNode *> children;
    DepartmentNode *parent;

    // create a departement node
    DepartmentNode(string departmentName, DepartmentNode *parentNode)
    {
        name = departmentName;
        parent = parentNode;
    }
};

// Represent entire department tree
class DepartmentTree
{
private:
    DepartmentNode *root;

    // Search for a department node by name
    DepartmentNode *findNode(DepartmentNode *current, string name);

    // Display the department hierarchy recursively
    void printHierarchy(DepartmentNode *current, int depth);

    // Preorder traversal recursively
    void printPreorder(DepartmentNode *current, bool &first);

    // delete allocated nodes
    void deleteNodes(DepartmentNode *current);

public:
    // Creates and destroys the tree
    DepartmentTree();
    ~DepartmentTree();

    // Check if the tree is empty
    bool isEmpty();

    // add a department
    void addDepartment(string name, string parentName, string &error);

    // Load department from file
    void loadFromFile(string filename);

    // Search and display department info
    void searchDepartment(string name);

    // Display the department hierarchy
    void displayHierarchy();

    // Display preorder traversal
    void preorderTraversal();
};

#endif
