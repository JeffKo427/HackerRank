#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    int k;
    cin >> n >> k;
    vector<int> houses(n);
    for (int x_i = 0;x_i < n;x_i++) {
        cin >> houses[x_i];
    }
    vector<int> transmitters;
    sort(houses.begin(), houses.end());
    
    // Delete all duplicates from x
    houses.erase( unique( houses.begin(), houses.end() ), houses.end() );
    //cout << houses.size() << endl;
    
    int distanceToLastTransmitter, prev;
    for (int i = 0; i < houses.size(); i++) {
        if (transmitters.size())
            distanceToLastTransmitter = houses.at(i) - transmitters.back();
        else
            distanceToLastTransmitter = k + i + 1;
        
        if (distanceToLastTransmitter > k) {
            prev = i;
            for (int j = i+1; j < houses.size(); j++) {
                if (houses.at(j) - houses.at(i) > k) {
                    break;
                }
                prev = j;
            }
            transmitters.push_back(houses.at(prev));
        }
    }
    
    /*
    cout << endl;
    for (int t : transmitters) {
        cout << t << " ";
    }
    cout << endl;
    */
    cout << transmitters.size();
    
    return 0;
}
