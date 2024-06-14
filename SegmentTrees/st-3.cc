// Interval updates.


#include <bits/stdc++.h>
using namespace std;


const int INF = 1e9;


using VI = vector<int>;


int n;
VI ST, lazy;


void print() {
  for (int i = 0; i < 4*n; ++i) cout << ' ' << setw(2) << i;
  cout << endl;
  for (int x : ST) cout << ' ' << setw(2) << x;
  cout << endl;
  for (int x : lazy) cout << ' ' << setw(2) << x;
  cout << endl;
}


void update(int p, int l, int r, int e, int d, int x) {
  if (l == e and r == d) {
    ST[p] = x;
    lazy[p] = true;
    return;
  }

  int m = (l + r)/2;
  int pl = 2*p;
  int pr = pl + 1;

  if (lazy[p]) {
    ST[pl] = ST[pr] = ST[p];
    lazy[pl] = lazy[pr] = true;
    lazy[p] = false;
  }

  if (e <= m) update(pl, l, m, e, min(m, d), x);
  if (d > m) update(pr, m + 1, r, max(m + 1, e), d, x);
  ST[p] = max(ST[pl], ST[pr]);
}


int query(int p, int l, int r, int e, int d) {
  if (lazy[p]) return ST[p];

  int m = (l + r)/2;
  int pl = 2*p;
  int pr = pl + 1;
  int res = -INF;
  if (e <= m) res = max(res, query(pl, l, m, e, min(m, d)));
  if (d > m) res = max(res, query(pr, m + 1, r, max(m + 1, e), d));
  return res;
}


int main() {
  cin >> n;
  ST = lazy = VI(4*n);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    update(1, 0, n - 1, i, i, x);
  }

  print();

  char c;
  while (cin >> c) {
    if (c == 'q') {
      int e, d;
      cin >> e >> d;
      cout << query(1, 0, n - 1, e, d) << endl;
    }
    else {
      int e, d, x;
      cin >> e >> d >> x;
      update(1, 0, n - 1, e, d, x);
      print();
    }
  }
}
