#include<bits/stdc++.h>
using namespace std;

struct node {
    double l, r, yl, yr, y;
    bool flag;
};

vector<node> tree(400010);
vector<double> X;

void build(int i, int l, int r) {
    tree[i].l = X[l];
    tree[i].r = X[r];
    tree[i].flag = false;
    if(l + 1 == r) return;
    int mid = (l + r) >> 1;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid, r);
}

void push_up(int i) {
    if(tree[i].flag) {
        tree[i].y = max(tree[i << 1].y, tree[i << 1 | 1].y);
    } else {
        tree[i].y = tree[i << 1].y;
    }
}

void update(int i, node val) {
    double mid = (tree[i].l + tree[i].r) / 2;
    if(val.l <= tree[i].l && tree[i].r <= val.r) {
        if(val.yl > val.yr) {
            tree[i].y = val.yl + (val.yr - val.yl) * (mid - val.l) / (val.r - val.l);
        } else {
            tree[i].y = val.yr - (val.yr - val.yl) * (val.r - mid) / (val.r - val.l);
        }
        tree[i].flag = true;
        return;
    }
    if(tree[i].flag) {
        tree[i << 1].y = tree[i].y;
        tree[i << 1 | 1].y = tree[i].y;
        tree[i << 1].flag = true;
        tree[i << 1 | 1].flag = true;
        tree[i].flag = false;
    }
    if(val.l < mid) update(i << 1, val);
    if(val.r > mid) update(i << 1 | 1, val);
    push_up(i);
}

double query(int i, double x) {
    if(tree[i].l + 1 == tree[i].r) return tree[i].y;
    double mid = (tree[i].l + tree[i].r) / 2;
    if(tree[i].flag) {
        tree[i << 1].y = tree[i].y;
        tree[i << 1 | 1].y = tree[i].y;
        tree[i << 1].flag = true;
        tree[i << 1 | 1].flag = true;
        tree[i].flag = false;
    }
    if(x < mid) return query(i << 1, x);
    else return query(i << 1 | 1, x);
}

int main() {
    int n;
    while(cin >> n) {
        X.clear();
        for(int i = 1; i <= n; i++) {
            char op;
            cin >> op;
            if(op == 'A') {
                node tmp;
                cin >> tmp.l >> tmp.r >> tmp.yl >> tmp.yr;
                X.push_back(tmp.l);
                X.push_back(tmp.r);
            } else {
                double x;
                cin >> x;
                X.push_back(x);
            }
        }
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        build(1, 0, X.size() - 1);
        for(int i = 1; i <= n; i++) {
            char op;
            cin >> op;
            if(op == 'A') {
                node tmp;
                cin >> tmp.l >> tmp.r >> tmp.yl >> tmp.yr;
                update(1, tmp);
            } else {
                double x;
                cin >> x;
                printf("%.3lf\n", query(1, x));
            }
        }
    }
    return 0;
}