#include <string>
#include <vector>


using namespace std;
class Facilities {
    private:
        string id;
        string facilityName;
        string buildingName;
        string facilityType;
    public:
        Facilities(string id, string facilityName, string buildingName, string facilityType); // Constructor

        string getId() const; // Get the facility ID

        string getFacilityName() const; // Get the facility name

        string getBuildingName() const; // Get the building name

        string getFacilityType() const; // Get the facility type

        void displayFacility() const; // Display the facility details
    };

        string StringToLower(const string& str); // Convert a string to lowercase

        void displayFacilities(const vector<Facilities>& facilities); // Display all facilities in the vector

        vector<Facilities> Search(const vector<Facilities>& facilities, string id); // Search for facilities by ID