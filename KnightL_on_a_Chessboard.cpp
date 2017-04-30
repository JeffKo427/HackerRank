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

struct Node {
  public: 
    int m,n;
    Square(int,int);
    Node *parent;
    vector<Node *> children;
};

Node::Node(int a, int b) {
    m = a;
    n = b;
}

void clearChessboard(bool **chessboard, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            chessboard[i][j] = false;
        }
    }
}

int main(){
    int n;
    cin >> n;
    // your code goes here
    bool chessboard[][] = new bool[n][n];
    for (int a = 1; a < n; a++) {
        for (int b = a; b < n; b++) {
            clearChessboard(chessboard, n);
            Node root = Node(0,0);
            chessboard[0][0] = true;
            
        }
    }
    return 0;
}
