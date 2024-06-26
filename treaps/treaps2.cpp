#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MOD = 1e9;

using Treap = struct Node*;

struct Node {
    int key, priority, sum, size;
    Treap l, r;

    Node(int key) : key(key), priority(rand()), sum(key), size(1), l(nullptr), r(nullptr) {}
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
    cout << "   Left: " << (t->l ? t->l->key : -1) << ", Right: " << (t->r ? t->r->key : -1) << endl;
    print_tree(t->r);
}

void print_set(Treap t) {
    if (!t) return;
    print_set(t->l);
    std::cout << t->key << "(" << t->sum << ") , ";
    print_set(t->r);
}


void rotate_right(Treap& t) {
    Treap temp = t->l;
    t->l = temp->r;
    temp->r = t;
    t = temp;
    update(t->r);
    update(t);
}

void rotate_left(Treap& t) {
    Treap temp = t->r;
    t->r = temp->l;
    temp->l = t;
    t = temp;
    update(t->l);
    update(t);
}

bool insert(Treap& t, int key) {
    if (!t) {
        t = new Node(key);
        return true;
    }
    if (key == t->key) {
        return false;
    }
    bool inserted;
    if (key < t->key) {
        inserted = insert(t->l, key);
        if (t->l && t->l->priority > t->priority) {
            rotate_right(t);
        }
    } else {
        inserted = insert(t->r, key);
        if (t->r && t->r->priority > t->priority) {
            rotate_left(t);
        }
    }
    update(t);
    return inserted;
}

int sum_range(Treap t, int i, int j) {
    if (!t || i > j) return 0;
    if (i == 1 && j == t->size) return t->sum;
    int left_size = t->l ? t->l->size : 0;
    if (j <= left_size) return sum_range(t->l, i, j)%MOD;
    if (i > left_size + 1) return sum_range(t->r, i - left_size - 1, j - left_size - 1)%MOD;

    int left_range = t->l ? sum_range(t->l, i, left_size)%MOD : 0;
    int right_range = t->r ? sum_range(t->r, max(1, i - left_size - 1), j - left_size - 1)%MOD : 0;
    return ((left_range + t->key)%MOD + right_range) % MOD;
}

int main() {
    srand(0);
    int m;
    while (cin >> m && m != 0) {
        Treap root = new Node(0);
        for (int inserts = 0; inserts < m; inserts++) {
            int y, i, j;
            cin >> y >> i >> j;
            
            //print_tree(root);
            //cout << "sum_range " << i << " " << j << ": "<< sum_range(root, i, j) << endl;            
            int z = (y + sum_range(root, i, j)) % MOD;
            if (!insert(root, z)) {
                std::cout << "R " << z << "\n";
            } else {
                std::cout << "I " << z << "\n";
            }
        }
        //cout << " The full set is: "; print_set(root); cout << endl;
        //print_tree(root);
        cout << "----------" << endl;
        delete root;
    }
    return 0;
}