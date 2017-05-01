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
    Node(int,int);
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

bool notOutOfBounds(int x, int y, int n) {
    return x > 0 && y > 0 && y < n-1 && x < n-1;
}

Node *graphMoves(Node *root, int a, int b, bool **chessboard, int n) {
    // add all non-repeat moves to tree
    bool movesAdded = false;
    // always eight possible moves: +a+b, +a-b, -a+b, -a-b where a in x b in y and same where a in y b in x
    int moves[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
    int newPos[2];
    Node* node = root;
    if (node->children.size()) {
        for (Node* child : node->children) {
            node = graphMoves(child, a, b, chessboard, n);
        }
    }
        
    for (int *move : moves) {
        newPos[0] = root->m + a * move[0];
        newPos[1] = root->n + b * move[1];
        if (notOutOfBounds(newPos[0],newPos[1],n) && !chessboard[newPos[0]][newPos[1]]) {
            movesAdded = true;
            Node *temp = new Node(newPos[0], newPos[1]);
            temp->parent = root;
            root->children.push_back(temp);
            if (newPos[0] == n-1 && newPos[1] == n-1) {
                return temp;
            }
        }
        newPos[0] = root->m + b * move[0];
        newPos[1] = root->n + a * move[1];
        if (notOutOfBounds(newPos[0],newPos[1],n) && !chessboard[newPos[0]][newPos[1]]) {
            movesAdded = true;
            Node *temp = new Node(newPos[0], newPos[1]);
            temp->parent = root;
            root->children.push_back(temp);
            if (newPos[0] == n-1 && newPos[1] == n-1) {
                return temp;
            }
        }
    }
    
    if (movesAdded) {
        node = graphMoves(root, a, b, chessboard, n);
    }
    return node;
}

int getDepth(Node *leaf, Node *root, int depth) {
    if (leaf == root) {
        return depth;
    } else {
        depth = getDepth(leaf->parent, root, depth+1);
    }
    
    return -1;
}

int main(){
    int n;
    cin >> n;
    // your code goes here
    bool **chessboard = new bool*[n];
    for(int i = 0; i < n; ++i) {
        chessboard[i] = new bool[n];
    }
    Node *solution;
    for (int a = 1; a < n; a++) {
        for (int b = 1; b < n; b++) {
            clearChessboard(chessboard, n);
            Node *root = new Node(0,0);
            chessboard[0][0] = true;
            solution = graphMoves(root, a, b, chessboard, n);
            cout << getDepth(solution, root, 0) << " ";
        }
        cout << endl;
    }
    
    return 0;
}
