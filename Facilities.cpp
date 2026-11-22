#include <iostream>
#include <iomanip>

#include "Facilities.h"

using namespace std;

//===========================================
//            Facilities Class
//===========================================

// Constructor
Facilities::Facilities(string id, string facilityName, string buildingName, string facilityType) {
    this->id = id;
    this->facilityName = facilityName;
    this->buildingName = buildingName;
    this->facilityType = facilityType;
}

// Get the facility ID
string Facilities::getId() const {
    return id;
}

// Get the facility name
string Facilities::getFacilityName() const {
    return facilityName;
}

// Get the building name
string Facilities::getBuildingName() const {
    return buildingName;
}

// Get the facility type
string Facilities::getFacilityType() const {
    return facilityType;
}

// Display the facility details individually
void Facilities::displayFacility() const {
    cout << left << setw(14) << setfill(' ') << "|" + id
         << setw(26) << "|" + facilityName
         << setw(22) << "|" + buildingName
         << setw(25) << "|" + facilityType
         << "|" << endl;
}

//===========================================
//            utility functions
//===========================================

// Convert a string to lowercase for easier comparing
string StringToLower(const string& str) {
    string lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}

// Display all facilities in the vector
void displayFacilities(const vector<Facilities>& facilities) {
    // Check if the vector is empty before displaying the table for displayign searches
    if (facilities.empty()) {
        cout << "No facilities found matching the search criteria." << endl;
        return;
    }

    // Display the table header for the facilities
    cout << endl << endl;
    cout << "+" << right << setw(14) << setfill('-') << "+" << setw(26) << "+" << setw(22) << "+" << setw(25) << "+" << endl;
    cout << left << setw(14) << setfill(' ') << "|Facility ID" << setw(26) << "|Facility Name" << setw(22) << "|Building Name" << setw(25) << "|Facility Type" << "|" << endl;
    cout << "+" << right << setw(14) << setfill('-') << "+" << setw(26) << "+" << setw(22) << "+" << setw(25) << "+" << endl;
    //
    // Display each facility in the vector at a time
    for (const Facilities& f : facilities)
    {
        f.displayFacility();
        cout << "+" << right << setw(14) << setfill('-') << "+" << setw(26) << "+" << setw(22) << "+" << setw(25) << "+" << endl;
    }
}

// Search for facilities by name, building, or type
vector<Facilities> Search(const vector<Facilities>& facilities, string id) {
    vector<Facilities> results;
    id = StringToLower(id);
    for (const Facilities& f : facilities) {
        // Convert the facility details to lowercase for easier comparison
        string facilityName = StringToLower(f.getFacilityName());
        string buildingName = StringToLower(f.getBuildingName());
        string facilityType = StringToLower(f.getFacilityType());
        // Check if any part of the facility matches search criteria
        if (facilityName == id || buildingName == id || facilityType == id) {
            results.push_back(f); // Add the matching facility to the results vector
        }
    }
    return results;
}

void FacilityCategoryReport(const vector<Facilities>& facilities) {
    vector<Categories> categories; // Vector to store unique facility categories and their counts
    int total = facilities.size(); // Total number of facilities
    for (Facilities f : facilities) {
        string category = f.getFacilityType();
        bool found = false;
        for (Categories& c : categories) {
            if (c.categoryName == category) {
                c.count++; // Increment the count if the category already exists
                found = true;
                break;
            }
        }
        if (!found) {
            Categories newCategory; // Create a new category if it doesn't exist
            newCategory.categoryName = category;
            newCategory.count = 1;
            categories.push_back(newCategory);
        }
    }

    cout << "\nFacility Category Report:\n";
    cout << "+--------------------------+-------+------------+\n";
    cout << "| Facility Category        | Count | Percentage |\n";
    cout << "+--------------------------+-------+------------+\n";
    for (const Categories& c : categories) {
        double percentage = (double)c.count / total * 100;
        cout << "| " << left << setw(24) << c.categoryName << " | " << right << setw(5) << c.count << " | " << fixed << setprecision(2) << setw(8) << percentage << " % |\n";
    }
    cout << "+--------------------------+-------+------------+\n";

}
