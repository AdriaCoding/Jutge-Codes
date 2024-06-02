#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int x, y, c;
    // Overload the "<" operator for sorting
    bool operator<(const Edge& other) const {
        return c < other.c;
    }
};

vector<int> parent; // stores the parent of each node

int repre(int x) {
    return (parent[x] == -1 ? x : parent[x] = repre(parent[x]));
}

vector<Edge> spanning_tree(int n, vector<Edge>& G) {
    int G_size = G.size();
    vector<Edge> T;
    parent = vector<int>(n, -1);
    
    sort(G.begin(), G.end());
    
    for (int i = 0; n > 1 && i < G_size; i++) {
        int rx = repre(G[i].x), ry = repre(G[i].y);
        if (rx != ry) {
            parent[rx] = ry;
            n--;
            T.push_back(G[i]);
        }
    }
    return T;
}
 
int main() {
    int n, m;
    while(cin >> n >> m){
        vector<Edge> G(m);
        for (int i = 0; i < m; i++) {
            cin >> G[i].x >> G[i].y >> G[i].c;
        }
        vector<Edge> T = spanning_tree(n, G);
        cout << "Spanning Tree:" << endl;
        for (int i = 0; i < T.size(); i++) {
            cout << i << ": " << T[i].x << " " << T[i].y << " " << T[i].c << endl;
        }cout << endl;
    }
}