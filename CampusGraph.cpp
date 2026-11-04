/*

    Implements:
    - Undirected campus graph
    - Graph display
    - Graph statistics
    - BFS reachability
*/

#include "CampusGraph.h"

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

namespace
{
    string toLowerCase(string text)
    {
        transform(
            text.begin(),
            text.end(),
            text.begin(),
            ::tolower
        );

        return text;
    }
}

CampusGraph::CampusGraph()
{
}

int CampusGraph::findBuildingIndexInternal(
    const string& name) const
{
    string target = toLowerCase(name);

    for (size_t i = 0; i < buildings.size(); i++)
    {
        if (toLowerCase(buildings[i]) == target)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int CampusGraph::findBuildingIndex(
    const string& name) const
{
    return findBuildingIndexInternal(name);
}

bool CampusGraph::addBuilding(
    const string& buildingName)
{
    if (findBuildingIndex(buildingName) != -1)
    {
        return false;
    }

    buildings.push_back(buildingName);
    adjacencyList.push_back(vector<int>());

    return true;
}

bool CampusGraph::connectionExists(
    int first,
    int second) const
{
    for (int neighbor : adjacencyList[first])
    {
        if (neighbor == second)
        {
            return true;
        }
    }

    return false;
}

bool CampusGraph::addConnection(
    const string& buildingA,
    const string& buildingB)
{
    int first =
        findBuildingIndex(buildingA);

    int second =
        findBuildingIndex(buildingB);

    if (first == -1 || second == -1)
    {
        return false;
    }

    if (first == second)
    {
        return false;
    }

    if (connectionExists(first, second))
    {
        return false;
    }

    adjacencyList[first].push_back(second);
    adjacencyList[second].push_back(first);

    return true;
}

void CampusGraph::displayGraph() const
{
    cout << "\n===== CAMPUS GRAPH =====\n";

    if (buildings.empty())
    {
        cout << "No buildings loaded.\n";
        return;
    }

    for (size_t i = 0; i < buildings.size(); i++)
    {
        cout << buildings[i] << "\n";

        if (adjacencyList[i].empty())
        {
            cout << "   (no connections)\n";
            continue;
        }

        for (int neighbor : adjacencyList[i])
        {
            cout << "   -> "
                 << buildings[neighbor]
                 << "\n";
        }
    }
}

int CampusGraph::getBuildingCount() const
{
    return static_cast<int>(
        buildings.size());
}

int CampusGraph::getConnectionCount() const
{
    int total = 0;

    for (const auto& neighbors : adjacencyList)
    {
        total += neighbors.size();
    }

    return total / 2;
}

int CampusGraph::getDegree(
    int vertex) const
{
    if (vertex < 0 ||
        vertex >= static_cast<int>(buildings.size()))
    {
        return 0;
    }

    return adjacencyList[vertex].size();
}

void CampusGraph::displayGraphStatistics() const
{
    cout << "\n===== GRAPH STATISTICS =====\n";

    cout << "Total Buildings: "
         << getBuildingCount()
         << "\n";

    cout << "Total Connections: "
         << getConnectionCount()
         << "\n\n";

    for (size_t i = 0; i < buildings.size(); i++)
    {
        cout << buildings[i]
             << " -> Degree "
             << getDegree(i)
             << "\n";
    }
}

void CampusGraph::bfsReachability(
    const string& startBuilding) const
{
    int start =
        findBuildingIndex(startBuilding);

    if (start == -1)
    {
        cout << "\nUnknown building: "
             << startBuilding
             << "\n";

        return;
    }

    vector<bool> visited(
        buildings.size(),
        false);

    vector<int> distance(
        buildings.size(),
        -1);

    queue<int> q;

    visited[start] = true;
    distance[start] = 0;

    q.push(start);

    int reachable = 0;

    cout << "\n===== BFS REACHABILITY =====\n";

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        reachable++;

        cout << buildings[current]
             << " (distance "
             << distance[current]
             << ")\n";

        for (int neighbor :
             adjacencyList[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;

                distance[neighbor] =
                    distance[current] + 1;

                q.push(neighbor);
            }
        }
    }

    cout << "\nReachable: "
         << reachable
         << " of "
         << buildings.size()
         << " buildings\n";
}