/*

    Loads:
    - buildings.txt
    - connections.txt

    
*/

#include "GraphLoader.h"
#include "CampusGraph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

namespace
{
    string trim(const string& text)
    {
        size_t start =
            text.find_first_not_of(
                " \t\r\n");

        if (start == string::npos)
        {
            return "";
        }

        size_t end =
            text.find_last_not_of(
                " \t\r\n");

        return text.substr(
            start,
            end - start + 1);
    }

    string toLowerCase(string text)
    {
        transform(
            text.begin(),
            text.end(),
            text.begin(),
            ::tolower);

        return text;
    }

    bool isCommentLine(
        const string& line)
    {
        string temp = trim(line);

        return !temp.empty()
            && temp[0] == '#';
    }
}

void GraphLoader::loadBuildings(
    const string& filename,
    CampusGraph& graph)
{
    ifstream file(filename);

    int accepted = 0;
    int rejected = 0;

    if (!file)
    {
        cout << "Error opening "
             << filename
             << "\n";

        return;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;

        line = trim(line);

        if (line.empty() ||
            isCommentLine(line))
        {
            continue;
        }

        if (graph.addBuilding(line))
        {
            accepted++;
        }
        else
        {
            rejected++;

            cout << "Warning: "
                 << filename
                 << " line "
                 << lineNumber
                 << ": duplicate building\n";
        }
    }

    cout << filename
         << ": "
         << accepted
         << " accepted, "
         << rejected
         << " rejected\n";
}

void GraphLoader::loadConnections(
    const string& filename,
    CampusGraph& graph)
{
    ifstream file(filename);

    int accepted = 0;
    int rejected = 0;

    if (!file)
    {
        cout << "Error opening "
             << filename
             << "\n";

        return;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;

        line = trim(line);

        if (line.empty() ||
            isCommentLine(line))
        {
            continue;
        }

        stringstream ss(line);

        string buildingA;
        string buildingB;

        if (!getline(ss,
            buildingA,
            '|'))
        {
            rejected++;
            continue;
        }

        if (!getline(ss,
            buildingB,
            '|'))
        {
            rejected++;
            continue;
        }

        buildingA = trim(buildingA);
        buildingB = trim(buildingB);

        if (buildingA.empty() ||
            buildingB.empty())
        {
            rejected++;

            cout << "Warning: "
                 << filename
                 << " line "
                 << lineNumber
                 << ": empty field\n";

            continue;
        }

        if (toLowerCase(buildingA)
            ==
            toLowerCase(buildingB))
        {
            rejected++;

            cout << "Warning: "
                 << filename
                 << " line "
                 << lineNumber
                 << ": self connection\n";

            continue;
        }

        if (graph.addConnection(
                buildingA,
                buildingB))
        {
            accepted++;
        }
        else
        {
            rejected++;

            cout << "Warning: "
                 << filename
                 << " line "
                 << lineNumber
                 << ": invalid or duplicate connection\n";
        }
    }

    cout << filename
         << ": "
         << accepted
         << " accepted, "
         << rejected
         << " rejected\n";
}