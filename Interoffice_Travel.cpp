#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Path {
  public:
    int from;
    int to;
    Path(int, int);
};

Path::Path(int a, int b) {
    from = a;
    to = b;
}

class Office {
  public:
    vector<int> hallways;
};

class Building {
  public:
    Building(int);
    int officeCount;
    Office *offices;
    int *W;
    void traverseHallways(vector<Path> &nodes);
    int getTotalEnergyForOffice(int);
};

Building::Building(int n) {
    officeCount = n;
    offices = new Office[n+1];
    W = new int[n];
}

void Building::traverseHallways(vector<Path> &nodes) {
    vector<Path> newNodes;
    for (Path path : nodes) {
        for (int o : offices[path.to].hallways) {
            if (o != path.from) {
                newNodes.push_back(Path(path.to, o));
            }
        }
    }
    nodes = newNodes;
}


int Building::getTotalEnergyForOffice(int j) {
    vector<Path> nodes;
    nodes.push_back(Path(0,j));
    int energy = 0;
    //cout << endl << "Meeting in office " << j << ": " << endl;
    for (int i = 0; i < officeCount; i++) {
        //cout << "Engineers travelling distance " << i << ": " << nodes.size() << endl;
        energy += nodes.size() * W[i];
        traverseHallways(nodes);
        if (nodes.size() == 0)
            break;
    }
    
    return energy;
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
        building.offices[u].hallways.push_back(v);
        building.offices[v].hallways.push_back(u);
    }

    // Print the energy expended to meet in each office.
    for (int j = 1; j <= n; j++) {
        cout << building.getTotalEnergyForOffice(j) << " ";
    }
    
    return 0;
}


