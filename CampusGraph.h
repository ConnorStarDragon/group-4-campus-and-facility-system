#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>

class CampusGraph
{
private:
    std::vector<std::string> buildings;
    std::vector<std::vector<int>> adjacencyList;

    int findBuildingIndexInternal(
        const std::string& name) const;

public:
    CampusGraph();

    bool addBuilding(
        const std::string& buildingName);

    bool addConnection(
        const std::string& buildingA,
        const std::string& buildingB);

    bool connectionExists(
        int first,
        int second) const;

    int findBuildingIndex(
        const std::string& buildingName) const;

    void displayGraph() const;

    void displayGraphStatistics() const;

    void bfsReachability(
        const std::string& startBuilding) const;

    int getBuildingCount() const;

    int getConnectionCount() const;

    int getDegree(int vertex) const;
};

#endif