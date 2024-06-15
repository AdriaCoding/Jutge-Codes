#include<bits/stdc++.h>
using namespace std;

const int MAXN = 3e4 + 5;
int n, q, a[MAXN], tree[4*MAXN], lazy[4*MAXN], minElement;

void displayTree(int node, int start, int end) {
    // Base case: leaf node
    if (start == end) {
        cout << "Leaf node at index " << start << ": " << tree[node] << "\n";
        return;
    }

    // Print current node
    cout << "Node covering [" << start << ", " << end << "]: " << tree[node] << "\n";

    // Recurse on left and right children
    int mid = (start + end) / 2;
    displayTree(2*node, start, mid);
    displayTree(2*node+1, mid+1, end);
}

void displayArray(int a[], int n) {
    cout << "Weight array with min element " << minElement << ": ";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}


void build(int node, int start, int end) {
    lazy[node] = 0; //Initializy lazy 
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

void update(int node, int start, int end, int idx, int val) {
    if (lazy[node] != 0){
        tree[node] += (end - start + 1) * lazy[node];
        if(start != end) {
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }    
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
    if (lazy[node] != 0){
        tree[node] += (end - start + 1) * lazy[node];
        if(start != end) {
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
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



int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    while (cin >> n >> q) {
        minElement = INT_MAX;
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
                if(minElement == 2){
                    displayArray(a, n);
                    for(int i = 1; i <= n; i++) {
                        update(1, 1, n, i, -1);
                    }
                }
            }
            //displayTree(1, 1, n);
            //displayArray(a, n); cout << endl;
        }
        int totalSum = tree[1];
        int num, den;
        for(int i = 1; i <= n; i++) {
            int commonDivisor = gcd(a[i], totalSum); 
            num = a[i] / commonDivisor;
            den = tree[1] / commonDivisor;
            cout << num << "/" << den << "\n";
        }
        cout << endl;
    }
    return 0;
}