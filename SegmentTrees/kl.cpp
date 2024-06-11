#include<bits/stdc++.h>
using namespace std;

const int MAXN = 3e4 + 5;
int n, q, a[MAXN], tree[4*MAXN];

void build(int node, int start, int end) {
    if(start == end) {
        tree[node] = a[start];
    } else {
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

void update(int node, int start, int end, int idx, int val) {
    if(start == end) {
        a[idx] += val;
        tree[node] += val;
    } else {
        int mid = (start + end) / 2;
        if(start <= idx and idx <= mid) {
            update(2*node, start, mid, idx, val);
        } else {
            update(2*node+1, mid+1, end, idx, val);
        }
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

int query(int node, int start, int end, int sum) {
    if(start == end) {
        return start;
    } else {
        int mid = (start + end) / 2;
        if(sum <= tree[2*node]) {
            return query(2*node, start, mid, sum);
        } else {
            return query(2*node+1, mid+1, end, sum - tree[2*node]);
        }
    }
}

int main() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        a[i] = 1;
    }
    build(1, 1, n);
    while(q--) {
        int x, correct;
        cin >> x >> correct;
        int idx = query(1, 1, n, x+1);
        if(correct) {
            update(1, 1, n, idx, -1);
            if(a[idx] == 0) {
                for(int i = 1; i <= n; i++) {
                    update(1, 1, n, i, 1);
                }
            }
        } else {
            update(1, 1, n, idx, 1);
            if(a[idx] == 2) {
                for(int i = 1; i <= n; i++) {
                    update(1, 1, n, i, -1);
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << "/" << tree[1] << "\n";
    }
    return 0;
}