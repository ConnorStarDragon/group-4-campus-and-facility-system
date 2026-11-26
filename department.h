#ifndef Department_H
#define Department_H

#include <string>
#include <vector>
using namespace std;

// one department
struct DepartmentNode
{
    string name;
    // DepartmentNode *next;
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
    // Print all department names
    void printDepartmentList(DepartmentNode *current);

    DepartmentNode *root;

    // Search for a department node by name
    DepartmentNode *findNode(DepartmentNode *current, string name);

    // Display the department hierarchy recursively
    void printHierarchy(DepartmentNode *current, int depth);

    // Preorder traversal recursively
    void printPreorder(DepartmentNode *current, bool &first);

    // delete allocated nodes
    void deleteNodes(DepartmentNode *current);

    // Visits children before their parent
    void printPostorder(DepartmentNode *current, bool &first);

    // Counts departments, leaves, and height
    void countDepartmentStats(DepartmentNode *current, int depth, int &total, int &leaves, int &height);

public:
    // Display all departments
    void displayDepartments();

    // Creates and destroys the tree
    DepartmentTree();
    ~DepartmentTree();

    // Check if the tree is empty
    bool isEmpty();

    // add a department
    bool addDepartment(string name, string parentName, string &error);

    // Load department from file
    void loadFromFile(string filename);

    // Search and display department info
    bool searchDepartment(string name);

    // Display the department hierarchy
    void displayHierarchy();

    // Display preorder traversal
    void preorderTraversal();

    // Display postorder traversal
    void postorderTraversal();

    // Display level-order traversal
    void levelOrderTraversal();

    // Display department statistics
    void displayDepartmentStatistics();
};

#endif
