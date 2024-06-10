#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MOD = 1e9;

using Treap = struct Node*;

struct Node {
    int key, sum, size;
    Treap l, r;

    Node(int key) : key(key), sum(key), size(1), l(nullptr), r(nullptr) {}
};

void update(Treap t) {
    if (t) {
        t->size = 1;
        t->sum = t->key;
        if (t->l) {
            t->size += t->l->size;
            t->sum = (t->sum + t->l->sum) % MOD;
        }
        if (t->r) {
            t->size += t->r->size;
            t->sum = (t->sum + t->r->sum) % MOD;
        }
    }
}
void print_tree(Treap t) {
    if (!t) return;
    print_tree(t->l);
    std::cout << "Key: " << t->key << ", Sum: " << t->sum << ", Size: " << t->size << "\n";
    print_tree(t->r);
}

bool insert(Treap& t, int key) {
    if (!t) {
        t = new Node(key);
        return false;
    }
    if (key == t->key) {
        return true;
    }
    bool isPresent;
    if (key < t->key) {
        isPresent = insert(t->l, key);
        if (t->l->key > t->key) {
            Treap temp = t->l;
            t->l = temp->r;
            temp->r = t;
            t = temp;
            update(t->r);
        }
    } else {
        isPresent = insert(t->r, key);
        if (t->r->key > t->key) {
            Treap temp = t->r;
            t->r = temp->l;
            temp->l = t;
            t = temp;
            update(t->l);
        }
    }
    update(t);
    return isPresent;
}

int sum_range(Treap t, int i, int j) {
    if (!t || i > j) return 0;
    if (i == 1 && j == t->size) return t->sum;
    int left_size = t->l ? t->l->size : 0;
    if (j <= left_size) return sum_range(t->l, i, j)%MOD;
    if (i > left_size + 1) return sum_range(t->r, i - left_size - 1, j - left_size - 1)%MOD;
    return ((t->l ? sum_range(t->l, i, left_size) : 0) + t->key + (t->r ? sum_range(t->r, 1, j - left_size - 1) : 0)) % MOD;
}

int find_ith (int i, Treap t) {
    if (!t) return 0;
    int s = t->l ? t->l->size : 0;
    if (i < s) return find_ith(i, t->l);
    if (i > s) return find_ith(i - s - 1, t->r);
    return t->sum;
}

int main() {
    srand(time(NULL));
    int m;
    while (cin >> m && m != 0) {
        Treap root = new Node(0);
        for (int inserts = 0; inserts < m; inserts++) {
            int y, i, j;
            cin >> y >> i >> j;
            print_tree(root);
            cout << "sum_range: " << sum_range(root, i, j) << endl;
            cout << "find_ith: " << find_ith(i, root) << endl;
            cout << "find_jth: " << find_ith(j, root) << endl;
            int z = (y + sum_range(root, i, j)) % MOD;
            if (insert(root, z)) {
                std::cout << "R " << z << "\n";
            } else {
                std::cout << "I " << z << "\n";
            }
        }
        cout << "----------" << endl;
    }
    return 0;
}