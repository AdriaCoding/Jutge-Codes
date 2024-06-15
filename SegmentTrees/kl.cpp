#include<bits/stdc++.h>
using namespace std;

const int MAXN = 3e4 + 5;
int n, q, a[MAXN], tree[4*MAXN], lazy[4*MAXN];
int minElement = INT_MAX;

void displayTree(int node, int start, int end) {
    if (start == end) {
        cout << "Leaf node at index " << start << ": " << tree[node] << "\n";
        return;
    }
    cout << "Node covering [" << start << ", " << end << "]: " << tree[node] << "\n";
    int mid = (start + end) / 2;
    displayTree(2*node, start, mid);
    displayTree(2*node+1, mid+1, end);
}

void displayArray(int n) {
    cout << "Weight array with min element " << minElement << ": ";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

void build(int node, int start, int end) {
    if(start == end) {
        tree[node] = a[start];
        minElement = min(minElement, a[start]);
    } else {
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

void propagate(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if(start != end) {
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int idx, int val) {
    propagate(node, start, end);
    if(start == end) {
        a[idx] += val;
        tree[node] += val;
        minElement = min(minElement, a[idx]); 
    } else {
        int mid = (start + end) / 2;
        if(start <= idx && idx <= mid) {
            update(2*node, start, mid, idx, val);
        } else {
            update(2*node+1, mid+1, end, idx, val);
        }
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

int query(int node, int start, int end, int sum) {
    propagate(node, start, end);
    if(start == end) {
        return start;
    } else {
        int mid = (start + end) / 2;
        propagate(2*node, start, mid);
        if(sum <= tree[2*node]) {
            return query(2*node, start, mid, sum);
        } else {
            return query(2*node+1, mid+1, end, sum - tree[2*node]);
        }
    }
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    while (cin >> n >> q) {
        fill(a, a + n + 1, 1);
        fill(tree, tree + 4 * n, 0);
        fill(lazy, lazy + 4 * n, 0);
        minElement = INT_MAX;
        build(1, 1, n);
        while(q--) {
            int x, correct;
            cin >> x >> correct;
            int idx = query(1, 1, n, x + 1);
            if(correct) {
                update(1, 1, n, idx, -1);
                if(a[idx] == 0) {
                    for(int i = 1; i <= n; i++) {
                        update(1, 1, n, i, 1);
                    }
                }
            } else {
                update(1, 1, n, idx, 1);
                if(minElement == 2){
                    //displayArray(n);
                    for(int i = 1; i <= n; i++) {
                        update(1, 1, n, i, -1);
                    }
                }
            }
        }
        int totalSum = tree[1];
        for(int i = 1; i <= n; i++) {
            int commonDivisor = gcd(a[i], totalSum); 
            int num = a[i] / commonDivisor;
            int den = totalSum / commonDivisor;
            cout << num << "/" << den << "\n";
        }
        cout << endl;
    }
    return 0;
}
