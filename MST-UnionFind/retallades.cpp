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
    if (parent[x] == x) return x;
    int res = repre(parent[x]);
    parent[x] = res ;
    return res ;
}

void solve(int n, vector<Edge>& G) {
    sort(G.begin(), G.end());

    parent = vector<int>(n);
    for (int i = 0; i < n; i++) parent[i] = i;

    int savings = 0;
    for (Edge& e : G) {
        int rx = repre(e.x), ry = repre(e.y);
        if (rx != ry) {
            parent[rx] = ry;
        }
        else {
            savings += e.c;
        }
    }
    cout << savings << endl;
}

int main() {
    int n, m;
    while(cin >> n >> m){
        vector<Edge> G(m);
        for (int i = 0; i < m; i++) {
            cin >> G[i].x >> G[i].y >> G[i].c;
        }
        solve(n, G);
    }

}