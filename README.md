# group-4-campus-and-facility-system

A terminal-based campus management system built in C++ to easily look up facilities, explore campus buildings, and view the department hierarchy

## Features

- **View Facilities:** displays an organized table of all facilities and their details
- **Search Facility by ID:** finds a facility using a custom hash table
- **View Campus Graph:** displays every building and the buildings it connects to, along with counts and degrees
- **Find Reachable Buildings:** runs a breadth-first search from a chosen building and shows how far each building is
- **Department Hierarchy:** adds, searches, and displays departments, and runs a preorder traversal
- **Clean Menus:** all tables and menus are well formatted with relevant clean headers

## Running the code

The code was built in C++ and compiled using g++.

Build from the project root:

```
g++ main.cpp Facilities.cpp HashTable.cpp CampusGraph.cpp GraphLoader.cpp department.cpp -o campus
```

Run:

```
./campus
```

## Common Commands

Uses numbers in the console to control the program. All usable commands are shown in the menu

*With the exception of '0' to access debug commands*
