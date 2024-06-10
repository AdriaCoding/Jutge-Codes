#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MOD = 1e9;

using Treap = struct Node*;

struct Node {
    int key, sum, priority;
    Treap l, r;

    Node(int key) : key(key), sum(key), priority(rand()), l(nullptr), r(nullptr) {}
};

Treap update(Treap t) {
    if (t) {
        t->sum = t->key + (t->l ? t->l->sum : 0) + (t->r ? t->r->sum : 0);
    }
    return t;
}


int main() {
    srand(time(NULL));
    int m;
    while (cin >> m && m != 0) {
        Treap root = new Node(0);
        for (int inserts = 0; inserts < m; inserts++) {
            int y, i, j;
            cin >> y >> i >> j;
            i--; j--;
        }
        cout << "----------" << endl;
    }
    return 0;
}