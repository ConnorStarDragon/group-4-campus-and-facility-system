#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>
#include <string>
#include <algorithm>

#include "HashTable.h"
#include "department.h"
#include "CampusGraph.h"
#include "GraphLoader.h"

using namespace std;

// Trim leading and trailing whitespace from a string
void trim(string &str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos)
    {
        str.clear();
        return;
    }
    size_t end = str.find_last_not_of(" \t\n\r");
    str = str.substr(start, end - start + 1);
}

int main()
{
    // Create Department Tree
    DepartmentTree departments;

    // Open input files
    ifstream facilitiesIn("facilities.txt");

    // Check if the input file was opened successfully
    if (!facilitiesIn.is_open())
    {
        cout << "Error: could not open \"facilities.txt\", treating it as if empty." << endl;
    }

    vector<Facilities> facilities; // Vector to store all facilities
    vector<string> previousIds;    // Vector to store previously seen facility IDs for duplicate checking

    int accepted = 0; // Count of accepted facility entries
    int rejected = 0; // Count of rejected facility entries

    int i = 0;                          // Index of the current facility entry being processed
    while (facilitiesIn.eof() == false) // Read facility entries until the end of the file
    {
        string id, facilityName, buildingName, facilityType; // Variables to store the current facility entry's data
        getline(facilitiesIn, id, '|');                      // Read the facility ID from the input file
        if (id[0] == '#')
        {
            facilitiesIn.ignore(numeric_limits<std::streamsize>::max(), '\n'); // skip comment line
            continue;
        }
        trim(id);
        if (id.empty())
        {
            if (facilitiesIn.eof())
            { // Check if the end of the file has been reached
                break;
            }
            cout << "Error: Facility ID is missing for entry " << i << ". Skipping this entry." << endl; // skip if missing id
            rejected++;
            facilitiesIn.ignore(numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        getline(facilitiesIn, facilityName, '|'); // Read the facility name from the input file
        trim(facilityName);
        if (facilityName.empty())
        {
            cout << "Error: Facility name is missing for entry " << i << ", id: " << id << ". Skipping this entry." << endl; // skip if missing facility name
            rejected++;
            facilitiesIn.ignore(numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        getline(facilitiesIn, buildingName, '|'); // Read the building name from the input file
        trim(buildingName);
        if (buildingName.empty())
        {
            cout << "Error: Building name is missing for entry " << i << ", id: " << id << ". Skipping this entry." << endl; // skip if missing building name
            rejected++;
            facilitiesIn.ignore(numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        getline(facilitiesIn, facilityType, '\n'); // Read the facility type from the input file
        trim(facilityType);
        if (facilityType.empty())
        {
            cout << "Error: Facility type is missing for entry " << i << ", id: " << id << ". Skipping this entry." << endl; // skip if missing facility type
            rejected++;
            facilitiesIn.ignore(numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (id.empty()) // Check if the facility ID is empty
        {
            break;
        }
        for (const string &prevId : previousIds)
        { // Check for duplicate facility IDs
            if (prevId == id)
            {
                cout << "Error: Duplicate facility ID found: " << id << ". Skipping this entry." << endl;
                rejected++;
                continue;
            }
        }
        // Add the current facility ID to the list of previous IDs to track duplicates
        previousIds.push_back(id);
        Facilities f(id, facilityName, buildingName, facilityType);
        facilities.push_back(f);
        accepted++;
    }

    // file load summary
    cout << "facilities.txt loaded successfully." << endl;
    cout << "Total facilities loaded: " << facilities.size() << endl;
    cout << accepted << " accepted " << rejected << " rejected" << endl;
    HashTable hashTable(facilities);
    cout << "Hash table size: " << hashTable.getTableSize() << endl;
    cout << "Total collisions in hash table: " << hashTable.getCollisions() << endl;

    // Load department tree from file
    departments.loadFromFile("departments.txt");

    CampusGraph graph;

    // Load campus graph from files
    GraphLoader::loadBuildings("buildings.txt", graph);
    GraphLoader::loadConnections("connections.txt", graph);

    cout << "\nThank you for using the Facilities Management System!";

    while (true)
    {
        cout << "\n\nPlease enter the number corresponding to the action you would like to take." << endl;
        cout << "1. View all facilities" << endl;
        cout << "2. Search facility by ID" << endl;
        cout << "3. Search facility by name" << endl;
        cout << "4. Search facility by category" << endl;
        cout << "5. View campus graph" << endl;
        cout << "6. Display graph counts and degrees" << endl;
        cout << "7. Find reachable buildings (BFS)" << endl;
        cout << "8. Find shortest path (BFS)" << endl;
        cout << "9. Add department" << endl;
        cout << "10. Search department" << endl;
        cout << "11. Display department hierarchy" << endl;
        cout << "12. Run preorder traversal" << endl;
        cout << "13. postorder traversal" << endl; // WIP
        cout << "14. level-order traversal" << endl; // WIP
        cout << "15. Department statistics" << endl; // WIP
        cout << "16. Facility category report" << endl; // WIP
		cout << "17. Graph connectivity report" << endl;
		cout << "18. Exit" << endl;

        int input;
        cin >> input;

        switch (input)
        {
        case 1:
            displayFacilities(facilities);
            break;
        case 2:
        {
            cout << "\nEnter facility ID, facility name, building name, or facility type: ";
            string searchId;
            cin.ignore();
            getline(cin, searchId);

            // search by id if string starts with f followed by a number
            if ((searchId[0] == 'F' || searchId[0] == 'f') && isdigit(searchId[1]))
            {
                // Header for the search results table
                cout << endl
                     << endl;
                cout << "+" << right << setw(14) << setfill('-') << "+" << setw(26) << "+" << setw(22) << "+" << setw(25) << "+" << endl;
                cout << left << setw(14) << setfill(' ') << "|Facility ID" << setw(26) << "|Facility Name" << setw(22) << "|Building Name" << setw(25) << "|Facility Type" << "|" << endl;
                cout << "+" << right << setw(14) << setfill('-') << "+" << setw(26) << "+" << setw(22) << "+" << setw(25) << "+" << endl;
                //
                hashTable.SearchUsingHash(searchId).displayFacility(); // Display the facility found by hash table search
                cout << "+" << right << setw(14) << setfill('-') << "+" << setw(26) << "+" << setw(22) << "+" << setw(25) << "+" << endl;
            }
            // search by name, building, or type if the string does not start with f then number
            else
            {
                vector<Facilities> results = Search(facilities, searchId);
                displayFacilities(results);
            }
            break;
        }
        case 5: 
            graph.displayGraph();
            break;

        case 6: 
            graph.displayGraphStatistics();
            break;

        case 7: 
        {
            string start;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter starting building: ";
            getline(cin, start);
            trim(start);

            if (start.empty())
                cout << "Error: Building name cannot be blank." << endl;
            else
                graph.bfsReachability(start);   // prints its own error for unknown buildings
            break;
        }
        case 8:
        {
			string start;
			string destination;

			cin.ignore(
				numeric_limits<streamsize>::max(),
				'\n');

			cout << "Enter start building: ";
			getline(cin, start);

			cout << "Enter destination building: ";
			getline(cin, destination);

			trim(start);
			trim(destination);

			if (start.empty() ||
				destination.empty())
			{
				cout << "Error: Building name cannot be blank."
					 << endl;
			}
			else
			{
				graph.shortestPath(
					start,
					destination);
			}

			break;
		}
        case 9:
        {
            string name;
            string parent;
            string error;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true)
            {
                cout << "Enter department name: ";
                getline(cin, name);
                trim(name);

                if (name.empty())
                {
                    cout << "Invalid department name. Try again." << endl;
                    continue;
                }

                parent = "NONE";

                if (!departments.isEmpty())
                {
                    cout << "Enter parent department: ";
                    getline(cin, parent);
                    trim(parent);

                    if (parent.empty())
                    {
                        cout << "Invalid parent name. Try again." << endl;
                        continue;
                    }
                }

                if (departments.addDepartment(name, parent, error))
                {
                    cout << "Department added successfully!" << endl;
                    break;
                }
                else
                {
                    cout << "Error: " << error << endl;
                    cout << "Please try again." << endl;
                }
            }
            break;
        }
        case 10:
        {
            string name;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true)
            {
                cout << "Enter department name to search: ";
                getline(cin, name);
                trim(name);

                if (name.empty())
                {
                    cout << "Invalid department name. Try again." << endl;
                    continue;
                }

                if (departments.searchDepartment(name))
                {
                    break;
                }

                cout << "Please try again." << endl;
            }
            break;
        }
        case 11:
        {
            departments.displayHierarchy();
            break;
        }

        case 12:
        {
            departments.preorderTraversal();
            break;
        }
        case 13:
            cout << "Postorder traversal is a work in progress." << endl;
            break;
        case 14:
            cout << "Level-order traversal is a work in progress." << endl;
            break;
        case 15:
            cout << "Department statistics is a work in progress." << endl;
            break;
        case 16:
            cout << "Facility category report is a work in progress." << endl;
            break;
        case 17:
            graph.displayConnectivityReport();
            break;
        case 18: 
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;
            break;
		
		
        //!!!!!!!!!!!!!
        // Only for debugging REMOVE THIS CASE IN FINAL VERSION!
        //!!!!!!!!!!!!!
		
        case 0:
            cout << "Debug commands:" << endl;
            cout << "1. display hash table" << endl;

            cin >> input;

            switch (input)
            {
            case 1:
                hashTable.DisplayHashTable();
                break;
            default:
                cout << "Invalid debug command." << endl;
                break;
            }
            break;
            //!!!!!!!!!!!!!
            // Only for debugging REMOVE THIS CASE IN FINAL VERSION!
            //!!!!!!!!!!!!!

        default:
            cout << "Invalid input. Please try again." << endl;
            break;
        }
    }

    return 0;
}
