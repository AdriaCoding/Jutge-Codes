#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct SegmentTree {
    int n;
    vector<double> tree, lazy;

    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0.0);
        lazy.assign(4 * n, -1.0); // Initialize lazy values with -1 to denote no updates
    }

    void apply(int node, int start, int end, double value) {
        if (lazy[node] != -1) {
            // We have a pending update, apply it
            double pendingValue = lazy[node];
            tree[node] = max(tree[node], pendingValue);
            if (start != end) {
                lazy[node*2] = max(lazy[node*2], pendingValue);
                lazy[node*2+1] = max(lazy[node*2+1], pendingValue);
            }
            lazy[node] = -1;
        }

        // Now apply the current update
        tree[node] = max(tree[node], value);
        if (start != end) {
            lazy[node*2] = max(lazy[node*2], value);
            lazy[node*2+1] = max(lazy[node*2+1], value);
        }
    }

    void update(int node, int start, int end, int l, int r, double value) {
        apply(node, start, end, -1); // Apply any pending updates

        if (start > end || start > r || end < l) {
            return;
        }

        if (start >= l && end <= r) {
            apply(node, start, end, value);
            return;
        }

        int mid = (start + end) / 2;
        update(node*2, start, mid, l, r, value);
        update(node*2+1, mid+1, end, l, r, value);
        tree[node] = max(tree[node*2], tree[node*2+1]);
    }

    double query(int node, int start, int end, int idx) {
        apply(node, start, end, -1); // Apply any pending updates

        if (start == end) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        if (idx <= mid) {
            return query(node*2, start, mid, idx);
        } else {
            return query(node*2+1, mid+1, end, idx);
        }
    }

    void update(int l, int r, double value) {
        update(1, 0, n-1, l, r, value);
    }

    double query(int idx) {
        return query(1, 0, n-1, idx);
    }
};

struct Trapezoid {
    double l, r, yl, yr;

    double heightAt(double x) const {
        if (x <= l) return yl;
        if (x >= r) return yr;
        double slope = (yr - yl) / (r - l);
        return yl + slope * (x - l);
    }
};

int main() {
    int n;
    while (cin >> n) {
        vector<pair<char, vector<double>>> operations;
        vector<double> coordinates;
        for (int i = 0; i < n; ++i) {
            char op;
            cin >> op;
            if (op == 'A') {
                double l, r, yl, yr;
                cin >> l >> r >> yl >> yr;
                operations.push_back({op, {l, r, yl, yr}});
                coordinates.push_back(l);
                coordinates.push_back(r);
            } else if (op == 'C') {
                double x;
                cin >> x;
                operations.push_back({op, {x}});
                coordinates.push_back(x);
            }
        }

        // Coordinate compression
        sort(coordinates.begin(), coordinates.end());
        coordinates.erase(unique(coordinates.begin(), coordinates.end()), coordinates.end());

        auto getIndex = [&](double x) {
            return lower_bound(coordinates.begin(), coordinates.end(), x) - coordinates.begin();
        };

        SegmentTree segTree(coordinates.size());

        for (const auto& op : operations) {
            if (op.first == 'A') {
                double l = op.second[0], r = op.second[1];
                double yl = op.second[2], yr = op.second[3];
                int li = getIndex(l), ri = getIndex(r);
                for (int i = li; i < ri; ++i) {
                    double x1 = coordinates[i], x2 = coordinates[i+1];
                    double h1 = Trapezoid{l, r, yl, yr}.heightAt(x1);
                    double h2 = Trapezoid{l, r, yl, yr}.heightAt(x2);
                    segTree.update(i, i, max(h1, h2));
                }
            } else if (op.first == 'C') {
                double x = op.second[0];
                int idx = getIndex(x);
                cout << fixed << setprecision(3) << segTree.query(idx) << endl;
            }
        }
    }

    return 0;
}

