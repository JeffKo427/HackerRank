#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

class Office {
  public:
    int self;
    vector<int> children;
    int parent;
    int nDescendants;
    int *descendantsByLevel;
    void show();
};

void Office::show() {
    cout << "Office #" << self << endl;
    cout << "Children: ";
    for (int c : children)
        cout << c << " ";
    cout << endl << "descendantsByLevel: ";
    for (int i = 0; i <= nDescendants; i++)
        cout << descendantsByLevel[i] << " ";
    cout << endl;
}

class Building {
  public:
    Building(int);
    int officeCount;
    Office *offices;
    int *W;
    int getTotalEnergyForOffice(int);
    void getNodesWithin(int j, int nodesWithin[]);
    void populateDescendants(int);
    void defineAndSolveForRoot(int, int);
};

Building::Building(int n) {
    officeCount = n;
    offices = new Office[n+1];
    for (int i = 0; i < n+1; i++)
        offices[i].self = i;
    W = new int[n];
}


int Building::getTotalEnergyForOffice(int j) {
    int energy = 0;
    int *nodesWithin = new int[officeCount];
    for (int i = 0; i < officeCount; i++)
        nodesWithin[i] = 0;
    getNodesWithin(j, nodesWithin);
    //printArray(nodesWithin, officeCount);
    for (int i = 0; i < officeCount; i++) {
        energy += nodesWithin[i] * W[i];
    }
    
    return energy;
}

void Building::getNodesWithin(int j, int nodesWithin[]) {
    if (offices[j].parent == -1) {
        for (int i = 0; i <= offices[j].nDescendants; i++) {
            nodesWithin[i] = offices[j].descendantsByLevel[i];
        }
    } else {
        getNodesWithin(offices[j].parent, nodesWithin);
        //printArray(nodesWithin, officeCount);
        for (int i = 1; i <= offices[j].nDescendants + 1; i++) {
            nodesWithin[i] = nodesWithin[i] - offices[j].descendantsByLevel[i-1];
        }
        for (int i = officeCount - 1; i > 0; i--) {
            if (i <= offices[j].nDescendants + 1)
                nodesWithin[i] = nodesWithin[i-1] + offices[j].descendantsByLevel[i];
            else
                nodesWithin[i] = nodesWithin[i-1];
        } 
    }
}

void Building::populateDescendants(int o) {
    offices[o].nDescendants = 0;
    for (int c : offices[o].children) {
        if (offices[c].nDescendants+1 > offices[o].nDescendants) {
            offices[o].nDescendants = offices[c].nDescendants+1;
        }
    }
    offices[o].descendantsByLevel = new int[offices[o].nDescendants + 1];
    offices[o].descendantsByLevel[0] = 1;
    offices[o].descendantsByLevel[1] = offices[o].children.size();
    //cout << endl << o << ":" << offices[o].children.size();
    if (offices[o].nDescendants > 1) {
        for (int c : offices[o].children) {
            for (int i = 2; i <= offices[c].nDescendants+1; i++) {
                offices[o].descendantsByLevel[i] += offices[c].descendantsByLevel[i-1];
            }
        }
    }
}

void Building::defineAndSolveForRoot(int o, int p) {
    // Erase the parent from the children and set it as the parent.
    if (p != -1)
        offices[o].children.erase(std::remove(offices[o].children.begin(), offices[o].children.end(), p), offices[o].children.end());
    offices[o].parent = p;
    // Recursively determine nDescendants.
    if (offices[o].children.size()) {
        for (int c : offices[o].children) {
            defineAndSolveForRoot(c, o);
        }
        populateDescendants(o);
        //offices[o].show();
    } else {
        offices[o].nDescendants = 0;
        offices[o].descendantsByLevel = new int[1];
        offices[o].descendantsByLevel[0] = 1;
        //offices[o].show();
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
    building.defineAndSolveForRoot(1,-1);
    for (int j = 1; j <= n; j++) {
        //building.offices[j].show();
        cout << building.getTotalEnergyForOffice(j) << " ";
    }
    
    return 0;
}

