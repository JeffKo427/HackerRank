#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Office {
  public:
    vector<int> children;
    int parent;
    int nDescendants;
    int *descendantsByLevel;
    
};

class Building {
  public:
    Building(int);
    int officeCount;
    Office *offices;
    int *W;
    int getTotalEnergyForOffice(int);
    void getNodesWithin(int j, int &nodesWithin);
    void populateDescendants(int);
    void defineAndSolveForRoot(int);
};

Building::Building(int n) {
    officeCount = n;
    offices = new Office[n+1];
    W = new int[n];
}


int Building::getTotalEnergyForOffice(int j) {
    int energy = 0;
    int *nodesWithin = new int[officeCount];
    getNodesWithin(j, nodesWithin);
    for (int i = 0; i < officeCount; i++) {
        energy += nodesWithin[i] * W[i];
    }
    
    return energy;
}

void Building::getNodesWithin(int j, int &nodesWithin) {
    if (offices[j].parent == 0) {
        nodesWithin = offices[j].nDescendants;
    } else {
        getNodesWithin(offices[j].parent, nodesWithin);
        for (int i = 1; i < offices[j].nDescendants; i++) {
            nodesWithin[i] = nodesWithin[i] - offices[j].descendantsByLevel[i-1];
        }
        for (int i = 1; i < offices[j].nDescendants; i++) {
            nodesWithin[i] = nodesWithin[i-1] + offices[j].descendantsByLevel[i]
        }
    }
}

void Building::populateDescendants(int o) {
    offices[o].nDescendants = max_element(offices[o].children.begin(), offices[o].children.end()) + 1;
    offices[o].descendantsByLevel = new int[offices[o].nDescendants + 1];
    offices[o].descendantsByLevel[0] = 1;
    offices[o].descendantsByLevel[1] = offices[o].children.size();
    if (offices[o].nDescendants > 1) {
        for (int c : children) {
            for (int i = 1; i < offices[c].nDescendants; i++) {
                offices[o].descendantsByLevel[i] += offices[c].descendantsByLevel[i-1];
            }
        }
    }
}

void Building::defineAndSolveForRoot(int o, int p) {
    // Erase the parent from the children and set it as the parent.
    if (p)
        offices[o].children.erase(std::remove(vec.begin(), vec.end(), p), vec.end());
    offices[o].parent = p;
    // Recursively determine nDescendants.
    if (offices[o].children.size()) {
        for (int c : offices[o].children) {
            defineAndSolveForRoot(c, o);
        }
        populateDescendants(o);
    } else {
        offices[o].nDescendants = 0;
    }   
}

int main() {
    // Read in the number of offices and the array of energy expenditures.
    int n;
    cin >> n;
    Building building(n);
    for (int i = 0; i < n; i++) {
        cin >> building.W[i];
    }

    // Read in the tree that defines the office building.
    int u,v;
    for (int i = 0; i < n-1; i++) {
        cin >> u >> v;
        building.offices[u].children.push_back(v);
        building.offices[v].children.push_back(u);
    }

    // Print the energy expended to meet in each office.
    building.offices[0].parent = 0;
    building.defineAndSolveForRoot(0);
    for (int j = 1; j <= n; j++) {
        cout << building.getTotalEnergyForOffice(j) << " ";
    }
    
    return 0;
}

