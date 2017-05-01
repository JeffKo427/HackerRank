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
    vector<int> x(n);
    for (int x_i = 0;x_i < n;x_i++) {
        cin >> x[x_i];
    }
    vector<int> transmitters;
    sort(x.begin(), x.end());
    
    int idealPlacement = x.front() + k;
    int previousHouse, nextHouse;
    for (int house : x) {
        //cout << house << " ";
        nextHouse = 0;
        for (int i = 0; i < n; i++) {
            if (x.at(i) > house + k) {
                nextHouse = x.at(i);
                break;
            }
        }
        if (house == idealPlacement) {
            transmitters.push_back(house);
            idealPlacement = max(nextHouse + k, house + 1 + 2*k);
        } else if (house > idealPlacement) {
            transmitters.push_back(previousHouse);
            idealPlacement = max(nextHouse + k, house + 1 + 2*k);
        }
        previousHouse = house;
    }
    if (previousHouse > (transmitters.back() + k))
        transmitters.push_back(previousHouse);
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
