#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;
int n, q, a[MAXN], tree[4 * MAXN], lazy[4 * MAXN];

void build(int node, int start, int end) {
    lazy[node] = 0; // Initialize lazy array
    if (start == end) {
        tree[node] = a[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void propagate(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void updateRange(int node, int start, int end, int l, int r, int val) {
    propagate(node, start, end);
    if (start > end || start > r || end < l)
        return;
    if (start >= l && end <= r) {
        tree[node] += (end - start + 1) * val;
        if (start != end) {
            lazy[2 * node] += val;
            lazy[2 * node + 1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(2 * node, start, mid, l, r, val);
    updateRange(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int queryIndex(int node, int start, int end, int sum) {
    propagate(node, start, end);
    if (start == end) {
        return start;
    }
    int mid = (start + end) / 2;
    propagate(2 * node, start, mid);
    if (sum <= tree[2 * node]) {
        return queryIndex(2 * node, start, mid, sum);
    } else {
        return queryIndex(2 * node + 1, mid + 1, end, sum - tree[2 * node]);
    }
}

int querySingle(int node, int start, int end, int idx) {
    propagate(node, start, end);
    if (start == end) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    if (idx <= mid) {
        return querySingle(2 * node, start, mid, idx);
    } else {
        return querySingle(2 * node + 1, mid + 1, end, idx);
    }
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void displayArray(int n) {
    cout << "Weight array with: ";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main() {
    while (cin >> n >> q) {
        fill(a, a + n + 1, 1);
        fill(tree, tree + 4 * n, 0);
        fill(lazy, lazy + 4 * n, 0);
        build(1, 1, n);
        while (q--) {
            int x, correct;
            cin >> x >> correct;
            int idx = queryIndex(1, 1, n, x + 1);
            if (correct) {
                updateRange(1, 1, n, idx, idx, -1);
                if (querySingle(1, 1, n, idx) == 0) {
                    updateRange(1, 1, n, 1, n, 1);
                }
            } else {
                updateRange(1, 1, n, idx, idx, 1);
                displayArray(n);
                if (querySingle(1, 1, n, idx) == 2) {
                    cout << querySingle(1, 1, n, idx) << "Decreaing size" << endl;
                    for (int i = 1; i <= n; i++) {
                        updateRange(1, 1, n, i, i, -1);
                    }
                }
                displayArray(n);
            }
        }
        int totalSum = tree[1];
        if (totalSum == 0) {
            totalSum = 1; // Avoid division by zero
        }
        for (int i = 1; i <= n; i++) {
            int val = querySingle(1, 1, n, i);
            int commonDivisor = gcd(val, totalSum);
            int num = val / commonDivisor;
            int den = totalSum / commonDivisor;
            cout << num << "/" << den << "\n";
        }
        cout << endl;
    }
    return 0;
}
