#ifndef GRAPHLOADER_H
#define GRAPHLOADER_H

#include <string>

class CampusGraph;

class GraphLoader
{
public:

    static void loadBuildings(
        const std::string& filename,
        CampusGraph& graph);

    static void loadConnections(
        const std::string& filename,
        CampusGraph& graph);
};

#endif